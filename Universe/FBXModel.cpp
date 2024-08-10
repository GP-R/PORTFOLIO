#include "pch.h"
#include "FBXModel.h"

FBXModel::FBXModel()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_vertices = 0;
	m_indices = 0;

	m_vertexCount = 0;
	m_indexCount = 0;
	m_faceCount = 0;
}


FBXModel::FBXModel(const FBXModel& other)
{
}


FBXModel::~FBXModel()
{
}

bool FBXModel::Initialize(ID3D11Device* device, const WCHAR* modelFilename, const WCHAR* textureFilename)
{
	bool result;

	result = LoadModel(modelFilename, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
	if (!result)
	{
		return false;
	}

	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	result = LoadTexture(device, textureFilename);
	if (!result)
	{
		return false;
	}

	return true;
}

bool FBXModel::InitializeBuffers(ID3D11Device* device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	if (!m_vertices || !m_indices)
		return false;

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = m_vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = m_indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool FBXModel::LoadTexture(ID3D11Device* device, const WCHAR* filename)
{
	bool result;

	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}

	result = m_Texture->Initialize(device, filename);
	if (!result)
	{
		return false;
	}

	return true;
}

ID3D11ShaderResourceView* FBXModel::GetTexture()
{
	return m_Texture->GetTexture();
}

void FBXModel::ReleaseTexture()
{
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}

void FBXModel::Shutdown()
{
	ShutdownBuffers();

	ReleaseModel();

	return;
}

void FBXModel::Render(ID3D11DeviceContext* deviceContext)
{
	RenderBuffers(deviceContext);

	return;
}

int FBXModel::GetIndexCount()
{
	return m_indexCount;
}

int FBXModel::GetFaceCount()
{
	return m_indexCount*3;
}

void FBXModel::ShutdownBuffers()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

void FBXModel::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

bool FBXModel::LoadModel(CString filename, UINT flag)
{
	Assimp::Importer importer;
	string strPath = std::string(CT2CA(filename.operator LPCWSTR()));
	const aiScene* pScene = importer.ReadFile(strPath, flag);

	if (!pScene) return false;

	const aiMesh* pMesh = pScene->mMeshes[0];	// Assume it's a single mesh

	if (!pMesh)
		return false;

	m_vertexCount = pMesh->mNumVertices;
	m_faceCount = pMesh->mNumFaces;
	m_indexCount = m_faceCount * 3;

	if (m_vertexCount == 0 || m_indexCount == 0)
		return false;

	m_vertices = new VertexType[m_vertexCount];

	// Fill each vertex data
	for (unsigned int i = 0; i < m_vertexCount; i++)
	{
		// Get position
		m_vertices[i].position.x = pMesh->mVertices[i].x;
		m_vertices[i].position.y = pMesh->mVertices[i].y;
		m_vertices[i].position.z = pMesh->mVertices[i].z;

		// Get UV
		if (pMesh->HasTextureCoords(0)) {
			m_vertices[i].texture.x = pMesh->mTextureCoords[0][i].x;
			m_vertices[i].texture.y = pMesh->mTextureCoords[0][i].y;
		}
		else {
			m_vertices[i].texture.x = 0;
			m_vertices[i].texture.y = 0;
		}

		// Get normal
		m_vertices[i].normal.x = pMesh->mNormals[i].x;
		m_vertices[i].normal.y = pMesh->mNormals[i].y;
		m_vertices[i].normal.z = pMesh->mNormals[i].z;
	}

	m_indices = new unsigned long[m_indexCount];

	for (unsigned int i = 0; i < m_faceCount; i++)
	{
		aiFace face = pMesh->mFaces[i];

		// ��ġ �о����
		m_indices[i * 3] = face.mIndices[0];
		m_indices[i * 3 + 1] = face.mIndices[1];
		m_indices[i * 3 + 2] = face.mIndices[2];
	}

	return true;
}

void FBXModel::ReleaseModel()
{
	if (m_vertices)
	{
		delete[] m_vertices;
		m_vertices = 0;
	}

	return;
}