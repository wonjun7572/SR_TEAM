#include "stdafx.h"
#include "..\Header\Logo.h"

#include "Export_Function.h"
#include "TestPlayer.h"
#include "TestMonster.h"
#include "Stage.h"
#include "ToolScene.h"
#include "TestCube.h"
#include "BaseMapping.h"

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
	FAILED_CHECK_RETURN(Ready_Layer_Wall(L"Layer_Wall"), E_FAIL);
	m_pLoading = CLoading::Create(m_pGraphicDev, LOADING_STAGE);
	NULL_CHECK_RETURN(m_pLoading, E_FAIL);


	return S_OK;
}

Engine::_int CLogo::Update_Scene(const _float& fTimeDelta)
{
	_int iResult = Engine::CScene::Update_Scene(fTimeDelta);

	if (m_PlayButton->Get_MouseCheck())
	{
		CScene*		pScene = CStage::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pScene, E_FAIL);
		FAILED_CHECK_RETURN(Engine::Set_Scene(pScene), E_FAIL);
		return 0;
	}



	return iResult;
}

void CLogo::LateUpdate_Scene(void)
{
	Engine::CScene::LateUpdate_Scene();
}

void CLogo::Render_Scene(void)
{
	//m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTraa->Get_WorldMatrixPointer());

	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);


	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);



}

HRESULT CLogo::Ready_Layer_Environment(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	// backGround
	pGameObject = CBackGround::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"BackGround", pGameObject), E_FAIL);

	//DynamicCamera
	pGameObject = CDynamicCamera::Create(m_pGraphicDev, &_vec3(10.f, 20.f, 10.f), &_vec3(20.f, 1.f, 20.f), &_vec3(0.f, 1.f, 0.f));
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

	
	m_mapLayer.insert({ pLayerTag, pLayer });
	return S_OK;
}

HRESULT CLogo::Ready_Layer_UI(const _tchar * pLayerTag)
{
	
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

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
HRESULT CLogo::Ready_Layer_Wall(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	HANDLE      hFile = CreateFile(L"../../Data/Map1.dat",      // 파일의 경로와 이름
		GENERIC_READ,         // 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
		NULL,               // 공유 방식(파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가)    
		NULL,               // 보안 속성(NULL을 지정하면 기본값 상태)
		OPEN_EXISTING,         // CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING  : 파일이 있을 경우에만 열기
		FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등) : FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일
		NULL);               // 생성될 파일의 속성을 제공할 템플릿 파일(안쓰니깐 NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return E_FAIL;
	}

	DWORD   dwByte = 0;

	_vec3   vRight, vUp, vLook, vPos, vScale, vAngle;
	_int	iDrawIndex = 0;
	CLayer* pMyLayer = nullptr;

	while (true)
	{
		ReadFile(hFile, &vRight, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &vUp, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &vLook, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &vPos, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &vScale, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &vAngle, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &iDrawIndex, sizeof(_int), &dwByte, nullptr);

		_tchar* Load_Name = new _tchar[20];
		wstring t = L"Test%d";
		wsprintfW(Load_Name, t.c_str(), m_iIndex);
		NameList.push_back(Load_Name);

		pGameObject =  CBaseMapping::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameObject(Load_Name, pGameObject), E_FAIL);

	 
		pGameObject->Set_DrawTexIndex(iDrawIndex);


		++m_iIndex;

		CTransform* Transcom = dynamic_cast<CTransform*>(pGameObject->Get_Component(L"Proto_TransformCom", ID_DYNAMIC));

		Transcom->Set_Info(INFO_RIGHT, &vRight);
		Transcom->Set_Info(INFO_UP, &vUp);
		Transcom->Set_Info(INFO_LOOK, &vLook);
		Transcom->Set_Info(INFO_POS, &vPos);
		Transcom->Set_Angle(&vAngle);
		Transcom->Set_Scale(&vScale);

		Transcom->Update_Component(0.01f);

		if (0 == dwByte)
			break;
	}
	CloseHandle(hFile);

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}
CLogo * CLogo::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLogo*	pInstance = new CLogo(pGraphicDev);

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
	for (auto iter : NameList)
	{
		Safe_Delete_Array(iter);
	}

	Engine::CScene::Free();
}


HRESULT CLogo::Ready_Proto(void)
{
	{
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_RcTexCom", CRcTex::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TransformCom", CTransform::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_CubeTexCom", CCubeTex::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TerrainTexCom", CTerrainTex::Create(m_pGraphicDev, VTXCNTX, VTXCNTZ, VTXITV)), E_FAIL);

	}
	{
	//Texture
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TerrainTexture_Stage_1", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/Texture2D/tex_stone_3.png", TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TerrainTexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Terrain/Grass_%d.tga", TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_CubeTexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/SkyBox/burger%d.dds", TEX_CUBE, 4)), E_FAIL);
//		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_LoadingTexCom", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/Texture2D/lang_select.png", TEX_NORMAL)), E_FAIL);
		
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_CubePlayerTexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/CubeTile/CubeTile_%d.dds", TEX_CUBE, 100)), E_FAIL);
	//	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_PlayerTexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Player/Ma.jpg", TEX_NORMAL)), E_FAIL);
	//	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_CubeMonsterTexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Texture.dds", TEX_CUBE, 4)), E_FAIL);
		
		
	}
	{		//MENUUI
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_OptionButton", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/MenuUI/UI%d.png", TEX_NORMAL, 2)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_LogoUITexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/Title/TitleMenu.png", TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_ButtonPlayTexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/MenuUI/UI%d.png", TEX_NORMAL, 2)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_ExitButton", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/MenuUI/UI%d.png", TEX_NORMAL, 2)), E_FAIL);
	}
	{

	//	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_CollisionCom", CCollision::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_CalculatorCom", CCalculator::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_HitboxCom", CHitBox::Create(m_pGraphicDev)), E_FAIL);
	}
	{
		//// HUD
		//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"theHUDui_7", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Player/theHUDui_7.png", TEX_NORMAL)), E_FAIL);
		//// 얼굴
		//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HP_100_Face", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Player/Face/HP100_%d.png", TEX_NORMAL, 5)), E_FAIL);
		//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HP_75_Face", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Player/Face/HP75_%d.png", TEX_NORMAL, 5)), E_FAIL);
		//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HP_50_Face", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Player/Face/HP50_%d.png", TEX_NORMAL, 5)), E_FAIL);
		//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HP_25_Face", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Player/Face/HP25_%d.png", TEX_NORMAL, 5)), E_FAIL);
		//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HP_0_Face", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Player/Face/HP0.png", TEX_NORMAL)), E_FAIL);
	}
	{
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Minimap", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/\Texture2D/hud_minimap_bg.png", TEX_NORMAL)), E_FAIL);
	}


	return S_OK;
}
