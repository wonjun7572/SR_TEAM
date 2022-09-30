#include "stdafx.h"
#include "..\Header\HealthPotion.h"


CHealthPotion::CHealthPotion(LPDIRECT3DDEVICE9 pGraphicDev)
	: CItem(pGraphicDev)
{
}

CHealthPotion::CHealthPotion(const CGameObject & rhs)
	: CItem(rhs)
{
}

CHealthPotion::~CHealthPotion()
{
}


HRESULT CHealthPotion::Ready_Object(const _vec3& vPos)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_pTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
	m_pTransCom->Set_Scale(2.f, 2.f, 2.f);
	return S_OK;
}

Engine::_int CHealthPotion::Update_Object(const _float& fTimeDelta)
{
	CItem::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_NONALPHA, this);
	return 0;
}

void CHealthPotion::LateUpdate_Object()
{
	CItem::LateUpdate_Object();
}

void CHealthPotion::Render_Object()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pTextureCom->Set_Texture(0);
	m_pBufferCom->Render_Buffer();
}

HRESULT CHealthPotion::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CSphereTex*>(Clone_Proto(L"Proto_SphereTexCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_SphereTexCom", pComponent });

	// 변경해줘야함
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_PlayerTexture"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_PlayerTexture", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	pComponent = m_pCalculatorCom = dynamic_cast<CCalculator*>(Clone_Proto(L"Proto_CalculatorCom"));
	NULL_CHECK_RETURN(m_pCalculatorCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CalculatorCom", pComponent });

	return S_OK;
}

CHealthPotion * CHealthPotion::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos)
{
	CHealthPotion* pInstance = new CHealthPotion(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CHealthPotion::Free()
{
	CItem::Free();
}
