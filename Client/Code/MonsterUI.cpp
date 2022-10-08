#include "stdafx.h"
#include "..\Header\MonsterUI.h"
#include "CubePlayer.h"
#include "Weapon.h"

CMonsterUI::CMonsterUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CMonsterUI::~CMonsterUI()
{
}

HRESULT CMonsterUI::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	D3DXMatrixOrthoLH(&m_matProj, WINCX, WINCY, 0.f, 1.f);
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"MonsterName", L"Roboto-Bold", 20, 15, FW_NORMAL), E_FAIL);
	
	m_fX = 0.f;
	m_fY = -300.f;
	m_fSizeX = 400.f;
	m_fSizeY = 20.f;

	m_fSizeHUDX = 410.f;
	m_fSizeHUDY = 31.f;
	return S_OK;
}

_int CMonsterUI::Update_Object(const _float & fTimeDelta)
{
	_int iResult = CGameObject::Update_Object(fTimeDelta);

	if (m_bSwitch)
	{
		m_pTransCom->Set_Scale(m_fSizeX, m_fSizeY, 1.f);
		m_pTransCom->Set_Pos(m_fX, -m_fY, 0.f);

		m_pHUDTransCom->Set_Scale(m_fSizeHUDX, m_fSizeHUDY, 1.f);
		m_pHUDTransCom->Set_Pos(m_fX, -m_fY, 0.f);
	
		m_strHp = to_wstring(_uint(m_fHp));
		m_strMaxHp = to_wstring(_uint(m_fMaxHp));

		Add_RenderGroup(RENDER_UI, this);
	}
	
	return iResult;
}

void CMonsterUI::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
	m_strMonsterUI = m_strObjName + L" ( " + m_strHp + L"/" + m_strMaxHp + L" ) ";
}

void CMonsterUI::Render_Object(void)
{
	_matrix      OldViewMatrix, OldProjMatrix, ViewMatrix;

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pHUDTransCom->Get_WorldMatrixPointer());
	
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &OldViewMatrix);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &OldProjMatrix);

	ViewMatrix = *D3DXMatrixIdentity(&ViewMatrix);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &ViewMatrix);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);
	
	m_pHUDTextureCom->Set_Texture();
	m_pHUDBufferCom->Render_Buffer();

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &OldViewMatrix);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &OldProjMatrix);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &OldViewMatrix);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &OldProjMatrix);

	ViewMatrix = *D3DXMatrixIdentity(&ViewMatrix);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &ViewMatrix);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);

	m_pTextureCom->Set_Texture();
	m_pBufferCom->Resize_Buffer(m_fHp / m_fMaxHp);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &OldViewMatrix);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &OldProjMatrix);

	Render_Font(L"MonsterName", m_strMonsterUI.c_str(), &_vec2(630.f, 120.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
}

CMonsterUI * CMonsterUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMonsterUI* pInstance = new CMonsterUI(pGraphicDev);
	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CMonsterUI::Free(void)
{
	CGameObject::Free();
}

HRESULT CMonsterUI::Add_Component()
{
	CComponent* pComponent = nullptr;
	
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(RCTEX_GENERAL_MONSTER_HP_COMP));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ RCTEX_GENERAL_MONSTER_HP_COMP, pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(MONSTER_HP_TEX));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Monsetr_HP" , pComponent });

	pComponent = m_pHUDBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(RCTEX_GENERAL_MONSTER_HUD_COMP));
	NULL_CHECK_RETURN(m_pHUDBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ RCTEX_GENERAL_MONSTER_HUD_COMP, pComponent });

	pComponent = m_pHUDTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pHUDTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Monster_HUD_Trans", pComponent });

	pComponent = m_pHUDTextureCom = dynamic_cast<CTexture*>(Clone_Proto(MONSTER_HP_HUD_TEX));
	NULL_CHECK_RETURN(m_pHUDTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Monsetr_HP_HUD" , pComponent });

	return S_OK;
}
