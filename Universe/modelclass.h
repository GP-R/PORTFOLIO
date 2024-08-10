////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"

#include <fstream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
	    XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

	struct FaceType
	{
		int vIndex1, vIndex2, vIndex3;
		int tIndex1, tIndex2, tIndex3;
		int nIndex1, nIndex2, nIndex3;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct InstanceType
	{
		XMFLOAT3 position;
	};

	struct VertexType02
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, const WCHAR*, const WCHAR*);
	bool TXTInitialize(ID3D11Device*, const WCHAR*, const WCHAR*);
	bool InstantiateInitialize(ID3D11Device*, const WCHAR*, const WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	void InstantiateRender(ID3D11DeviceContext*);
	bool LineInitialize(ID3D11Device*, float radius, unsigned int numSegments);
	void LineRender(ID3D11DeviceContext* deviceContext);
	int GetIndexCount();
	int GetVertexCount();

	ID3D11ShaderResourceView* GetTexture();
	int GetFaceCount();
	bool LoadModel(const WCHAR*);

	bool LoadTXTModel(const WCHAR* filename);
	void ReleaseModel();
	int GetInstanceCount();

private:
	bool InitializeBuffers(ID3D11Device*);
	bool InstantiateInitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
	void InstantiateRenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, const WCHAR*);
	void ReleaseTexture();

	bool ReadFileCounts(const WCHAR*);
	bool LoadDataStructures(const WCHAR*, int, int, int, int);

	bool InitializeLineBuffers(ID3D11Device* device, float radius, unsigned int numSegments);

	void LineRenderBuffers(ID3D11DeviceContext* deviceContext);

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount, m_textureCount, m_normalCount, m_faceCount;
	TextureClass* m_Texture;

	ModelType* m_model;
	int m_polygonCount;

	int m_instanceCount = 0;
	ID3D11Buffer* m_instanceBuffer = nullptr;
};

#endif