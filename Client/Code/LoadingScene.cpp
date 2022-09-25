#include "stdafx.h"
#include "..\Header\LoadingScene.h"

#include "Export_Function.h"
#include "LoadBar.h"
#include "ToolScene.h"
CLoadingScene::CLoadingScene(LPDIRECT3DDEVICE9 pGraphicDev)
	:CScene(pGraphicDev)
{
}


CLoadingScene::~CLoadingScene()
{
}

HRESULT CLoadingScene::Ready_Scene(void)
{
	FAILED_CHECK_RETURN(Engine::CScene::Ready_Scene(), E_FAIL);
	//	FAILED_CHECK_RETURN(Ready_Resource(m_pGraphicDev, RESOURCE_END), E_FAIL);

	FAILED_CHECK_RETURN(Ready_GameLogic_Layer(L"GameLogic"), E_FAIL);

	//m_pLoading = CLoading::Create(m_pGraphicDev, LOADING_STAGE, &m_fLoadingCount);
	//NULL_CHECK_RETURN(m_pLoading, E_FAIL);


	m_pLoading = CLoading::Create(m_pGraphicDev, LOADING_STAGE);
	NULL_CHECK_RETURN(m_pLoading, E_FAIL);



	return S_OK;
}

_int CLoadingScene::Update_Scene(const _float & fTimeDelta)
{
	_int iExit = Engine::CScene::Update_Scene(fTimeDelta);
	//	dynamic_cast<CLoadingBar*>(m_mapLayer.begin()->second->Get_GameObject(L"Loading_Bar"))->Set_Load(m_fLoadingCount  * 0.01f);
	/*if (Engine::Get_DIKeyState(DIK_RETURN) & 0x80)
	{

	Engine::CScene*		pScene = CStage::Create(m_pGraphicDev);

	NULL_CHECK_RETURN(pScene, E_FAIL);

	FAILED_CHECK_RETURN(Engine::Set_Scene(pScene), E_FAIL);

	return 0;
	}*/





	if (true == m_pLoading->Get_Finish())
	{
		if (Get_DIKeyState(DIK_1) & 0x8000)
		{
			CScene*		pScene = CStage::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pScene, E_FAIL);

			FAILED_CHECK_RETURN(Engine::Set_Scene(pScene), E_FAIL);

			return 0;
		}

		if (Get_DIKeyState(DIK_2) & 0x8000)
		{
			CScene*		pToolScene = CToolScene::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pToolScene, E_FAIL);

			FAILED_CHECK_RETURN(Engine::Set_Scene(pToolScene), E_FAIL);

			return 0;
		}
		/*if (Engine::Get_DIKeyState(DIK_RETURN) & 0x80)
		{

			Engine::CScene*		pScene = CStage::Create(m_pGraphicDev);

			NULL_CHECK_RETURN(pScene, E_FAIL);

			FAILED_CHECK_RETURN(Engine::Set_Scene(pScene), E_FAIL);

			return 0;
		}*/
	}

	return iExit;
}

void CLoadingScene::Render_Scene(void)
{
	//Render_Font(L"Font_Jinji", m_pLoading->Get_String(), &_vec2(50.f, 50.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
}

HRESULT CLoadingScene::Ready_Environment_Layer(const _tchar * pLayerTag)
{
	return S_OK;
}

HRESULT CLoadingScene::Ready_GameLogic_Layer(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;


	//backGround

	pGameObject = CBackGround::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"BackGround", pGameObject), E_FAIL);



	//pGameObject = CLoadingBar::Create(m_pGraphicDev, L"",&m_matView._41, 1.f, 3, 0.f);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LoadingBar", pGameObject), E_FAIL);


	//LoadBar


	pGameObject = CLoadBar::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LoadBar", pGameObject), E_FAIL);




	//pGameObject = CTitle::Create(m_pGraphicDev, L"Texture_Loading_Back", CTitle::RIGHT, _vec3(WINCX*0.01f, 0.f, 0.03f), 1.f, 0);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TitleLoadBack", pGameObject), E_FAIL);


	//pGameObject = CLoadingBar::Create(m_pGraphicDev, L"Texture_Loading_Bar", _vec3(-WINCX * 0.48f, WINCY*0.43f, 0.02f), 1.f, 0);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Loading_Bar", pGameObject), E_FAIL);

	//pGameObject = CLoadingBar::Create(m_pGraphicDev, L"Texture_Loading_Frame", _vec3(-WINCX * 0.48f, WINCY*0.43f, 0.02f), 1.f, 0, 1.f);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Loading_Frame", pGameObject), E_FAIL);

	m_mapLayer.insert({ pLayerTag, pLayer });


	return S_OK;
}

HRESULT CLoadingScene::Ready_UI_Layer(const _tchar * pLayerTag)
{
	return S_OK;
}

HRESULT CLoadingScene::Ready_Proto(void)
{
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_RcTexCom", CRcTex::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_LogoTexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/Title/bg_antarctic.png", TEX_NORMAL)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_LoadingTexCom", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/Texture2D/lang_select.png", TEX_NORMAL)), E_FAIL);


	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TransformCom", CTransform::Create()), E_FAIL);

	return S_OK;
}

//HRESULT CLoadingScene::Ready_Resource(LPDIRECT3DDEVICE9 & pGraphicDev, RESOURCEID eMax)
//{
//}

CLoadingScene * CLoadingScene::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLoadingScene*	pInstance = new CLoadingScene(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Engine::Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CLoadingScene::Free(void)
{
	Engine::Safe_Release(m_pLoading);
	Engine::CScene::Free();
}