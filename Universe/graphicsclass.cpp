////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "graphicsclass.h"

GraphicsClass::GraphicsClass()
{
	m_NumOfPolygon = 0;
	PosX = 400.0f;
	PosY = 400.0f;
	for (int i = 0; i < 19; i++)
	{
		angle[i] = 40.0f * i;
	}

	deltaTime = 0.0009f; // 각도를 얼마나 자주 업데이트 할 것인지 결정하는 값
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{

}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	m_Camera->SetPosition(0.0f, 0.0f, -800.0f);

	m_Camera->SetRotation(0.0f, 0.0f, 0.0f);

	m_Sun = new FBXModel;

	m_Coin01 = new FBXModel;
	m_Coin02 = new FBXModel;
	m_Coin03 = new FBXModel;

	m_Mercury = new FBXModel;
	m_Venus = new FBXModel;
	m_Earth = new FBXModel;
	m_Mars = new FBXModel;
	m_Jupiter = new FBXModel;
	m_Saturn = new FBXModel;
	m_Ring = new ModelClass;

	m_Neptune = new ModelClass;
	m_Circle = new ModelClass;
	m_Circle2 = new ModelClass;
	m_LineModel = new ModelClass;
	m_LineModel1 = new ModelClass;
	m_LineModel2 = new ModelClass;
	m_LineModel3 = new ModelClass;
	m_LineModel4 = new ModelClass;
	m_LineModel5 = new ModelClass;

	m_BillboardModel = new ModelClass;
	if(!m_Sun || !m_Mercury || !m_Venus || !m_Earth|| !m_Mars || !m_Jupiter || !m_Saturn || !m_Circle2 || !m_Neptune || !m_Ring || !m_Circle || !m_LineModel)
	{
		return false;
	}

	m_Sun->Initialize(m_D3D->GetDevice(), L"./data/Planet.fbx", L"./data/2k_sun.dds");

	m_Coin01->Initialize(m_D3D->GetDevice(), L"./data/Planet.fbx", L"./data/2k_sun.dds");
	CreateBoundingVolumes(m_Coin01->GetVertices(), m_Coin01->GetVertexCount(), m_Coin01Radius, m_Coin01CenterOffset);

	m_Coin02->Initialize(m_D3D->GetDevice(), L"./data/Planet.fbx", L"./data/2k_sun.dds");
	CreateBoundingVolumes(m_Coin02->GetVertices(), m_Coin02->GetVertexCount(), m_Coin02Radius, m_Coin02CenterOffset);

	m_Coin03->Initialize(m_D3D->GetDevice(), L"./data/Planet.fbx", L"./data/2k_sun.dds");
	CreateBoundingVolumes(m_Coin03->GetVertices(), m_Coin03->GetVertexCount(), m_Coin03Radius, m_Coin03CenterOffset);
	
	m_Mercury->Initialize(m_D3D->GetDevice(), L"./data/Planet.fbx", L"./data/2k_mercury.dds");
	CreateBoundingVolumes(m_Mercury->GetVertices(), m_Mercury->GetVertexCount(), MercwuryRadius, MercuryCenterOffset);
	m_Venus->Initialize(m_D3D->GetDevice(), L"./data/Planet.fbx", L"./data/2k_venus.dds");
	m_Earth->Initialize(m_D3D->GetDevice(), L"./data/Planet.fbx", L"./data/2k_earth.dds");
	m_Mars->Initialize(m_D3D->GetDevice(), L"./data/Planet.fbx", L"./data/2k_mars.dds");
	m_Jupiter->Initialize(m_D3D->GetDevice(), L"./data/Planet.fbx", L"./data/2k_jupiter.dds");
	m_Saturn->Initialize(m_D3D->GetDevice(), L"./data/Planet.fbx", L"./data/2k_saturn.dds");
	m_Ring->Initialize(m_D3D->GetDevice(), L"./data/Ring.obj", L"./data/2k_mercury.dds");

	m_Circle->InstantiateInitialize(m_D3D->GetDevice(), L"./data/Rock.obj", L"./data/2k_mercury.dds");
	m_Circle2->InstantiateInitialize(m_D3D->GetDevice(), L"./data/Rock.obj", L"./data/2k_mercury.dds");

	m_LineModel->LineInitialize(m_D3D->GetDevice(), 200, 100);
	m_LineModel1->LineInitialize(m_D3D->GetDevice(), 400, 100);
	m_LineModel2->LineInitialize(m_D3D->GetDevice(), 600, 100);
	m_LineModel3->LineInitialize(m_D3D->GetDevice(), 900, 100);
	m_LineModel4->LineInitialize(m_D3D->GetDevice(), 1300, 100);
	m_LineModel5->LineInitialize(m_D3D->GetDevice(), 1900, 100);

	if (!m_BillboardModel->TXTInitialize(m_D3D->GetDevice(), L"./data/square.txt", L"./data/info.dds"))
	{
		MessageBox(hwnd, L"Could not initialize the billboard model object.", L"Error", MB_OK);
		return false;
	}

	// 지형 객체를 생성합니다.
	m_Terrain = new TerrainClass;
	if (!m_Terrain)
	{
		return false;
	}

	// 지형 객체를 초기화 합니다.
	result = m_Terrain->Initialize(m_D3D->GetDevice(), "../DXTestCamera/data/heightmap01.bmp", L"../DXTestCamera/data/dirt01.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	// 지형 쉐이더 객체를 생성합니다.
	m_TerrainShader = new TerrainShaderClass;
	if (!m_TerrainShader)
	{
		return false;
	}

	// 지형 쉐이더 객체를 초기화 합니다.
	result = m_TerrainShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}

	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	//m_NumOfPolygon += m_Sun->GetFaceCount();
	m_NumOfPolygon += m_Mercury->GetFaceCount();
	m_NumOfPolygon += m_Venus->GetFaceCount();
	m_NumOfPolygon += m_Earth->GetFaceCount();
	m_NumOfPolygon += m_Mars->GetFaceCount();
	m_NumOfPolygon += m_Jupiter->GetFaceCount();
	m_NumOfPolygon += m_Saturn->GetFaceCount();
	m_NumOfPolygon += m_Ring->GetFaceCount();
	//m_NumOfPolygon += m_Sun->GetFaceCount();

	// Create the light shader object.
	m_InstantiateShader = new InstantiateShaderClass;
	if (!m_InstantiateShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_InstantiateShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.6f, 0.6f, 0.6f, 1.0f);
//	m_Light->SetAmbientColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
//	m_Light->SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
//	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
//	m_Light->SetDirection(1.0f, 0.0f, 0.0f);
	m_Light->SetDirection(1.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}


	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}
	
	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"./data/seafloor.dds", 1024, 1024);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
//	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);

	XMMATRIX baseViewMatrix = {};
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}


	m_Text2 = new TextClass;
	if (!m_Text2)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text2->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	m_Stage01_SkyDome = new SkyDomeClass;
	if (!m_Stage01_SkyDome)
	{
		return false;
	}
	result = m_Stage01_SkyDome->Initialize(m_D3D->GetDevice(), L"./data/skymap05.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);
		return false;
	}

	m_Stage02_SkyDome = new SkyDomeClass;
	if (!m_Stage02_SkyDome)
	{
		return false;
	}
	result = m_Stage02_SkyDome->Initialize(m_D3D->GetDevice(), L"./data/skymap06.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);
		return false;
	}

	// 스카이 돔 쉐이더 객체를 생성합니다.
	m_SkyDomeShader = new SkyDomeShaderClass;
	if (!m_SkyDomeShader)
	{
		return false;
	}

	// 스카이 돔 쉐이더 객체를 초기화 합니다.
	result = m_SkyDomeShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// 지형 쉐이더 객체를 해제합니다.
	if (m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		delete m_TerrainShader;
		m_TerrainShader = 0;
	}

	if (m_InstantiateShader)
	{
		m_InstantiateShader->Shutdown();
		delete m_InstantiateShader;
		m_InstantiateShader = 0;
	}

	// 스카이 돔 쉐이더 객체를 해제합니다.
	if (m_SkyDomeShader)
	{
		m_SkyDomeShader->Shutdown();
		delete m_SkyDomeShader;
		m_SkyDomeShader = 0;
	}

	// 스카이 돔 객체를 해제합니다.
	if (m_Stage01_SkyDome)
	{
		m_Stage01_SkyDome->Shutdown();
		delete m_Stage01_SkyDome;
		m_Stage01_SkyDome = 0;
	}

	// 스카이 돔 객체를 해제합니다.
	if (m_Stage02_SkyDome)
	{
		m_Stage02_SkyDome->Shutdown();
		delete m_Stage02_SkyDome;
		m_Stage02_SkyDome = 0;
	}

	// Release the model object.
	if(m_Sun)
	{
		m_Sun->Shutdown();
		delete m_Sun;
		m_Sun = 0;
	}
	if (m_Mercury)
	{
		m_Mercury->Shutdown();
		delete m_Mercury;
		m_Mercury = 0;
	}
	if (m_Venus)
	{
		m_Venus->Shutdown();
		delete m_Venus;
		m_Venus = 0;
	}
	if (m_Earth)
	{
		m_Earth->Shutdown();
		delete m_Earth;
		m_Earth = 0;
	}
	if (m_Mars)
	{
		m_Mars->Shutdown();
		delete m_Mars;
		m_Mars = 0;
	}
	if (m_Jupiter)
	{
		m_Jupiter->Shutdown();
		delete m_Jupiter;
		m_Jupiter = 0;
	}
	if (m_Saturn)
	{
		m_Saturn->Shutdown();
		delete m_Saturn;
		m_Saturn = 0;
	}
	if (m_Circle2)
	{
		m_Circle2->Shutdown();
		delete m_Circle2;
		m_Circle2 = 0;
	}
	if (m_Neptune)
	{
		m_Neptune->Shutdown();
		delete m_Neptune;
		m_Neptune = 0;
	}
	if (m_Ring)
	{
		m_Ring->Shutdown();
		delete m_Ring;
		m_Ring = 0;
	}
	if (m_Circle)
	{
		m_Circle->Shutdown();
		delete m_Circle;
		m_Circle = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}
	
	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}
	if (m_LineModel)
	{
		m_LineModel->Shutdown();
		delete m_LineModel;
		m_LineModel = 0;
	}
	if (m_LineModel1)
	{
		m_LineModel1->Shutdown();
		delete m_LineModel1;
		m_LineModel1 = 0;
	}
	if (m_LineModel2)
	{
		m_LineModel2->Shutdown();
		delete m_LineModel2;
		m_LineModel2 = 0;
	}
	if (m_LineModel3)
	{
		m_LineModel3->Shutdown();
		delete m_LineModel3;
		m_LineModel3 = 0;
	}
	if (m_LineModel4)
	{
		m_LineModel4->Shutdown();
		delete m_LineModel4;
		m_LineModel4 = 0;
	}
	if (m_LineModel5)
	{
		m_LineModel5->Shutdown();
		delete m_LineModel5;
		m_LineModel5 = 0;
	}
	// 지형 객체를 해제합니다.
	if (m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}
	return;
}

bool GraphicsClass::BoundingSphereCollision(float firstObjBoundingSphere,
	XMVECTOR firstObjCenterOffset,
	XMMATRIX& firstObjWorldSpace,
	float secondObjBoundingSphere,
	XMVECTOR secondObjCenterOffset,
	XMMATRIX& secondObjWorldSpace)
{
	//Declare local variables
	XMVECTOR world_1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR world_2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	float objectsDistance = 0.0f;

	//Transform the objects world space to objects REAL center in world space
	world_1 = XMVector3TransformCoord(firstObjCenterOffset, firstObjWorldSpace);
	world_2 = XMVector3TransformCoord(secondObjCenterOffset, secondObjWorldSpace);

	//Get the distance between the two objects
	objectsDistance = XMVectorGetX(XMVector3Length(world_1 - world_2));

	//If the distance between the two objects is less than the sum of their bounding spheres...
	if (objectsDistance <= (firstObjBoundingSphere + secondObjBoundingSphere))
		//Return true
		return true;

	//If the bounding spheres are not colliding, return false
	return false;
}

void GraphicsClass::CreateBoundingVolumes(FBXModel::VertexType* vertArray, int vertexCount, float& boundingSphere, XMVECTOR& objectCenterOffset)
{
	XMFLOAT3 minVertex = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
	XMFLOAT3 maxVertex = XMFLOAT3(-FLT_MAX, -FLT_MAX, -FLT_MAX);


	for (int i = 0; i < vertexCount; i++)
	{
		// Update the minVertex and maxVertex from the model's vertices
		minVertex.x = min(minVertex.x, vertArray[i].position.x);
		minVertex.y = min(minVertex.y, vertArray[i].position.y);
		minVertex.z = min(minVertex.z, vertArray[i].position.z);

		maxVertex.x = max(maxVertex.x, vertArray[i].position.x);
		maxVertex.y = max(maxVertex.y, vertArray[i].position.y);
		maxVertex.z = max(maxVertex.z, vertArray[i].position.z);
	}

	// Compute the model's center
	float distX = (maxVertex.x - minVertex.x) / 2.0f;
	float distY = (maxVertex.y - minVertex.y) / 2.0f;
	float distZ = (maxVertex.z - minVertex.z) / 2.0f;

	objectCenterOffset = XMVectorSet(maxVertex.x - distX, maxVertex.y - distY, maxVertex.z - distZ, 0.0f);

	// Compute the bounding sphere radius
	boundingSphere = XMVectorGetX(XMVector3Length(XMVectorSet(distX, distY, distZ, 0.0f)));
}

bool GraphicsClass::Frame(bool Start)
{
	bool result;

	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += XM_PI * 0.0005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Render the graphics scene.
	result = Render(rotation, Start);
	if(!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::Frame(int fps, int cpu, int mouseX, int mouseY, bool Start)
{
	bool result;
	static float rotation = 0.0f;

	rotation += (float)XM_PI * 0.01f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	result = m_Text->SetFPS(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetCPU(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetMousePosition(m_NumOfPolygon, mouseY, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text2->SetTitle(m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = Render(rotation, Start);
	if (!result)
	{
		return false;
	}

	return true;
}

CameraClass* GraphicsClass::getCamera()
{
	return m_Camera;
}

bool GraphicsClass::Render(float rotation, bool Start)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;
	XMFLOAT3 cameraPosition;
	XMFLOAT3 billboardPos;
	float x, y;
	float radius;

	if (!bStage_02)
	{
		for (int i = 0; i < 19; i++)
		{
			angle[i] += deltaTime;
		}
		//angle[4] -= 0.01f;
		//angle[5] -= 0.02f;
		PosX -= deltaTime*30;
		PosY -= deltaTime;

		m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

		m_Camera->Render();

		m_D3D->GetWorldMatrix(worldMatrix);
		m_Camera->GetViewMatrix(viewMatrix);
		m_D3D->GetProjectionMatrix(projectionMatrix);
		m_D3D->GetOrthoMatrix(orthoMatrix);

		billboardPos.x = 0.0f;
		billboardPos.y = 1000.0f;
		billboardPos.z = 2000.0f;

		result = RenderSkyDome(m_Stage01_SkyDome);
		if (!result)
		{
			assert("Render Sky Dome Error");
		}
		result = RenderText();
		if (!result)
		{
			assert("Render Text Error");
		}

		if (Start == false)
		{
			result = m_Text2->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
			if (!result)
			{
				return false;
			}
		}

		m_Camera->GetViewMatrix(viewMatrix);
		if (Start)
		{
			cameraPosition = m_Camera->GetPosition();

			double billboardAngle = atan2(billboardPos.x - cameraPosition.x, billboardPos.z - cameraPosition.z) * (180.0 / XM_PI);
			float bbRotation = (float)billboardAngle * 0.0174532925f;

			worldMatrix = XMMatrixScaling(300.0f, 300.0f, 300.0f) * XMMatrixRotationY(bbRotation) * XMMatrixTranslation(billboardPos.x, billboardPos.y, billboardPos.z);

			m_BillboardModel->Render(m_D3D->GetDeviceContext());

			if (!m_TextureShader->Render(m_D3D->GetDeviceContext(), m_BillboardModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_BillboardModel->GetTexture()))
			{
				return false;
			}

			m_D3D->GetWorldMatrix(worldMatrix);

			worldMatrix = XMMatrixScaling(5.0f, 5.0f, 5.0f) * XMMatrixTranslation(PosX,PosY,-50.0f);
			m_Circle->InstantiateRender(m_D3D->GetDeviceContext());

			result = m_InstantiateShader->Render(m_D3D->GetDeviceContext(), m_Circle->GetIndexCount(), 10,
				worldMatrix, viewMatrix, projectionMatrix,
				m_Circle->GetTexture(),
				m_Light->GetDirection(), XMFLOAT4(0.15f, 0.15f, 0.15f, 1.0f), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));


			m_D3D->GetWorldMatrix(worldMatrix);

			worldMatrix = XMMatrixScaling(5.0f, 5.0f, 5.0f) * XMMatrixTranslation(PosX, PosY-800.0f, -50.0f);
			m_Circle2->InstantiateRender(m_D3D->GetDeviceContext());

			result = m_InstantiateShader->Render(m_D3D->GetDeviceContext(), m_Circle2->GetIndexCount(), 10,
				worldMatrix, viewMatrix, projectionMatrix,
				m_Circle2->GetTexture(),
				m_Light->GetDirection(), XMFLOAT4(0.15f, 0.15f, 0.15f, 1.0f), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

			m_D3D->GetWorldMatrix(worldMatrix);
			m_LineModel->LineRender(m_D3D->GetDeviceContext());
			if (!m_ColorShader->LineRender(m_D3D->GetDeviceContext(), m_LineModel->GetVertexCount(), worldMatrix, viewMatrix, projectionMatrix))
			{
				return false;
			}

			m_D3D->GetWorldMatrix(worldMatrix);
			m_LineModel1->LineRender(m_D3D->GetDeviceContext());
			if (!m_ColorShader->LineRender(m_D3D->GetDeviceContext(), m_LineModel1->GetVertexCount(), worldMatrix, viewMatrix, projectionMatrix))
			{
				return false;
			}

			m_D3D->GetWorldMatrix(worldMatrix);
			m_LineModel2->LineRender(m_D3D->GetDeviceContext());
			if (!m_ColorShader->LineRender(m_D3D->GetDeviceContext(), m_LineModel2->GetVertexCount(), worldMatrix, viewMatrix, projectionMatrix))
			{
				return false;
			}

			m_D3D->GetWorldMatrix(worldMatrix);
			m_LineModel3->LineRender(m_D3D->GetDeviceContext());
			if (!m_ColorShader->LineRender(m_D3D->GetDeviceContext(), m_LineModel3->GetVertexCount(), worldMatrix, viewMatrix, projectionMatrix))
			{
				return false;
			}

			m_D3D->GetWorldMatrix(worldMatrix);
			m_LineModel4->LineRender(m_D3D->GetDeviceContext());
			if (!m_ColorShader->LineRender(m_D3D->GetDeviceContext(), m_LineModel4->GetVertexCount(), worldMatrix, viewMatrix, projectionMatrix))
			{
				return false;
			}

			m_D3D->GetWorldMatrix(worldMatrix);
			m_LineModel5->LineRender(m_D3D->GetDeviceContext());
			if (!m_ColorShader->LineRender(m_D3D->GetDeviceContext(), m_LineModel5->GetVertexCount(), worldMatrix, viewMatrix, projectionMatrix))
			{
				return false;
			}

			m_D3D->GetWorldMatrix(worldMatrix);

			//worldMatrix = XMMatrixScaling(300.0f, 300.0f, 300.0f) * XMMatrixTranslation(100.0f, 0.0f, 0.0f) * XMMatrixRotationY(rotation);
			worldMatrix = XMMatrixScaling(100.0f, 100.0f, 100.0f) * XMMatrixRotationY(rotation) * XMMatrixTranslation(0.0f, 0.0f, 0.0f);
			m_Sun->Render(m_D3D->GetDeviceContext());

			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Sun->GetIndexCount(),
				worldMatrix, viewMatrix, projectionMatrix,
				m_Sun->GetTexture(),
				m_Light->GetDirection(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) , m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), INFINITE);
	


			m_D3D->GetWorldMatrix(worldMatrix);

			radius = 200.0f;
			x = radius * cos(angle[0]);
			y = radius * sin(angle[0]);

			worldMatrix = XMMatrixScaling(60.0f, 60.0f, 60.0f) * XMMatrixRotationY(rotation) * XMMatrixTranslation(x, 0.0f, y);

			m_Mercury->Render(m_D3D->GetDeviceContext());

			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Mercury->GetIndexCount(),
				worldMatrix, viewMatrix, projectionMatrix,
				m_Mercury->GetTexture(),
				XMFLOAT3(x, 0.0f, y), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

			m_D3D->GetWorldMatrix(worldMatrix);
			worldMatrix = XMMatrixTranslation(x, 0.0f, y);

			XMVECTOR zero = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			XMMATRIX tmp;
			m_D3D->GetWorldMatrix(tmp);
			tmp = XMMatrixTranslation(m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z);

			if (BoundingSphereCollision(MercwuryRadius * 50, zero, worldMatrix, 1.0f, zero, tmp))
			{
				bStage_02 = true;

				m_Camera->SetPosition(0.0f, 0.0f, 30.0f);
				CameraSpeed = 0.5f;
			}


			radius = 400.0f;
	
			x = radius * cos(angle[1]);
			y = radius * sin(angle[1]);

			m_D3D->GetWorldMatrix(worldMatrix);

			worldMatrix = XMMatrixScaling(60.0f, 60.0f, 60.0f)  * XMMatrixRotationY(rotation) * XMMatrixTranslation(x, 0.0f,y);
			m_Venus->Render(m_D3D->GetDeviceContext());

			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Venus->GetIndexCount(),
				worldMatrix, viewMatrix, projectionMatrix,
				m_Venus->GetTexture(),
				XMFLOAT3(x, 0.0f, y), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());



			radius = 600.0f;
			x = radius * cos(angle[2]);
			y = radius * sin(angle[2]);

			m_D3D->GetWorldMatrix(worldMatrix);

			worldMatrix = XMMatrixScaling(110.0f, 110.0f, 110.0f)  * XMMatrixRotationY(rotation) * XMMatrixTranslation(x, 0.0f, y);
			m_Earth->Render(m_D3D->GetDeviceContext());

			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Earth->GetIndexCount(),
				worldMatrix, viewMatrix, projectionMatrix,
				m_Earth->GetTexture(),
				XMFLOAT3(x, 0.0f, y), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());



			radius = 900.0f;
			x = radius * cos(angle[3]);
			y = radius * sin(angle[3]);

			m_D3D->GetWorldMatrix(worldMatrix);
			worldMatrix = XMMatrixScaling(90.0f, 90.0f, 90.0f)   * XMMatrixRotationY(rotation) * XMMatrixTranslation(x, 0.0f, y);
			m_Mars->Render(m_D3D->GetDeviceContext());

			/*result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Mars->GetIndexCount(),
				worldMatrix, viewMatrix, projectionMatrix,
				m_Mars->GetTexture(),
				XMFLOAT3(x, 0.0f, y), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());*/



			radius = 1300.0f;
			x = radius * cos(angle[4]);
			y = radius * sin(angle[4]);

			m_D3D->GetWorldMatrix(worldMatrix);

			worldMatrix = XMMatrixScaling(200.0f, 200.0f, 200.0f)  * XMMatrixRotationY(rotation) * XMMatrixTranslation(x, 0.0f, y);
			m_Jupiter->Render(m_D3D->GetDeviceContext());

			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Jupiter->GetIndexCount(),
				worldMatrix, viewMatrix, projectionMatrix,
				m_Jupiter->GetTexture(),
				XMFLOAT3(x, 0.0f, y), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

			radius = 1900.0f;
			x = radius * cos(angle[5]);
			y = radius * sin(angle[5]);

			m_D3D->GetWorldMatrix(worldMatrix);

			worldMatrix = XMMatrixScaling(130.0f, 130.0f, 130.0f)  * XMMatrixRotationY(rotation) * XMMatrixTranslation(x, 0.0f,y);
			m_Saturn->Render(m_D3D->GetDeviceContext());

			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Saturn->GetIndexCount(),
				worldMatrix, viewMatrix, projectionMatrix,
				m_Saturn->GetTexture(),
				XMFLOAT3(x, 0.0f, y), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

			m_D3D->GetWorldMatrix(worldMatrix);

			worldMatrix = XMMatrixScaling(130.0f, 130.0f, 130.0f) * XMMatrixRotationY(rotation) * XMMatrixTranslation(x, 0.0f, y);
			m_Ring->Render(m_D3D->GetDeviceContext());

			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Ring->GetIndexCount(),
				worldMatrix, viewMatrix, projectionMatrix,
				m_Ring->GetTexture(),
				XMFLOAT3(x, 0.0f, y), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		}
	}
	else
	{
		m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

		m_Camera->Render();

		m_D3D->GetWorldMatrix(worldMatrix);
		m_Camera->GetViewMatrix(viewMatrix);
		m_D3D->GetProjectionMatrix(projectionMatrix);
		m_D3D->GetOrthoMatrix(orthoMatrix);

		result = RenderSkyDome(m_Stage02_SkyDome);
		if (!result)
		{
			assert("Render Sky Dome Error");
		}
		// 지형 버퍼를 렌더링 합니다.
		m_Terrain->Render(m_D3D->GetDeviceContext());

		if (!m_TerrainShader->Render(m_D3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Light->GetDirection(), m_Terrain->GetTexture()))
		{
			return false;
		}

		if (!bAddCoin01)
		{
			m_D3D->GetWorldMatrix(worldMatrix);

			worldMatrix = XMMatrixScaling(1.0f, 1.0f, 1.0f) * XMMatrixTranslation(20.0f, 3.0f, 20.0f);
			m_Coin01->Render(m_D3D->GetDeviceContext());

			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Coin01->GetIndexCount(),
				worldMatrix, viewMatrix, projectionMatrix,
				m_Coin01->GetTexture(),
				m_Light->GetDirection(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), INFINITE);

			m_D3D->GetWorldMatrix(worldMatrix);
			worldMatrix = XMMatrixTranslation(20.0f, 3.0f, 20.0f);

			XMVECTOR zero = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			XMMATRIX tmp;
			m_D3D->GetWorldMatrix(tmp);
			tmp = XMMatrixTranslation(m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z);

			if (BoundingSphereCollision(m_Coin01Radius, zero, worldMatrix, 1.0f, zero, tmp))
			{
				bAddCoin01 = true;
			}
		}

		//----------------------------------------------------------------

		if (!bAddCoin02)
		{
			m_D3D->GetWorldMatrix(worldMatrix);

			worldMatrix = XMMatrixScaling(1.0f, 1.0f, 1.0f) * XMMatrixTranslation(100.0f, 3.0f, 100.0f);
			m_Coin02->Render(m_D3D->GetDeviceContext());

			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Coin02->GetIndexCount(),
				worldMatrix, viewMatrix, projectionMatrix,
				m_Coin02->GetTexture(),
				m_Light->GetDirection(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), INFINITE);

			m_D3D->GetWorldMatrix(worldMatrix);
			worldMatrix = XMMatrixTranslation(100.0f, 3.0f, 100.0f);

			XMVECTOR zero = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			XMMATRIX tmp;
			m_D3D->GetWorldMatrix(tmp);
			tmp = XMMatrixTranslation(m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z);

			if (BoundingSphereCollision(m_Coin02Radius, zero, worldMatrix, 1.0f, zero, tmp))
			{
				bAddCoin02 = true;
			}
		}


		//----------------------------------------------------------------

		if (!bAddCoin03)
		{
			m_D3D->GetWorldMatrix(worldMatrix);

			worldMatrix = XMMatrixScaling(1.0f, 1.0f, 1.0f) * XMMatrixTranslation(40.0f, 3.0f, 150.0f);
			m_Coin03->Render(m_D3D->GetDeviceContext());

			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Coin03->GetIndexCount(),
				worldMatrix, viewMatrix, projectionMatrix,
				m_Coin03->GetTexture(),
				m_Light->GetDirection(), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), INFINITE);

			m_D3D->GetWorldMatrix(worldMatrix);
			worldMatrix = XMMatrixTranslation(40.0f, 3.0f, 150.0f);

			XMVECTOR zero = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			XMMATRIX tmp;
			m_D3D->GetWorldMatrix(tmp);
			tmp = XMMatrixTranslation(m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z);

			if (BoundingSphereCollision(m_Coin03Radius, zero, worldMatrix, 1.0f, zero, tmp))
			{
				bAddCoin03 = true;
			}
		}
		//----------------------------------------------------------------
	 }
	 if (bAddCoin01 && bAddCoin02 && bAddCoin03)
	 {
		 return false;
	 }
	 m_D3D->EndScene();
	return true;
}

bool GraphicsClass::RenderText()
{
	XMMATRIX worldMatrix{}, orthoMatrix{};
	bool result = false;

	m_D3D->TurnOnAlphaBlending();
	m_D3D->TurnZBufferOff();

	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);

	m_D3D->TurnOffAlphaBlending();
	m_D3D->TurnZBufferOn();

	return result;
}

bool GraphicsClass::RenderSkyDome(SkyDomeClass* skyDome)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	XMFLOAT3 cameraPosition{};
	bool result = false;

	m_D3D->TurnOffCulling();
	m_D3D->TurnZBufferOff();

	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_Camera->GetViewMatrix(viewMatrix);


	cameraPosition = m_Camera->GetPosition();
	XMMATRIX Scale = XMMatrixScaling(50000.0f, 50000.0f, 50000.0f);
	worldMatrix = Scale * XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);
	
	skyDome->Render(m_D3D->GetDeviceContext());
	result = m_SkyDomeShader->Render(m_D3D->GetDeviceContext(), skyDome->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		skyDome->GetTexture());

	m_D3D->TurnOnCulling();
	m_D3D->TurnZBufferOn();

	return result;
}