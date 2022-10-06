#include "stdafx.h"
#include "..\Header\LoadBar.h"
#include "Export_Function.h"

CLoadBar::CLoadBar(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CLoadBar::~CLoadBar()
{
}

HRESULT CLoadBar::Ready_Object()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(0.5f, 0.1f, 0.f);
	m_pTransformCom->Set_Pos(0.f, -0.5f, 0.f);

	RECT rc{ m_tRect.left, m_tRect.top, m_tRect.left, m_tRect.bottom };
	m_tRect.bottom = _long(0.05);
	m_tRect.top = _long(0.05);
	m_tRect.left = _long(0.5);
	m_tRect.right = _long(0.5);

	//로딩 비율값 구해주기 
	LoadingRate = (CurrentLoading / OriginLoading);
	m_fNewHeight = _float(m_tRect.left) + _float(m_tRect.right);

	return S_OK;
}

_int CLoadBar::Update_Object(const _float & fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_UI, this);
	return 0;
}

void CLoadBar::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CLoadBar::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrixPointer());
	m_pTextureCom->Set_Texture(0);
	m_pRcTexCom->Render_Buffer();
}

HRESULT CLoadBar::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, m_pTransformCom });

	pComponent = m_pRcTexCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_RcTexCom"));
	NULL_CHECK_RETURN(m_pRcTexCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTexCom", m_pRcTexCom });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_LoadingTexCom"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_LoadingTexCom", m_pTextureCom });

	return S_OK;
}

CLoadBar * CLoadBar::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLoadBar* pInstance = new CLoadBar(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CLoadBar::Free(void)
{
	CGameObject::Free();
}
