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

	return S_OK;
}

_int CWeaponUI::Update_Object(const _float & fTimeDelta)
{
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
	Begin_OrthoProj();
	m_pTextureCom->Set_Texture(0);
	m_pBufferCom->Render_Buffer();
	End_OrthoProj();
}

void CWeaponUI::Begin_OrthoProj()
{
	_matrix matWorld, matView, matProj, matOrtho;
	m_pGraphicDev->GetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	memcpy(&m_matWorld, &matWorld, sizeof(_matrix));
	memcpy(&m_matView, &matView, sizeof(_matrix));
	memcpy(&m_matProj, &matProj, sizeof(_matrix));

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	matView.m[0][0] = 260.f; // 이미지 가로
	matView.m[1][1] = 65.f; // 이미지 세로
	matView.m[2][2] = 1.f;
	matView.m[3][0] = m_pTransCom->m_vInfo[INFO_POS].x + 541.f;
	matView.m[3][1] = m_pTransCom->m_vInfo[INFO_POS].y - 395.f;

	D3DXMatrixOrthoLH(&matOrtho, WINCX, WINCY, 0.f, 1.f);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matOrtho);
}

void CWeaponUI::End_OrthoProj()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);
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
	CWeaponUI *	pInstance = new CWeaponUI(pGraphicDev);

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
