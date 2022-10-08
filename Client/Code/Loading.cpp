#include "stdafx.h"
#include "..\Header\Loading.h"

#include "Export_Function.h"
#include "..\..\Engine\Header\Engine_Macro.h"

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
	// 버퍼 컴포넌트들
	{
	  //FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TerrainTexCom", CTerrainTex::Create(m_pGraphicDev, VTXCNTX, VTXCNTZ, VTXITV)), E_FAIL);
      //FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_CubeTexCom", CCubeTex::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(RCTEX_HP_COMP, CRcTex::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(RCTEX_DEFENCE_COMP, CRcTex::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(RCTEX_BULLET_COMP, CRcTex::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(RCTEX_MONTER_HP_COMP, CRcTex::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(RCTEX_GENERAL_MONSTER_HP_COMP, CRcTex::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(RCTEX_GENERAL_MONSTER_HUD_COMP, CRcTex::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(SPHERECOL_COMP, CSphereTex::Create(m_pGraphicDev, 1.f)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(FLEXIBLEAXISCUBE_COMP, CFlexibleAxisCube::Create(m_pGraphicDev)), E_FAIL);
	}
	// 파티클
	{
		FAILED_CHECK_RETURN(Engine::Ready_Proto(SHOTPARTICLE_TEX, CTexture::Create(m_pGraphicDev, SHOTPARTICLE_TEX_PATH, TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(BULLETPARTICLE_TEX, CTexture::Create(m_pGraphicDev, BULLETPARTICLE_TEX_PATH, TEX_NORMAL)), E_FAIL);
	}
	
	{
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_CubePlayerTexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/CubeTile/CubeTile_%d.dds", TEX_CUBE, 100)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_CubeMonsterTexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/Texture.dds", TEX_CUBE, 4)), E_FAIL);
	}

	{
		FAILED_CHECK_RETURN(Engine::Ready_Proto(COLLISION_COMP, CCollision::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(CALCULATOR_COMP, CCalculator::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(HITBOX_COMP, CHitBox::Create(m_pGraphicDev)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(QUATERNION_COMP, CQuarternion::Create(m_pGraphicDev)), E_FAIL);
	}
	
	// AnimationPlayer파싱
	{
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"", CTexture::Create(m_pGraphicDev, HP_100_FACE_PATH, TEX_NORMAL, 5)), E_FAIL);
	}

	// PLAYER UI
	{
		// HUD
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"theHUDui_7", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Player/theHUDui_7.png", TEX_NORMAL)), E_FAIL);
		// 얼굴
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HP_100_Face", CTexture::Create(m_pGraphicDev, HP_100_FACE_PATH, TEX_NORMAL, 5)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HP_75_Face", CTexture::Create(m_pGraphicDev, HP_75_FACE_PATH, TEX_NORMAL, 5)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HP_50_Face", CTexture::Create(m_pGraphicDev, HP_50_FACE_PATH, TEX_NORMAL, 5)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HP_25_Face", CTexture::Create(m_pGraphicDev, HP_25_FACE_PATH, TEX_NORMAL, 5)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HP_0_Face", CTexture::Create(m_pGraphicDev, HP_0_FACE_PATH, TEX_NORMAL)), E_FAIL);
	}

	{
		// HP
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"HP_Gage", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Player/Gage/theHUDui_10.png", TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Monster_General_HP", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/Texture2D/Palette Texture.png", TEX_NORMAL)), E_FAIL);

		FAILED_CHECK_RETURN(Engine::Ready_Proto(MONSTER_HP_TEX, CTexture::Create(m_pGraphicDev, MONSTER_HP_TEX_PATH, TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(MONSTER_HP_HUD_TEX, CTexture::Create(m_pGraphicDev, MONSTER_HP_HUD_TEX_PATH, TEX_NORMAL)), E_FAIL);

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

	//인벤토리
	{
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_InventoryTexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Inventory/QuickSlot9.png", TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_ItemIconTexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Inventory/ammo_box_pistol.png", TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_InvCursorTexture", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Inventory/Cursor0.png", TEX_NORMAL)), E_FAIL);

	}

	//ITEM
	{
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Hp", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Sprite/Hp2.jpg", TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_MaxHp", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Sprite/Hp.png", TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Defense", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Sprite/DSC04709.jpg", TEX_NORMAL)), E_FAIL);
	}

	// Map
	{
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Minimap", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/\Texture2D/hud_minimap_bg.png", TEX_NORMAL)), E_FAIL);
	}

	// PNGtoCube
	{
		FAILED_CHECK_RETURN(Engine::Ready_Proto(RIFLE_ITEM_BUFFER, CDynamicBuffer::Create(m_pGraphicDev, RIFLE_ITEM_TEX_PATH, 0.01f, 1.f, 1.f)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(RIFLE_ITEM_TEX, CTexture::Create(m_pGraphicDev, RIFLE_ITEM_TEX_PATH, TEX_NORMAL)), E_FAIL);
	
		FAILED_CHECK_RETURN(Engine::Ready_Proto(SHOTGUN_ITEM_BUFFER, CDynamicBuffer::Create(m_pGraphicDev, SHOTGUN_ITEM_TEX_PATH, 0.01f, 1.f, 1.f)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(SHOTGUN_ITEM_TEX, CTexture::Create(m_pGraphicDev, SHOTGUN_ITEM_TEX_PATH, TEX_NORMAL)), E_FAIL);

		FAILED_CHECK_RETURN(Engine::Ready_Proto(SNIPER_ITEM_BUFFER, CDynamicBuffer::Create(m_pGraphicDev, SNIPER_ITEM_TEX_PATH, 0.01f, 1.f, 1.f)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(SNIPER_ITEM_TEX, CTexture::Create(m_pGraphicDev, SNIPER_ITEM_TEX_PATH, TEX_NORMAL)), E_FAIL);
	
		FAILED_CHECK_RETURN(Engine::Ready_Proto(ADDHP_ITEM_BUFFER, CDynamicBuffer::Create(m_pGraphicDev, ADDHP_ITEM_TEX_PATH, 0.01f, 1.f, 1.f)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(ADDHP_ITEM_TEX, CTexture::Create(m_pGraphicDev, ADDHP_ITEM_TEX_PATH, TEX_NORMAL)), E_FAIL);

		FAILED_CHECK_RETURN(Engine::Ready_Proto(ADDDEFENCE_ITEM_BUFFER, CDynamicBuffer::Create(m_pGraphicDev, ADDDEFENCE_ITEM_TEX_PATH, 0.01f, 1.f, 1.f)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(ADDDEFENCE_ITEM_TEX, CTexture::Create(m_pGraphicDev, ADDDEFENCE_ITEM_TEX_PATH, TEX_NORMAL)), E_FAIL);

		FAILED_CHECK_RETURN(Engine::Ready_Proto(ADDMAXHP_ITEM_BUFFER, CDynamicBuffer::Create(m_pGraphicDev, ADDMAXHP_ITEM_TEX_PATH, 0.01f, 1.f, 1.f)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(ADDMAXHP_ITEM_TEX, CTexture::Create(m_pGraphicDev, ADDMAXHP_ITEM_TEX_PATH, TEX_NORMAL)), E_FAIL);

		FAILED_CHECK_RETURN(Engine::Ready_Proto(BULLET_ITEM_BUFFER, CDynamicBuffer::Create(m_pGraphicDev, BULLET_ITEM_TEX_PATH, 0.01f, 1.f, 1.f)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(BULLET_ITEM_TEX, CTexture::Create(m_pGraphicDev, BULLET_ITEM_TEX_PATH, TEX_NORMAL)), E_FAIL);
	}

	// ITEM
	{
		FAILED_CHECK_RETURN(Engine::Ready_Proto(ITEM_TRANSFORM_COMP, CTransform::Create(m_pGraphicDev)), E_FAIL);
	}

	FAILED_CHECK_RETURN(Engine::Ready_Proto(CROSSHAIR_RIFLE_TEX, CTexture::Create(m_pGraphicDev, CROSSHAIR_RIFLE_TEX_PATH, TEX_NORMAL)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(CROSSHAIR_SHOTGUN_TEX, CTexture::Create(m_pGraphicDev, CROSSHAIR_SHOTGUN_PATH, TEX_NORMAL)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(CROSSHAIR_SNIPER_TEX, CTexture::Create(m_pGraphicDev, CROSSHAIR_SNIPER_TEX_PATH, TEX_NORMAL)), E_FAIL);
	
	{
		//Shop
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_ShopTextureCom", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Sprite/UI upgrade system - sheet_2.png", TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_InteractShop", CTexture::Create(m_pGraphicDev, L"../Bin/Resource/Texture/CubeTile/CubeTile_%d.dds", TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_UziTextureCom", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Gun/Gun_0.png", TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_ShotGunTextureCom", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Gun/Gun_2.png", TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_SniperTextureCom", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/Gun/Gun_4.png", TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_ButtonOneformCom", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/ShopUI/UI%d.png", TEX_NORMAL, 2)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_ButtonTwoformCom", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/ShopUI/UI%d.png", TEX_NORMAL, 2)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_ButtonThreeformCom", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/ShopUI/UI%d.png", TEX_NORMAL, 2)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_LevelLaserCom", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/ShopUI/Level%d.png", TEX_NORMAL, 2)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_HeavyCom", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/ShopUI/Level%d.png", TEX_NORMAL, 2)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_RailGunCom", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/ShopUI/RailGun.png", TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_BurstModeCom", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/ShopUI/RailGun.png", TEX_NORMAL)), E_FAIL);
		FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_UpgradeStringCom", CTexture::Create(m_pGraphicDev, L"../Bin/Resources/UI/ShopUI/UIupgrade.png", TEX_NORMAL)), E_FAIL);
	}

	m_bFinish = true;

	return 0;
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
