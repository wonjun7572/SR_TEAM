#include "stdafx.h"
#include "..\Header\LoadingBar.h"

CLoadingBar::CLoadingBar(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CLoadingBar::~CLoadingBar(void)
{
}

HRESULT CLoadingBar::Ready_Object()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	
	if (m_fMin >= 0)
	{
		Power_On();
		m_bPower = true;
	}
	return S_OK;
}

_int CLoadingBar::Update_Object(const _float & fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_UI, this);

	return 0;
}

void CLoadingBar::LateUpdate_Object(void)
{
	if (m_fMax <= 100.f)
	{
		Power_Off();
		m_bPower = false;
		this->Kill_Obj();

	}
	CGameObject::LateUpdate_Object();
}

void CLoadingBar::Render_Object(void)
{
	Begin_OrthoProj();
	m_pUITextureCom->Set_Texture();
	m_pBufferUICom->Resize_Buffer(m_fMin / m_fMax);
	m_pBufferUICom->Render_Buffer();
	End_OrthoProj();
	
	
	Begin_HudOrthoProj();
	m_pHUDTextureCom->Set_Texture();
	m_pHUDBufferCom->Render_Buffer();
	End_HudOrthoProj();
}

HRESULT CLoadingBar::Add_Component(void)
{

	CComponent* pComponent = nullptr;


	//loading
	pComponent = m_pBufferUICom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_LoadingBar"));
	NULL_CHECK_RETURN(m_pBufferUICom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_LoadingBar", pComponent });
	
	pComponent = m_pUITransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pUITransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });

	pComponent = m_pUITextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_ReadyLoading"));
	NULL_CHECK_RETURN(m_pUITextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_ReadyLoading", pComponent });
	
	

	//Hud
	pComponent = m_pHUDBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_HudLoading"));
	NULL_CHECK_RETURN(m_pHUDBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_HudLoading", pComponent });


	pComponent = m_pHUDTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pHUDTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"TRANSFORM_COMP2", pComponent });

	pComponent = m_pHUDTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_HudLoadinga"));
	NULL_CHECK_RETURN(m_pHUDTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_HudLoadinga", pComponent });


	
	
	return S_OK;
}

void CLoadingBar::Begin_OrthoProj()
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

	matView.m[0][0] = 400.f; // 이미지 가로
	matView.m[1][1] = 150.f; // 이미지 세로
	matView.m[2][2] = 1.f;
	matView.m[3][0] = m_pUITransCom->m_vInfo[INFO_POS].x;
	matView.m[3][1] = m_pUITransCom->m_vInfo[INFO_POS].y;

	D3DXMatrixOrthoLH(&matOrtho, WINCX, WINCY, 0.f, 1.f);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matOrtho);
}

void CLoadingBar::End_OrthoProj()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);

}

void CLoadingBar::Begin_HudOrthoProj()
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

	matView.m[0][0] = 400; // 이미지 가로
	matView.m[1][1] = 150.f; // 이미지 세로
	matView.m[2][2] = 1.f;
	matView.m[3][0] = m_pHUDTransCom->m_vInfo[INFO_POS].x;
	matView.m[3][1] = m_pHUDTransCom->m_vInfo[INFO_POS].y;

	D3DXMatrixOrthoLH(&matOrtho, WINCX, WINCY, 0.f, 1.f);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matOrtho);
}

void CLoadingBar::End_HudOrthoProj()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

CLoadingBar * CLoadingBar::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLoadingBar* pInstance = new CLoadingBar(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CLoadingBar::Free(void)
{
	CGameObject::Free();
}
