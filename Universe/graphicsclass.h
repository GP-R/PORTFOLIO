////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"

#include "textureshaderclass.h"
#include "bitmapclass.h"
#include "textclass.h"
#include "SkyDomeClass.h"
#include "SkyDomeShader.h"
#include "instantiateshaderclass.h"
#include "colorshaderclass.h"
#include "FBXModel.h"
#include "TerrainClass.h"
#include "TerrainShaderClass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 50000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(bool Start);
	bool Frame(int, int, int, int, bool);

	CameraClass* getCamera();
	float GetCameraSpeed() { return CameraSpeed; }
private:
	bool Render(float, bool);
	bool RenderText();
	bool RenderSkyDome(SkyDomeClass* skyDome);
	bool BoundingSphereCollision(float firstObjBoundingSphere,
		XMVECTOR firstObjCenterOffset,
		XMMATRIX& firstObjWorldSpace,
		float secondObjBoundingSphere,
		XMVECTOR secondObjCenterOffset,
		XMMATRIX& secondObjWorldSpace);
	void CreateBoundingVolumes(FBXModel::VertexType* vertPosArray, int vertexCount, float& boundingSphere, XMVECTOR& objectCenterOffset);

private:
	D3DClass* m_D3D = nullptr;

	CameraClass* m_Camera = nullptr;
	XMVECTOR CameraCenterOffset;
	float CameraRadius = 0.0f;

	FBXModel* m_Sun = nullptr;

	FBXModel* m_Coin01 = nullptr;
	XMVECTOR m_Coin01CenterOffset;
	float m_Coin01Radius = 0.0f;

	FBXModel* m_Coin02 = nullptr;
	XMVECTOR m_Coin02CenterOffset;
	float m_Coin02Radius = 0.0f;

	FBXModel* m_Coin03 = nullptr;
	XMVECTOR m_Coin03CenterOffset;
	float m_Coin03Radius = 0.0f;

	FBXModel* m_Mercury = nullptr;
	XMVECTOR MercuryCenterOffset;
	float MercwuryRadius = 0.0f;

	FBXModel* m_Venus = nullptr;
	FBXModel* m_Earth = nullptr;
	FBXModel* m_Mars = nullptr;
	FBXModel* m_Jupiter = nullptr;
	FBXModel* m_Saturn = nullptr;
	ModelClass* m_Ring = nullptr;

	ModelClass* m_Circle2 = nullptr;
	ModelClass* m_Neptune = nullptr;
	ModelClass* m_Asteroid = nullptr;

	ModelClass* m_Circle = nullptr;
	ModelClass* m_LineModel = nullptr;
	ModelClass* m_LineModel1 = nullptr;
	ModelClass* m_LineModel2 = nullptr;
	ModelClass* m_LineModel3 = nullptr;
	ModelClass* m_LineModel4 = nullptr;
	ModelClass* m_LineModel5 = nullptr;

	TerrainClass* m_Terrain = nullptr;
	TerrainShaderClass* m_TerrainShader = nullptr;

	ModelClass* m_BillboardModel = nullptr;

	InstantiateShaderClass* m_InstantiateShader = nullptr;

	LightShaderClass* m_LightShader = nullptr;
	LightClass* m_Light = nullptr;

	ColorShaderClass* m_ColorShader = nullptr;
	TextureShaderClass* m_TextureShader = nullptr;
	BitmapClass* m_Bitmap = nullptr;

	TextClass* m_Text = nullptr;
	TextClass* m_Text2 = nullptr;

	SkyDomeClass* m_Stage01_SkyDome = nullptr;
	SkyDomeClass* m_Stage02_SkyDome = nullptr;
	SkyDomeShaderClass* m_SkyDomeShader = nullptr;

	float angle[20];
	float deltaTime = 0.0f;
	int m_NumOfPolygon;

	float PosX;
	float PosY;
	bool bStage_02 = false;
	float CameraSpeed = 30.0f;

	bool bAddCoin01 = false;
	bool bAddCoin02 = false;
	bool bAddCoin03 = false;
};

#endif