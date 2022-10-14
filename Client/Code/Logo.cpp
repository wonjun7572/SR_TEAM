#include "stdafx.h"
#include "..\Header\Logo.h"

#include "Export_Function.h"
#include "Stage.h"
#include "ToolScene.h"
#include "LogoBilBoard.h"
#include "LogoCamera.h"
#include "Loading.h"
#include "PlayButton.h"
#include "OptionButton.h"
#include "LogoUI.h"
#include "ExitButton.h"

CLogo::CLogo(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev)
{
}

CLogo::~CLogo()
{
}

HRESULT CLogo::Ready_Scene(void)
{
	if (FAILED(Engine::CScene::Ready_Scene()))
		return E_FAIL;

	FAILED_CHECK_RETURN(Ready_Proto(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Environment(L"Ready_Layer_Environment"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(L"Ready_Layer_UI"), E_FAIL);

	m_pLoading = CLoading::Create(m_pGraphicDev, LOADING_STAGE);
	NULL_CHECK_RETURN(m_pLoading, E_FAIL);

	return S_OK;
}

Engine::_int CLogo::Update_Scene(const _float& fTimeDelta)
{
	_int iResult = Engine::CScene::Update_Scene(fTimeDelta);

	if (m_pLoading->Get_Finish())
	{
		if (m_PlayButton->Get_MouseCheck())
		{
			CScene*      pScene = CStage::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pScene, E_FAIL);
			FAILED_CHECK_RETURN(Engine::Set_Scene(pScene), E_FAIL);
			pScene->Set_SceneId(STAGE_SCENE);
			return 0;
		}

		if (m_OptionButton->Get_MouseCheck())
		{
			CScene*      pScene = CToolScene::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pScene, E_FAIL);
			FAILED_CHECK_RETURN(Engine::Set_Scene(pScene), E_FAIL);
			pScene->Set_SceneId(TOOL_SCENE);
			return 0;
		}
	}

	return iResult;
}

void CLogo::LateUpdate_Scene(void)
{
	Engine::CScene::LateUpdate_Scene();
}

void CLogo::Render_Scene(void)
{
	
}

HRESULT CLogo::Ready_Layer_Environment(const _tchar * pLayerTag)
{
	Engine::CLayer*      pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*      pGameObject = nullptr;

	pGameObject = CLogoCamera::Create(m_pGraphicDev, &_vec3(0.f, 10.f, -20.f), &_vec3(0.f, 10.f, 0.f), &_vec3(0.f, 1.f, 0.f));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"DynamicCamera", pGameObject), E_FAIL);

	//Terrian 
	pGameObject = CTerrain::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Terrain", pGameObject), E_FAIL);

	// Sky box
	pGameObject = CSkyBox::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"SkyBox", pGameObject), E_FAIL);

	//Billboard
	pGameObject = CLogoBilboard::Create(m_pGraphicDev, _vec3(15.f, 1.f, 15.f));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LogoBilboard", pGameObject), E_FAIL);


	m_mapLayer.insert({ pLayerTag, pLayer });
	return S_OK;
}

HRESULT CLogo::Ready_Layer_UI(const _tchar * pLayerTag)
{

	Engine::CLayer*      pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*      pGameObject = nullptr;

	pGameObject = CLogoUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LogoUI", pGameObject), E_FAIL);
	//PlayButton
	m_PlayButton = dynamic_cast<CPlayButton*> (pGameObject = CPlayButton::Create(m_pGraphicDev));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"PlayButton", pGameObject), E_FAIL);

	//OptionButton
	m_OptionButton = dynamic_cast<COptionButton*>(pGameObject = COptionButton::Create(m_pGraphicDev));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"OptionButton", pGameObject), E_FAIL);

	//ExitButton
	m_ExitButton = dynamic_cast<CExitButton*>(pGameObject = CExitButton::Create(m_pGraphicDev));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"ExitButton", pGameObject), E_FAIL);

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}
CLogo * CLogo::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLogo*   pInstance = new CLogo(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CLogo::Free(void)
{
	Safe_Release(m_pLoading);

	Engine::CScene::Free();
}


HRESULT CLogo::Ready_Proto(void)
{
	{
		FAILED_CHECK_RETURN(Engine::Ready_Proto(RCTEX_COMP, CRcTex::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(TRANSFORM_COMP, CTransform::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(CUBETEX_COMP, CCubeTex::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(TERRAINTEX_COMP, CTerrainTex::Create(m_pGraphicDev, VTXCNTX, VTXCNTZ, VTXITV)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(SPHERETEX_COMP, CSphereTex::Create(m_pGraphicDev, 1.f)), E_FAIL);
	}
	{
		//Texture
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TerrainTexture_Stage_1", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/Texture2D/tex_stone_3.png", TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TerrainTexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Terrain/Grass_%d.tga", TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_CubeTexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/SkyBox/burger%d.dds", TEX_CUBE, 4)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"SkyBox_TEX", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/Sky01.jpg", TEX_NORMAL)), E_FAIL);
	

	}
	{      //MENUUI
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_OptionButton", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/MenuUI/UI%d.png", TEX_NORMAL, 2)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_LogoUITexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Sprite/character_select_UI_1.png", TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_ButtonPlayTexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/MenuUI/UI%d.png", TEX_NORMAL, 2)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_ExitButton", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/MenuUI/UI%d.png", TEX_NORMAL, 2)), E_FAIL);
	}

	//Menu Bilboard
	{
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_LogoBil", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/Texture2D/amidevil.png", TEX_NORMAL)), E_FAIL);
	}

	return S_OK;
}