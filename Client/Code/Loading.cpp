#include "stdafx.h"
#include "..\Header\Loading.h"

#include "Export_Function.h"

CLoading::CLoading(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_bFinish(false)
	, m_eID(LOADING_END)	
{
	m_pGraphicDev->AddRef();
}


CLoading::~CLoading()
{
}

HRESULT CLoading::Ready_Loading(LOADINGID eID)
{
	InitializeCriticalSection(&m_Crt);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, Thread_Main, this, 0, nullptr);

	m_eID = eID;

	return S_OK;
}

_uint CLoading::Loading_ForStage(void)
{
	
	// ¹öÆÛ ÄÄÆ÷³ÍÆ®µé
	
	{
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TriColCom", CTriCol::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_RcColCom", CRcCol::Create(m_pGraphicDev)), E_FAIL);
//		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TerrainTexCom", CTerrainTex::Create(m_pGraphicDev, VTXCNTX, VTXCNTZ, VTXITV)), E_FAIL);
//		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_CubeTexCom", CCubeTex::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_SphereTexCom", CSphereTex::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"RcTex_HP", CRcTex::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"RcTex_Defense", CRcTex::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"RcTex_Bullet", CRcTex::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"FLARE_Alpha", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/Particle/fireball_hit_big%d.png", TEX_NORMAL, 8)), E_FAIL);

	}

	
	
	{
//		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TerrainTexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Terrain/Grass_%d.tga", TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_PlayerTexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Player/Ma.jpg", TEX_NORMAL)), E_FAIL);
//		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_CubeTexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/SkyBox/burger%d.dds", TEX_CUBE, 4)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_CubePlayerTexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/CubeTile/CubeTile_%d.dds", TEX_CUBE, 100)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_CubeMonsterTexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Texture.dds", TEX_CUBE, 4)), E_FAIL);
	}

	{
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_CollisionCom", CCollision::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_CalculatorCom", CCalculator::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_HitboxCom", CHitBox::Create(m_pGraphicDev)), E_FAIL);
	}

	
	// PLAYER UI
	{
		// HUD
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"theHUDui_7", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Player/theHUDui_7.png", TEX_NORMAL)), E_FAIL);
		// ¾ó±¼
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HP_100_Face", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Player/Face/HP100_%d.png", TEX_NORMAL, 5)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HP_75_Face", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Player/Face/HP75_%d.png", TEX_NORMAL, 5)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HP_50_Face", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Player/Face/HP50_%d.png", TEX_NORMAL, 5)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HP_25_Face", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Player/Face/HP25_%d.png", TEX_NORMAL, 5)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HP_0_Face", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Player/Face/HP0.png", TEX_NORMAL)), E_FAIL);
	}



	{
	// HP
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HP_Gage", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Player/Gage/theHUDui_10.png", TEX_NORMAL)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_HP", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/Texture2D/Palette Texture.png", TEX_NORMAL)), E_FAIL);

	// DEFENSE
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"DEFENSE_Gage", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Player/Gage/theHUDui_9.png", TEX_NORMAL)), E_FAIL);
	}



	// WEAPON UI
	{
	// HUD
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"theHUDui_11", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Weapon/theHUDui_11.png", TEX_NORMAL)), E_FAIL);
	
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"BULLET_Gage", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Weapon/theHUDui_12.png", TEX_NORMAL)), E_FAIL);
	// GUN
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Gun_UI", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Gun/Gun_%d.png", TEX_NORMAL, 6)), E_FAIL);
	}
	
	//ITEM
	{
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Hp", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Sprite/Hp2.jpg", TEX_NORMAL)), E_FAIL);

		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_MaxHp", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Sprite/Hp.png", TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Defense", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Sprite/DSC04709.jpg", TEX_NORMAL)), E_FAIL);
	}

	
	
	{
		// Map
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Minimap", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/\Texture2D/hud_minimap_bg.png", TEX_NORMAL)), E_FAIL);
	}








	m_bFinish = true;



	return _uint();
}

_uint CLoading::Loading_ForBoss(void)
{
	return _uint();
}

unsigned int CLoading::Thread_Main(void * pArg)
{
	CLoading*		pLoading = (CLoading*)pArg;

	_uint iFlag = 0;

	EnterCriticalSection(&(pLoading->Get_Crt()));

	switch (pLoading->Get_LoadingID())
	{
	case LOADING_STAGE:
		iFlag = pLoading->Loading_ForStage();
		break;

	case LOADING_BOSS:
		// iFlag = pLoading->Loading_ForBoss();
		break;
	}
	
	LeaveCriticalSection(&(pLoading->Get_Crt()));

	return iFlag;
}

CLoading * CLoading::Create(LPDIRECT3DDEVICE9 pGraphicDev, LOADINGID eID)
{
	CLoading*		pInstance = new CLoading(pGraphicDev);

	if (FAILED(pInstance->Ready_Loading(eID)))
	{
		MSG_BOX("Loading Create Failed");
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CLoading::Free(void)
{
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
	DeleteCriticalSection(&m_Crt);
	Safe_Release(m_pGraphicDev);
}
