#include "stdafx.h"
#include "..\Header\TestGun.h"


CTestGun::CTestGun(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CTestGun::~CTestGun()
{
}

HRESULT CTestGun::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CTestGun::Update_Object(const _float & fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);
	m_pTransCom->Set_Pos(2.f, 2.f, 2.f);
	m_pTransCom->Set_Rotation(ROT_Z, D3DXToRadian(-90.f));
	Add_RenderGroup(RENDER_NONALPHA, this);
	return 0;
}

void CTestGun::LateUpdate_Object(void)
{
}

void CTestGun::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pTexture->Set_Texture(0);
	m_pBufferCom->Render_Buffer();
}

HRESULT CTestGun::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CDynamicBuffer*>(Clone_Proto(L"DynamicBuffer"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"DynamicBuffer", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });

	pComponent = m_pTexture = dynamic_cast<CTexture*>(Clone_Proto(L"DynamicBuffer_Tex"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"DynamicBuffer_Tex", pComponent });

	return S_OK;
}

CTestGun * CTestGun::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTestGun* pInstance = new CTestGun(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CTestGun::Free(void)
{
	CGameObject::Free();
}
