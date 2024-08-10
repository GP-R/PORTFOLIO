#ifndef _FBXMODELCLASS_H_
#define _FBXMODELCLASS_H_

/////////////
// LINKING //
/////////////
#pragma comment(lib, "assimp-vc142-mtd.lib")

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

#include <fstream>
#include <atlstr.h>
#include "textureclass.h"

using namespace std;

// ASSIMP library
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class FBXModel
{
public:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

public:
	FBXModel();
	FBXModel(const FBXModel&);
	~FBXModel();

	bool Initialize(ID3D11Device*, const WCHAR*, const WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	VertexType* GetVertices() { return m_vertices; }
	int GetVertexCount() { return m_vertexCount; }

	int GetIndexCount();
	int GetFaceCount();

	bool LoadModel(CString, UINT flag);
	void ReleaseModel();
	ID3D11ShaderResourceView* GetTexture();
private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, const WCHAR*);
	void ReleaseTexture();

private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	unsigned int m_vertexCount, m_indexCount, m_faceCount;
	TextureClass* m_Texture;

	VertexType* m_vertices;
	unsigned long* m_indices;
};

#endif