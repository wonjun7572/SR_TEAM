#include "stdafx.h"
#include "..\Header\GunUI.h"

#include "Export_Function.h"
#include "CubePlayer.h"

CGunUI::CGunUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CGunUI::~CGunUI()
{
}

HRESULT CGunUI::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_iGunIndex = 0;

	return S_OK;
}

_int CGunUI::Update_Object(const _float & fTimeDelta)
{
	_int iResult = CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_UI, this);
	if (m_pPlayer == nullptr)
		m_pPlayer = Engine::Get_GameObject(L"Layer_Character", L"PLAYER");

	if (m_pPlayer != nullptr)
	{
		m_iGunIndex = dynamic_cast<CCubePlayer*>(m_pPlayer)->Get_Ability()->iGunTexture;
	}
	return iResult;
}

void CGunUI::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CGunUI::Render_Object(void)
{
	Begin_OrthoProj();

	if (dynamic_cast<CCubePlayer*>(m_pPlayer)->Get_Weapon() != nullptr)
	{
		m_pTextureCom->Set_Texture(m_iGunIndex);
		m_pBufferCom->Render_Buffer();
	}

	End_OrthoProj();
}

void CGunUI::Begin_OrthoProj()
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

	matView.m[0][0] = 120.f; // 이미지 가로
	matView.m[1][1] = 50.f; // 이미지 세로
	matView.m[2][2] = 1.f;
	matView.m[3][0] = m_pTransCom->m_vInfo[INFO_POS].x + 580.f;
	matView.m[3][1] = m_pTransCom->m_vInfo[INFO_POS].y - 290.f;

	D3DXMatrixOrthoLH(&matOrtho, WINCX, WINCY, 0.f, 1.f);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matOrtho);
}

void CGunUI::End_OrthoProj()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

HRESULT CGunUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_RcTexCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTexCom", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Gun_UI"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Gun_UI", pComponent });

	return S_OK;
}

CGunUI * CGunUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CGunUI*	pInstance = new CGunUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CGunUI::Free(void)
{
	CGameObject::Free();
}
