#include "stdafx.h"
#include "..\Header\WeaponUI.h"

#include "Export_Function.h"

CWeaponUI::CWeaponUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CWeaponUI::~CWeaponUI()
{
}

HRESULT CWeaponUI::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	D3DXMatrixOrthoLH(&m_ProjMatrix, WINCX, WINCY, 0.f, 1.f);

	m_fX = 500.f;
	m_fY = 393.f;
	m_fSizeX = 300.f;
	m_fSizeY = 140.f;
	return S_OK;
}

_int CWeaponUI::Update_Object(const _float & fTimeDelta)
{
	m_pTransCom->Set_Scale(m_fSizeX, m_fSizeY, 1.f);
	m_pTransCom->Set_Pos(m_fX, -m_fY, 0.f);
	_int iResult = CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_UI, this);
	return iResult;
}

void CWeaponUI::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CWeaponUI::Render_Object(void)
{

	m_pTextureCom->Set_Texture(0);


	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());


	_matrix      OldViewMatrix, OldProjMatrix;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &OldViewMatrix);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &OldProjMatrix);

	_matrix      ViewMatrix;

	ViewMatrix = *D3DXMatrixIdentity(&ViewMatrix);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &ViewMatrix);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);
	m_pTextureCom->Set_Texture(0);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &OldViewMatrix);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &OldProjMatrix);
}

HRESULT CWeaponUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_RcTexCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTexCom", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"theHUDui_11"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"theHUDui_11", pComponent });

	return S_OK;
}

CWeaponUI * CWeaponUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWeaponUI *   pInstance = new CWeaponUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CWeaponUI::Free(void)
{
	CGameObject::Free();
}