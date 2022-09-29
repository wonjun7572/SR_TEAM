#include "stdafx.h"
#include "..\Header\MainApp.h"

#include "ImGuiMgr.h"
#include "Logo.h"
#include "PoolMgr.h"

static bool show_transform_window = false;
static bool show_gameobject_window = false;
static bool show_save_window = false;		

USING(Engine)
CMainApp::CMainApp()	
	: m_pGraphicDev(nullptr)
{
}

CMainApp::~CMainApp()
{
	
}

HRESULT CMainApp::Ready_MainApp(void)
{
	FAILED_CHECK_RETURN(SetUp_DefaultSetting(&m_pGraphicDev), E_FAIL);	
	
	FAILED_CHECK_RETURN(Ready_Scene(m_pGraphicDev, &m_pManagementClass), E_FAIL);
	Ready_Input(g_hWnd);
	
	return S_OK;
}

_int CMainApp::Update_MainApp(const _float & fTimeDelta)
{
	Engine::Update_Input();
	Engine::SetUp_InputDev();

	NULL_CHECK_RETURN(m_pManagementClass, -1);

	// 툴 프레임 업데이트 
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	CImGuiMgr::LoggerWindow();

	m_pManagementClass->Update_Scene(fTimeDelta);

	return 0;
}

void CMainApp::LateUpdate_MainApp(void)
{
	NULL_CHECK(m_pManagementClass);

	m_pManagementClass->LateUpdate_Scene();
}

void CMainApp::Render_MainApp(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	Engine::Render_Begin(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));
	
	m_pManagementClass->Render_Scene(m_pGraphicDev);
	
	// 툴 그리기
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
	
	Engine::Render_End();

	/////////


	////D3DXCreateRenderToSurface 함수에 대한 설명은 msdn이나 Directx 문서에 잘 나와있으니 생략하고 일단 D3DXCreateRenderToSurface함수를 이용해서 텍스쳐에 그려주려면 일단
	//LPD3DXRENDERTOSURFACE	g_pRenderToSurface;
	//LPDIRECT3DTEXTURE9		g_pTexture;
	//LPDIRECT3DSURFACE9		g_pSurface;

	////와 같은 3개의 개체가 필요하다.위의 개체 말고도 여러가지 부수적인 것들도 필요하지만 설명을 위한 필수 항목만 언급하겠다.

	////	위의 3개체 가 선언 되었다면 D3DXCreateRenderToSurface 함수를 이용해 RenderToSurface개체를 얻고 D3DXCreateTexture함수로 그려질수 있는 텍스쳐개체를 얻어온다.그리고 GetSurfaceLevel함수를 사용해서 서페이스에 그려지는걸 텍스쳐에 그대로 옮기도록 설정한다.
	//D3DXCreateRenderToSurface(m_pGraphicDev, 15, 15, D3DFMT_A8R8G8B8, TRUE, D3DFMT_D24S8, &g_pRenderToSurface);
	//D3DXCreateTexture(m_pGraphicDev, 15, 15, 0, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_pTexture);
	//g_pTexture->GetSurfaceLevel(0, &g_pSurface);
	////초기화가 됐으면 이제 surface에 그려주면 된다.


	//g_pRenderToSurface->BeginScene(g_pSurface, NULL);
	////여기에 surface(texture)에 그려질 부분을 렌더링 해주면 된다
	//m_pGraphicDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f), 1.f, 0);

	//g_pRenderToSurface->EndScene(0);

	//이제 texture에 그려진 장면을 정점을 잡아서 uv좌표에 맞춰서 랜더링 해주면 된다.
	//여기서 가장 중요한건 RenderToSurface를 만들거나 Texture를 만들때 format이랑 width, height를 꼭 맞춰 주어야 한다.
	//심지어 텍스쳐를 입힐 사각형의 크기도 width, height를 맞춰 주어야 한다.

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//m_pGraphicDev->CreateTexture(15, 15, 1, D3DUSAGE_RENDERTARGET, D3DFMT_D24S8, D3DPOOL_DEFAULT, &g_pTexture, NULL);
	//D3DXCreateRenderToSurface(m_pGraphicDev, 15, 15, D3DFMT_D24S8, TRUE, D3DFMT_UNKNOWN, &g_pRenderToSurface);
	//g_pTexture->GetSurfaceLevel(0, &g_pSurface);
	//m_pGraphicDev->SetRenderTarget(0, g_pSurface);
	//g_pRenderToSurface->BeginScene(g_pSurface, NULL);
	//m_pGraphicDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff0000ff, 1.0f, 0);
	//g_pRenderToSurface->EndScene(0);





	////렌더러 텍스쳐 그리기

	//m_pGraphicDev->SetRenderTarget(0, g_rendererTexture.g_pSurface);
	//g_rendererTexture.g_pRenderToSurface->BeginScene(g_rendererTexture.g_pSurface, NULL);
	//m_pGraphicDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff0000ff, 1.0f, 0);
	//m_pGraphicDev->SetVertexShader(NULL);
	//g_pMesh->DrawSubset(0);
	//g_rendererTexture.g_pRenderToSurface->EndScene(D3DX_FILTER_NONE);


	////렌드링

	//HRESULT hr;
	//m_pGraphicDev->SetRenderTarget(0, g_pBackBuffer);
	//m_pGraphicDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	//m_pGraphicDev->BeginScene();
	//m_pGraphicDev->SetVertexShader(NULL);
	//g_pMesh->DrawSubset(0);

	//D3DXVECTOR3 pos(0, 0, 0);
	//g_pSprite->Begin(0);
	//g_pSprite->Draw(g_rendererTexture.pTexture, NULL, &pos, NULL, 0xffffffff);
	//g_pSprite->End();

	//m_pGraphicDev->EndScene();
	//hr = m_pGraphicDev->Present(NULL, NULL, NULL, NULL);










}

HRESULT CMainApp::SetUp_DefaultSetting(LPDIRECT3DDEVICE9 * ppGraphicDev)
{
	// 디바이스 초기화
	FAILED_CHECK_RETURN(Engine::Ready_GraphicDev(g_hWnd, MODE_WIN, 800, 600, &m_pDeviceClass), E_FAIL);
	m_pDeviceClass->AddRef();

	(*ppGraphicDev) = m_pDeviceClass->Get_GraphicDev();
	(*ppGraphicDev)->AddRef();

	FAILED_CHECK_RETURN(Engine::Ready_InputDev(g_hInst, g_hWnd), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"Font_Default", L"바탕", 15, 20, FW_HEAVY), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"Font_Jinji", L"궁서", 30, 30, FW_NORMAL), E_FAIL);
	IMGUI_CHECKVERSION();


	// 툴 세팅
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
																//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
																//io.ConfigViewportsNoAutoMerge = true;
																//io.ConfigViewportsNoTaskBarIcon = true;

																// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX9_Init(m_pGraphicDev);
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);

//#ifdef _DEBUG
//	if (::AllocConsole() == TRUE)
//	{
//		FILE* nfp[3];
//		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
//		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
//		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
//		std::ios::sync_with_stdio();
//	}
//#endif // _DEBUG

	return S_OK;
}

HRESULT CMainApp::Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CManagement** ppManagement)
{
	Engine::CScene*			pScene = nullptr;

	pScene = CLogo::Create(pGraphicDev);
	NULL_CHECK_RETURN(pScene, E_FAIL);

	FAILED_CHECK_RETURN(Engine::Create_Management(pGraphicDev, ppManagement), E_FAIL);
	(*ppManagement)->AddRef();

	FAILED_CHECK_RETURN((*ppManagement)->Set_Scene(pScene), E_FAIL);
	Initialize();
	return S_OK;
}

void CMainApp::Render_ImgUI()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("FPS");                       
		ImGui::Checkbox("Another Window", &show_gameobject_window);
		ImGui::Checkbox("TransFrom Window", &show_transform_window);
		ImGui::Checkbox("Save Window", &show_save_window);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Mouse Pos: %g, %g", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
		ImGui::Text("Mouse wheel: %.1f", ImGui::GetIO().MouseWheel);
		ImGui::End();
	}

	if (show_transform_window)
	{
		ImGui::Begin("TRANSFORM");

		if (ImGui::CollapsingHeader("Player"))
		{
			CTransform*		pPlayerTransformCom = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_GameLogic", L"TestPlayer", L"Proto_TransformCom", ID_DYNAMIC));
			NULL_CHECK(pPlayerTransformCom);
			ImGui::Text("TestPlayer TransForm");
			ImGui::DragFloat3("PlayerScale X/Y/Z", pPlayerTransformCom->m_vScale, 0.1f, 0.01f, 10.0f);
			ImGui::DragFloat3("PlayerRotation X/Y/Z", pPlayerTransformCom->m_vAngle, 0.1f, -180.0f, 180.0f);
			ImGui::DragFloat3("PlayerTranslation X/Y/Z", pPlayerTransformCom->m_vInfo[INFO_POS], 0.1f, -1000.0f, 1000.0f);
		}

		if (ImGui::CollapsingHeader("Terrain"))
		{
			CTransform*		pTerrainTransformCom = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Environment", L"Terrain", L"Proto_TransformCom", ID_DYNAMIC));
			NULL_CHECK(pTerrainTransformCom);
			ImGui::Text("Terrain TransForm");
			ImGui::DragFloat3("TerrainScale X/Y/Z", pTerrainTransformCom->m_vScale, 0.1f, 0.01f, 10.0f);
			ImGui::DragFloat3("TerrainRotation X/Y/Z", pTerrainTransformCom->m_vAngle, 0.1f, -180.0f, 180.0f);
			ImGui::DragFloat3("TerrainTranslation X/Y/Z", pTerrainTransformCom->m_vInfo[INFO_POS], 0.1f, -1000.0f, 1000.0f);
		}

		if (ImGui::CollapsingHeader("SkyBox"))
		{
			CTransform*		pSkyBoxTransformCom = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Environment", L"SkyBox", L"Proto_TransformCom", ID_DYNAMIC));
			NULL_CHECK(pSkyBoxTransformCom);
			ImGui::Text("SkyBox TransForm");
			ImGui::DragFloat3("SkyBoxScale X/Y/Z", pSkyBoxTransformCom->m_vScale, 0.1f, 0.01f, 10.0f);
			ImGui::DragFloat3("SkyBoxRotation X/Y/Z", pSkyBoxTransformCom->m_vAngle, 0.1f, -180.0f, 180.0f);
			ImGui::DragFloat3("SkyBoxTranslation X/Y/Z", pSkyBoxTransformCom->m_vInfo[INFO_POS], 0.1f, -1000.0f, 1000.0f);
		}

		if (ImGui::Button("Close"))
			show_transform_window = false;

		ImGui::End();
	}

	if (show_gameobject_window)
	{
		ImGui::Begin("Another Window", &show_gameobject_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_gameobject_window = false;

		ImGui::End();
	}

	if (show_save_window)
	{
		CTransform*	pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_GameLogic", L"TestPlayer", L"Proto_TransformCom", ID_DYNAMIC));

		ImGui::Begin("Save/Load", &show_save_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

		if (ImGui::Button("Save")) ///////////////////////////////////// 저장
		{
			HANDLE		hFile = CreateFile(L"../../Data/Map.dat",
				// 파일의 경로와 이름
				GENERIC_WRITE,			// 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
				NULL,					// 공유 방식(파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가)	 
				NULL,					// 보안 속성(NULL을 지정하면 기본값 상태)
				CREATE_ALWAYS,			// CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING  : 파일이 있을 경우에만 열기
				FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등) : FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일
				NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(안쓰니깐 NULL)

			if (INVALID_HANDLE_VALUE == hFile)
			{
				return;
			}

			DWORD	dwByte = 0;

			_vec3	vRight, vUp, vLook, vPos, vScale, vAngle;
			pPlayerTransform->Get_Info(INFO_RIGHT, &vRight);
			pPlayerTransform->Get_Info(INFO_UP, &vUp);
			pPlayerTransform->Get_Info(INFO_LOOK, &vLook);
			pPlayerTransform->Get_Info(INFO_POS, &vPos);
			memcpy(vScale, pPlayerTransform->m_vScale, sizeof(_vec3));
			memcpy(vAngle, pPlayerTransform->m_vAngle, sizeof(_vec3));

			WriteFile(hFile, &vRight, sizeof(_vec3), &dwByte, nullptr);
			WriteFile(hFile, &vUp, sizeof(_vec3), &dwByte, nullptr);
			WriteFile(hFile, &vLook, sizeof(_vec3), &dwByte, nullptr);
			WriteFile(hFile, &vPos, sizeof(_vec3), &dwByte, nullptr);
			WriteFile(hFile, &vScale, sizeof(_vec3), &dwByte, nullptr);
			WriteFile(hFile, &vAngle, sizeof(_vec3), &dwByte, nullptr);

			CloseHandle(hFile);

			MSG_BOX("Save_Complete");
		}

		if (ImGui::Button("Load"))///////////////////////////////////// 불러오기
		{
			CTransform*	pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_GameLogic", L"TestPlayer", L"Proto_TransformCom", ID_DYNAMIC));

			HANDLE		hFile = CreateFile(L"../../Data/Map.dat",		// 파일의 경로와 이름
				GENERIC_READ,			// 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
				NULL,					// 공유 방식(파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가)	 
				NULL,					// 보안 속성(NULL을 지정하면 기본값 상태)
				OPEN_EXISTING,			// CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING  : 파일이 있을 경우에만 열기
				FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등) : FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일
				NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(안쓰니깐 NULL)

			if (INVALID_HANDLE_VALUE == hFile)
			{
				return;
			}

			DWORD	dwByte = 0;

			_vec3	vRight, vUp, vLook, vPos, vScale, vAngle;

			while (true)
			{
				ReadFile(hFile, &vRight, sizeof(_vec3), &dwByte, nullptr);
				ReadFile(hFile, &vUp, sizeof(_vec3), &dwByte, nullptr);
				ReadFile(hFile, &vLook, sizeof(_vec3), &dwByte, nullptr);
				ReadFile(hFile, &vPos, sizeof(_vec3), &dwByte, nullptr);
				ReadFile(hFile, &vScale, sizeof(_vec3), &dwByte, nullptr);
				ReadFile(hFile, &vAngle, sizeof(_vec3), &dwByte, nullptr);

				pPlayerTransform->Set_Info(INFO_RIGHT, &vRight);
				pPlayerTransform->Set_Info(INFO_UP, &vUp);
				pPlayerTransform->Set_Info(INFO_LOOK, &vLook);
				pPlayerTransform->Set_Info(INFO_POS, &vPos);
				pPlayerTransform->Set_Angle(&vAngle);
				pPlayerTransform->Set_Scale(&vScale);

				pPlayerTransform->Update_Component(0.01f);

				//	받아온 정보 입력해줘야함

				if (0 == dwByte)
					break;

				//m_vecTile.push_back(new TILE(tInfo));
			}
			CloseHandle(hFile);
		}

		if (ImGui::Button("Close Me"))
			show_save_window = false;

		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	ImGui::EndFrame(); 
}

CMainApp * CMainApp::Create(void)
{
	CMainApp*	pInstance = new CMainApp;

	if (FAILED(pInstance->Ready_MainApp()))
	{
		MSG_BOX("MainApp Create Failed");
		Safe_Release<CMainApp*>(pInstance);		
	}
	
	return pInstance;
}

void CMainApp::Free(void)
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();


	Safe_Release(m_pGraphicDev);
	Safe_Release(m_pDeviceClass);
	Safe_Release(m_pManagementClass);
	CImGuiMgr::GetInstance()->DestroyInstance();
	CPoolMgr::GetInstance()->DestroyInstance();
	Engine::Release_Utility();
	Engine::Release_System();
}
