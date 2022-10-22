#include "stdafx.h"
#include "..\Header\MainApp.h"

#include "ImGuiMgr.h"
#include "Logo.h"
#include "PoolMgr.h"
#include "FinalStage.h"

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
	
	if (m_pManagementClass->Get_Scene()->Get_SceneId() == STAGE_SCENE)
	{
		if (Get_Layer(L"STAGE_KEY")->Get_GameList().size() == 0)
		{
			Engine::CScene*			pScene = nullptr;

			pScene = CFinalStage::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pScene, E_FAIL);

			FAILED_CHECK_RETURN(m_pManagementClass->Set_Scene(pScene), E_FAIL);
		}

		//if (Get_Layer(STAGE_GUNITEM)->Get_GameObjectMap().size() == 0)
		if(Get_DIKeyState(DIK_Y))
		{
			Engine::CScene*			pScene = nullptr;

			pScene = CFinalStage::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pScene, E_FAIL);

			FAILED_CHECK_RETURN(m_pManagementClass->Set_Scene(pScene), E_FAIL);
		}
	}


	//if (Get_DIKeyState(DIK_Y))
	//{
	//	Engine::CScene*			pScene = nullptr;

	//	pScene = CFinalStage::Create(m_pGraphicDev);
	//	NULL_CHECK_RETURN(pScene, E_FAIL);

	//	FAILED_CHECK_RETURN(m_pManagementClass->Set_Scene(pScene), E_FAIL);
	//}


	// 툴 프레임 업데이트 
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//CImGuiMgr::LoggerWindow();

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
}

HRESULT CMainApp::SetUp_DefaultSetting(LPDIRECT3DDEVICE9 * ppGraphicDev)
{
	// 디바이스 초기화
	FAILED_CHECK_RETURN(Engine::Ready_GraphicDev(g_hWnd, MODE_WIN, WINCX, WINCY, &m_pDeviceClass), E_FAIL);
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


#ifdef _DEBUG
	if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}
#endif  _DEBUG

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
