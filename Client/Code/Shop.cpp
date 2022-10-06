#include "stdafx.h"
#include "..\Header\Shop.h"
#include "Export_Function.h"
#include "Uzi.h"
#include "Shotgun.h"
#include "CubePlayer.h"
CShop::CShop(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}


CShop::~CShop()
{
}

HRESULT CShop::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"UziRaffle", L"Roboto-Bold", 20, 20, FW_NORMAL), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"ShotGun", L"Roboto-Bold", 20, 20, FW_NORMAL), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"Sniper", L"Roboto-Bold", 20, 20, FW_NORMAL), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"Upgrade", L"Roboto-Bold", 20, 20, FW_NORMAL), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"Information", L"Roboto-Bold", 15, 17, FW_NORMAL), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"LASER MODE", L"Roboto-Bold", 10, 10, FW_NORMAL), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"HEAVY MODE", L"Roboto-Bold", 10, 10, FW_NORMAL), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"RAILGUN MODE", L"Roboto-Bold", 10, 10, FW_NORMAL), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"BURST MODE", L"Roboto-Bold", 10, 10, FW_NORMAL), E_FAIL);
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	
	D3DXMatrixOrthoLH(&m_matProj, WINCX, WINCY, 0.f, 1.f);

	//ShopView
	{	fScale = 2.f;
		_vec3 vPos = _vec3(610.f, 490.f, 0.f);
		_float fWidth = (_float)m_pTextureform->Get_ImageInfo().Width;
		_float fHeight = (_float)m_pTextureform->Get_ImageInfo().Height;
		m_TranformCom->Set_Pos(vPos.x - WINCX * 0.5f, -vPos.y + WINCY * 0.5f, 0.f);
		m_TranformCom->Set_Scale(fWidth * fScale, fHeight * fScale * 1.5f, 1.f);
	}

	//UZI

	{	fScale2 = 6.f;
		_vec3 vPos = _vec3(400.f, 320.f, 0.f);
		_float fWidth = (_float)m_pUziTextureform->Get_ImageInfo().Width;
		_float fHeight = (_float)m_pUziTextureform->Get_ImageInfo().Height;
		m_pUziTransformCom->Set_Pos(vPos.x - WINCX * 0.5f, -vPos.y + WINCY * 0.5f, 0.f);
		m_pUziTransformCom->Set_Scale(fWidth *fScale2, fHeight * fScale2, 1.f);
	}

	//ShotGun
	{
		fScale11 = 4.f;
		_vec3 vPos = _vec3(400.f, 320.f, 0.f);
		_float fWidth = (_float)m_pShotGunTextureform->Get_ImageInfo().Width;
		_float fHeight = (_float)m_pShotGunTextureform->Get_ImageInfo().Height;
		m_pShotGunformCom->Set_Pos(vPos.x - WINCX * 0.5f, -vPos.y + WINCY * 0.5f, 0.f);
		m_pShotGunformCom->Set_Scale(fWidth * fScale11, fHeight * fScale11, 1.f);
	}
	
	//Sniper
	{
		fScale12 = 4.f;
		_vec3 vPos = _vec3(400.f, 320.f, 0.f);
		_float fWidth = (_float)m_pSniperTextureform->Get_ImageInfo().Width;
		_float fHeight = (_float)m_pSniperTextureform->Get_ImageInfo().Height;
		m_pSniperformCom->Set_Pos(vPos.x - WINCX * 0.5f, -vPos.y + WINCY * 0.5f, 0.f);
		m_pSniperformCom->Set_Scale(fWidth * fScale12, fHeight * fScale12, 1.f);
	}


	//button
	if (m_pButtonOneform || m_eWeaponButton == BUTTON_ONE)
	{
		fScale3 = 2.f;
		m_vPos_ButtonOne = _vec3(300.f, 135.f, 0.f);
		_float fWidth = (_float)m_pButtonOneform->Get_ImageInfo().Width;
		_float fHeight = (_float)m_pButtonOneform->Get_ImageInfo().Height;
		m_pButtonTransformCom->Set_Pos(m_vPos_ButtonOne.x - WINCX * 0.5f, -m_vPos_ButtonOne.y + WINCY * 0.5f, 0.f);
		m_pButtonTransformCom->Set_Scale(fWidth * fScale3, fHeight * fScale3, 1.f);
	}

	//button(shotgun)
	if (m_pButtonTwoform || m_eWeaponButton == BUTTON_TWO)
	{
		fScale4 = 2.f;
		m_vPos_ButtonTwo = _vec3(600.f, 135.f, 0.f);
		_float fWidth = (_float)m_pButtonTwoform->Get_ImageInfo().Width;
		_float fHeight = (_float)m_pButtonTwoform->Get_ImageInfo().Height;
		m_pShotGunTransformCom->Set_Pos(m_vPos_ButtonTwo.x - WINCX * 0.5f, -m_vPos_ButtonTwo.y + WINCY * 0.5f, 0.f);
		m_pShotGunTransformCom->Set_Scale(fWidth * fScale4, fHeight * fScale4, 1.f);
	}
	//button(Sniper)
	if (m_pButtonThreeform || m_eWeaponButton == BUTTON_THREE)
	{
		fScale5 = 2.f;
		m_vPos_ButtonThree = _vec3(900.f, 135.f, 0.f);
		_float fWidth = (_float)m_pButtonThreeform->Get_ImageInfo().Width;
		_float fHeight = (_float)m_pButtonThreeform->Get_ImageInfo().Height;
		m_pSniperTransformCom->Set_Pos(m_vPos_ButtonThree.x - WINCX * 0.5f, -m_vPos_ButtonThree.y + WINCY * 0.5f, 0.f);
		m_pSniperTransformCom->Set_Scale(fWidth* fScale5, fHeight * fScale5, 1.f);
	}
	//Upgrade(laser)
	if (m_pLaserRaffle || m_eLevelUP == LEVEL_LASER)
	{
		fScale6 = 2.f;
		m_vPos_ButtonFour = _vec3(940.f, 300.f, 0.f);
		_float fWidth = (_float)m_pLaserRaffle->Get_ImageInfo().Width;
		_float fHeight = (_float)m_pLaserRaffle->Get_ImageInfo().Height;
		m_pLaserTransformCom->Set_Pos(m_vPos_ButtonFour.x - WINCX * 0.5f, -m_vPos_ButtonFour.y + WINCY * 0.5f, 0.f);
		m_pLaserTransformCom->Set_Scale(fWidth * fScale6, fHeight * fScale6, 1.f);
	}
	//Upgrade(HeavyRaffle)
	if (m_pHeavyRaffle || m_eLevelUP == LEVEL_HEAVY)
	{
		fScale7 = 2.f;
		m_vPos_ButtonFive = _vec3(1200.f, 300.f, 0.f);
		_float fWidth = (_float)m_pHeavyRaffle->Get_ImageInfo().Width;
		_float fHeight = (_float)m_pHeavyRaffle->Get_ImageInfo().Height;
		m_pHeavyTransformCom->Set_Pos(m_vPos_ButtonFive.x - WINCX * 0.5f, -m_vPos_ButtonFive.y + WINCY * 0.5f, 0.f);
		m_pHeavyTransformCom->Set_Scale(fWidth * fScale7, fHeight * fScale7, 1.f);
	}
	//Upgrade(RailGun)
	if (m_pRailGunScope || m_eLevelUP == LEVEL_RAIL)
	{
		fScale8 = 2.f;
		m_vPos_ButtonSix = _vec3(940.f, 400.f, 0.f);
		_float fWidth = (_float)m_pRailGunScope->Get_ImageInfo().Width;
		_float fHeight = (_float)m_pRailGunScope->Get_ImageInfo().Height;
		m_pRailGunTransformCom->Set_Pos(m_vPos_ButtonSix.x - WINCX * 0.5f, -m_vPos_ButtonSix.y + WINCY * 0.5f, 0.f);
		m_pRailGunTransformCom->Set_Scale(fWidth * fScale8, fHeight * fScale8, 1.f);
	}

	//Upgrade(BurstMode)
	if (m_pBurstMode || m_eLevelUP == LEVEL_BURST)
	{
		fScale9 = 2.f;
		m_vPos_ButtonSeven = _vec3(1200.f, 400.f, 0.f);
		_float fWidth = (_float)m_pBurstMode->Get_ImageInfo().Width;
		_float fHeight = (_float)m_pBurstMode->Get_ImageInfo().Height;
		m_pBurstModeTransformCom->Set_Pos(m_vPos_ButtonSeven.x - WINCX * 0.5f, -m_vPos_ButtonSeven.y + WINCY * 0.5f, 0.f);
		m_pBurstModeTransformCom->Set_Scale(fWidth * fScale9, fHeight * fScale9, 1.f);
	}
	//
	if (m_pUpgradeString || m_eLevelUP == LEVEL_UPGRADETEXT)
	{
		fScale13 = 2.5f;
		m_vPos_UpgradeTexture = _vec3(1060.f, 220.f, 0.f);
		_float fWidth = (_float)m_pUpgradeString->Get_ImageInfo().Width;
		_float fHeight = (_float)m_pUpgradeString->Get_ImageInfo().Height;
		m_pUpgradeTransformCom->Set_Pos(m_vPos_UpgradeTexture.x - WINCX * 0.5f, -m_vPos_UpgradeTexture.y + WINCY * 0.5f, 0.f);
		m_pUpgradeTransformCom->Set_Scale(fWidth * fScale13, fHeight * fScale13 * 1.2f, 1.f);
	}



	
	m_pUpgrade = L"UPGRADE";
	m_pInformation = L"Press [Return] And Hold to Buy Upgrade";
	m_pUziRaffle = L"UziRaffle";
	m_pShotGun = L"ShotGun";
	m_pSniper = L"Sniper";
	m_pLaser = L"LASER MODE";
	m_pHeavy = L"HEAVY MODE";
	m_pRailGun = L"RAILGUN MODE";
	m_pBurst = L"BURST MODE";
	return S_OK; 

}

_int CShop::Update_Object(const _float & fTimeDelta)
{
	if (m_bShop)
	{
		Add_RenderGroup(RENDER_UI, this);
	}

	Key_Input();
	Engine::CGameObject::Update_Object(fTimeDelta);
	return  0;
}

void CShop::LateUpdate_Object()
{
	CGameObject::LateUpdate_Object();
}

void CShop::Render_Object()
{
	

	if (m_bShop)
	{
		Render_Ortho(m_TranformCom, m_pTextureform);
	}
	{
		Render_Ortho(m_pButtonTransformCom, m_pButtonOneform, 0);
		Render_Ortho(m_pShotGunTransformCom, m_pButtonTwoform, 0);
		Render_Ortho(m_pSniperTransformCom, m_pButtonThreeform, 0);
		Render_Ortho(m_pLaserTransformCom, m_pLaserRaffle, 0);
		Render_Ortho(m_pHeavyTransformCom, m_pHeavyRaffle, 0);
		Render_Ortho(m_pRailGunTransformCom, m_pRailGunScope, 0);
		Render_Ortho(m_pBurstModeTransformCom, m_pBurstMode, 0);
		Render_Ortho(m_pUpgradeTransformCom, m_pUpgradeString, 0);
	}

	if (PointTest(m_vPos_ButtonOne))
	{
		Render_Ortho(m_pButtonTransformCom, m_pButtonOneform, 1);
		m_GunChecking = false;
		if (Get_DIMouseState(DIM_LB) & 0x80)
		{
		
		
		Render_Ortho(m_pUziTransformCom, m_pUziTextureform, 0);
		m_GunChecking = true;
		}
		m_bChecking = true;
	}
	if (PointTest(m_vPos_ButtonTwo))
	{
		Render_Ortho(m_pShotGunTransformCom, m_pButtonTwoform, 1);
		m_GunChecking = false;
		if (Get_DIMouseState(DIM_LB) & 0x80)
		{
			Render_Ortho(m_pShotGunformCom, m_pShotGunTextureform, 0);
			m_GunChecking = true;
	
		}
		m_bChecking = true;
	}
	if (PointTest(m_vPos_ButtonThree))
	{
		Render_Ortho(m_pSniperTransformCom, m_pButtonThreeform, 1);
		m_GunChecking = false;
		if (Get_DIMouseState(DIM_LB) & 0x80)
		{
			Render_Ortho(m_pSniperformCom, m_pSniperTextureform, 0);
			m_GunChecking = true;

		}
		m_bChecking = true;
	}
	if (PointTest(m_vPos_ButtonFour))
	{
		Render_Ortho(m_pLaserTransformCom, m_pLaserRaffle, 1);
		if (Get_DIMouseState(DIM_LB) & 0x80)
			{
			if (m_pLaserRaffle || m_eLevelUP == LEVEL_LASER)
			{
				dynamic_cast<CUzi*>(Engine::Get_GameObject(STAGE_GUN, L"UZI1"))->Get_UziUpgrade();
				m_bChecking = true;
			}
		}
		m_bChecking = true;
	}
	if (PointTest(m_vPos_ButtonFive))
	{
		Render_Ortho(m_pHeavyTransformCom, m_pHeavyRaffle, 1);
		m_bChecking = true;
	}
	if (PointTest(m_vPos_ButtonSix))
	{
		Render_Ortho(m_pRailGunTransformCom, m_pRailGunScope, 1);
		m_bChecking = true;
	}
	if (PointTest(m_vPos_ButtonSeven))
	{
		Render_Ortho(m_pBurstModeTransformCom, m_pBurstMode, 1);
		m_bChecking = true;
	}

	Render_Font(L"Upgrade", m_pUpgrade.c_str(), &_vec2(1020.f, 215.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	Render_Font(L"Information", m_pInformation.c_str(), &_vec2(750.f, 560.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	Render_Font(L"UziRaffle", m_pUziRaffle.c_str(), &_vec2(260.f, 125.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	Render_Font(L"ShotGun", m_pShotGun.c_str(), &_vec2(560.f, 125.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	Render_Font(L"Sniper", m_pSniper.c_str(), &_vec2(880.f, 125.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	Render_Font(L"LASER MODE", m_pLaser.c_str(), &_vec2(920.f, 293.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	Render_Font(L"HEAVY MODE", m_pHeavy.c_str(), &_vec2(1190.f, 293.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	Render_Font(L"RAILGUN MODE", m_pRailGun.c_str(), &_vec2(910.f, 397.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	Render_Font(L"BURST MODE", m_pBurst.c_str(), &_vec2(1170.f, 397.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
}

void CShop::Key_Input()
{
	if (Get_DIKeyState(DIK_K))
	{
		CRenderer::GetInstance()->On_Shop();
		m_bShop = false;

	}
	if (Get_DIKeyState(DIK_L))
	{
		CRenderer::GetInstance()->Off_Shop();
		m_bShop = true;

	}
}

void CShop::Render_Ortho(CTransform * pTransform, CTexture * pTexture, _int iIndex)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, pTransform->Get_WorldMatrixPointer());

	_matrix		OldViewMatrix, OldProjMatrix;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &OldViewMatrix);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &OldProjMatrix);

	_matrix		ViewMatrix;

	ViewMatrix = *D3DXMatrixIdentity(&ViewMatrix);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &ViewMatrix);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);

	pTexture->Set_Texture(iIndex);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &OldViewMatrix);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &OldProjMatrix);
}

HRESULT CShop::Add_Component(void)
{

	CComponent * pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_RcTexCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTexCom", pComponent });

	pComponent = m_pTextureform = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_ShopTextureCom"));
	NULL_CHECK_RETURN(m_pTextureform, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_ShopTextureCom", pComponent });

	pComponent = m_pUziTextureform = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_UziTextureCom"));
	NULL_CHECK_RETURN(m_pUziTextureform, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_UziTextureCom", pComponent });

	pComponent = m_pShotGunTextureform = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_ShotGunTextureCom"));
	NULL_CHECK_RETURN(m_pShotGunTextureform, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_ShotGunTextureCom", pComponent });

	pComponent = m_pSniperTextureform = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_SniperTextureCom"));
	NULL_CHECK_RETURN(m_pSniperTextureform, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_SniperTextureCom", pComponent });

	//b1
	pComponent = m_pButtonOneform = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_ButtonOneformCom"));
	NULL_CHECK_RETURN(m_pButtonOneform, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_ButtonOneformCom", pComponent });
	//b2
	pComponent = m_pButtonTwoform = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_ButtonTwoformCom"));
	NULL_CHECK_RETURN(m_pButtonTwoform, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_ButtonTwoformCom", pComponent });
	//b3
	pComponent = m_pButtonThreeform = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_ButtonThreeformCom"));
	NULL_CHECK_RETURN(m_pButtonThreeform, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_ButtonThreeformCom", pComponent });



	//Levelup
	pComponent = m_pLaserRaffle = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_LevelLaserCom"));
	NULL_CHECK_RETURN(m_pLaserRaffle, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_LevelLaserCom", pComponent });

	pComponent = m_pHeavyRaffle = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_HeavyCom"));
	NULL_CHECK_RETURN(m_pHeavyRaffle, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_HeavyCom", pComponent });

	pComponent = m_pRailGunScope = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_RailGunCom"));
	NULL_CHECK_RETURN(m_pRailGunScope, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RailGunCom", pComponent });

	pComponent = m_pBurstMode = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_BurstModeCom"));
	NULL_CHECK_RETURN(m_pBurstMode, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_BurstModeCom", pComponent });

	pComponent = m_pUpgradeString = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_UpgradeStringCom"));
	NULL_CHECK_RETURN(m_pUpgradeString, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_UpgradeStringCom", pComponent });



	pComponent = m_TranformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_TranformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	pComponent = m_pUziTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pUziTransformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"UZI_TransformCom", pComponent });

	pComponent = m_pShotGunformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pShotGunformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Shotgun_TransformCom", pComponent });

	pComponent = m_pSniperformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pSniperformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Sniper_TransformCom", pComponent });


	pComponent = m_pButtonTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pButtonTransformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"ButtonOne_TransformCom", pComponent });

	pComponent = m_pShotGunTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pShotGunTransformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"ButtonTwo_TransformCom", pComponent });
	
	
	pComponent = m_pSniperTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pSniperTransformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"ButtonThree_TransformCom", pComponent });

	pComponent = m_pLaserTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pLaserTransformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"ButtonFour_TransformCom", pComponent });

	pComponent = m_pHeavyTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pHeavyTransformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"ButtonFive_TransformCom", pComponent });

	pComponent = m_pRailGunTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pRailGunTransformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"ButtonSix_TransformCom", pComponent });

	pComponent = m_pBurstModeTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pBurstModeTransformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"ButtonSeven_TransformCom", pComponent });
	
	pComponent = m_pUpgradeTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pUpgradeTransformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"UpgradeTexture_TransformCom", pComponent });
	
	return S_OK;
}

_bool CShop::PointMouse(const _vec3& vPos)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	_long lLeft, lRight, lUp, lDown;

	lLeft = _long((0.5 * WINCX) * (1 + m_TranformCom->m_vInfo[INFO_POS].x ) - (m_TranformCom->m_vScale.x  * (0.5 * WINCX)));
	lRight = _long((0.5 * WINCX) * (1 + m_TranformCom->m_vInfo[INFO_POS].x) + (m_TranformCom->m_vScale.x   * (0.5 * WINCX)));
	lUp = _long((0.5 * WINCY) * (1 - m_TranformCom->m_vInfo[INFO_POS].y) - (m_TranformCom->m_vScale.y  * (WINCY * 0.5)));
	lDown = _long((0.5 * WINCY) * (1 - m_TranformCom->m_vInfo[INFO_POS].y) + (m_TranformCom->m_vScale.y  * (WINCY * 0.5)));

	RECT rc = { lLeft, lUp, lRight, lDown };

	if (PtInRect(&rc, pt))
	{
		return true;
	}

	return false;
}

_bool CShop::PointTest(const _vec3& vPos)
{
	POINT rt;
	GetCursorPos(&rt);
	ScreenToClient(g_hWnd, &rt);

	RECT	rcUI = { _long((vPos.x) + 45.f  - (_float)m_pButtonOneform->Get_ImageInfo().Width * 1.5f),
					_long((vPos.y)  - (_float)m_pButtonOneform->Get_ImageInfo().Height)  ,
					_long((vPos.x ) + 45.f + (_float)m_pButtonOneform->Get_ImageInfo().Width * 1.5f)   ,
					_long((vPos.y) + (_float)m_pButtonOneform->Get_ImageInfo().Height )  };

	if (PtInRect(&rcUI, rt))
	{
		return true;
	}

	return false;
}

CShop * CShop::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CShop* pInstance = new CShop(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CShop::Free()
{
	CGameObject::Free();

}