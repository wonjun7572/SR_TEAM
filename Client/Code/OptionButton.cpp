#include "stdafx.h"
#include "..\Header\OptionButton.h"
#include "Export_Function.h"



COptionButton::COptionButton(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}


COptionButton::~COptionButton()
{
}

HRESULT COptionButton::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);



	m_pTransformCom->Set_Scale(0.1f, 0.1f, 0.f);
	m_pTransformCom->Set_Pos(0.65f, 0.45f, 0.f);
	return S_OK;
}

_int COptionButton::Update_Object(const _float & fTimeDelta)
{

	Engine::CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_UI, this);

	return 0;
}

void COptionButton::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void COptionButton::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrixPointer());
	m_pTextureCom->Set_Texture(0);
	m_pRcTexCom->Render_Buffer();

}

HRESULT COptionButton::Add_Component(void)
{

	CComponent* pComponent = nullptr;
	pComponent = m_pRcTexCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_RcTexCom"));
	NULL_CHECK_RETURN(m_pRcTexCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTexCom", pComponent });


	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_OptionButton"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_OptionButton", pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });


	return S_OK;
}

COptionButton * COptionButton::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	COptionButton* pInstance = new COptionButton(pGraphicDev);
	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void COptionButton::Free(void)
{
	CGameObject::Free();
}
