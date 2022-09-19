#include "stdafx.h"
#include "..\Header\MainApp.h"

#include "Logo.h"
#include "..\Default\imgui_impl_win32.h"
#include "..\Default\imgui_impl_dx9.h"

static bool show_transform_window = false;
static bool show_gameobject_window = false;

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

	return S_OK;
}

_int CMainApp::Update_MainApp(const _float & fTimeDelta)
{
	Engine::SetUp_InputDev();

	NULL_CHECK_RETURN(m_pManagementClass, -1);

	m_pManagementClass->Update_Scene(fTimeDelta);

	if (Get_DIKeyState(DIK_O) & 0x80)
		m_bImgUI = !m_bImgUI;

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

	if (m_bImgUI)
		Render_ImgUI();
	else
		Get_GraphicDev()->SetRenderState(D3DRS_ZENABLE, TRUE);

	Engine::Render_End();
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

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX9_Init(Get_GraphicDev());

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

	Engine::Release_Utility();
	Engine::Release_System();
}
