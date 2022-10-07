#include "stdafx.h"
#include "..\Header\MainApp.h"

#include "ImGuiMgr.h"
#include "Logo.h"
#include "PoolMgr.h"
#include "MovieScene.h"

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

	// �� ������ ������Ʈ 
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
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	Engine::Render_Begin(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f));
	
	m_pManagementClass->Render_Scene(m_pGraphicDev);
	
	// �� �׸���
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
	
	Engine::Render_End();

	/////////

	////D3DXCreateRenderToSurface �Լ��� ���� ������ msdn�̳� Directx ������ �� ���������� �����ϰ� �ϴ� D3DXCreateRenderToSurface�Լ��� �̿��ؼ� �ؽ��Ŀ� �׷��ַ��� �ϴ�
	//LPD3DXRENDERTOSURFACE	g_pRenderToSurface;
	//LPDIRECT3DTEXTURE9		g_pTexture;
	//LPDIRECT3DSURFACE9		g_pSurface;

	////�� ���� 3���� ��ü�� �ʿ��ϴ�.���� ��ü ���� �������� �μ����� �͵鵵 �ʿ������� ������ ���� �ʼ� �׸� ����ϰڴ�.

	////	���� 3��ü �� ���� �Ǿ��ٸ� D3DXCreateRenderToSurface �Լ��� �̿��� RenderToSurface��ü�� ��� D3DXCreateTexture�Լ��� �׷����� �ִ� �ؽ��İ�ü�� ���´�.�׸��� GetSurfaceLevel�Լ��� ����ؼ� �����̽��� �׷����°� �ؽ��Ŀ� �״�� �ű⵵�� �����Ѵ�.
	//D3DXCreateRenderToSurface(m_pGraphicDev, 15, 15, D3DFMT_A8R8G8B8, TRUE, D3DFMT_D24S8, &g_pRenderToSurface);
	//D3DXCreateTexture(m_pGraphicDev, 15, 15, 0, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_pTexture);
	//g_pTexture->GetSurfaceLevel(0, &g_pSurface);
	////�ʱ�ȭ�� ������ ���� surface�� �׷��ָ� �ȴ�.


	//g_pRenderToSurface->BeginScene(g_pSurface, NULL);
	////���⿡ surface(texture)�� �׷��� �κ��� ������ ���ָ� �ȴ�
	//m_pGraphicDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f), 1.f, 0);

	//g_pRenderToSurface->EndScene(0);

	//���� texture�� �׷��� ����� ������ ��Ƽ� uv��ǥ�� ���缭 ������ ���ָ� �ȴ�.
	//���⼭ ���� �߿��Ѱ� RenderToSurface�� ����ų� Texture�� ���鶧 format�̶� width, height�� �� ���� �־�� �Ѵ�.
	//������ �ؽ��ĸ� ���� �簢���� ũ�⵵ width, height�� ���� �־�� �Ѵ�.

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//m_pGraphicDev->CreateTexture(15, 15, 1, D3DUSAGE_RENDERTARGET, D3DFMT_D24S8, D3DPOOL_DEFAULT, &g_pTexture, NULL);
	//D3DXCreateRenderToSurface(m_pGraphicDev, 15, 15, D3DFMT_D24S8, TRUE, D3DFMT_UNKNOWN, &g_pRenderToSurface);
	//g_pTexture->GetSurfaceLevel(0, &g_pSurface);
	//m_pGraphicDev->SetRenderTarget(0, g_pSurface);
	//g_pRenderToSurface->BeginScene(g_pSurface, NULL);
	//m_pGraphicDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff0000ff, 1.0f, 0);
	//g_pRenderToSurface->EndScene(0);

	////������ �ؽ��� �׸���

	//m_pGraphicDev->SetRenderTarget(0, g_rendererTexture.g_pSurface);
	//g_rendererTexture.g_pRenderToSurface->BeginScene(g_rendererTexture.g_pSurface, NULL);
	//m_pGraphicDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff0000ff, 1.0f, 0);
	//m_pGraphicDev->SetVertexShader(NULL);
	//g_pMesh->DrawSubset(0);
	//g_rendererTexture.g_pRenderToSurface->EndScene(D3DX_FILTER_NONE);

	////���帵

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
	// ����̽� �ʱ�ȭ
	FAILED_CHECK_RETURN(Engine::Ready_GraphicDev(g_hWnd, MODE_WIN, WINCX, WINCY, &m_pDeviceClass), E_FAIL);
	m_pDeviceClass->AddRef();

	(*ppGraphicDev) = m_pDeviceClass->Get_GraphicDev();
	(*ppGraphicDev)->AddRef();

	FAILED_CHECK_RETURN(Engine::Ready_InputDev(g_hInst, g_hWnd), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"Font_Default", L"����", 15, 20, FW_HEAVY), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"Font_Jinji", L"�ü�", 30, 30, FW_NORMAL), E_FAIL);

	IMGUI_CHECKVERSION();

	// �� ����
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

#ifdef _DEBUG
	if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}
#endif // _DEBUG

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
