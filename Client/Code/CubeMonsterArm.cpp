
#include "stdafx.h"
#include "..\Header\CubeMonsterArm.h"


CCubeMonsterArm::CCubeMonsterArm(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}


CCubeMonsterArm::~CCubeMonsterArm()
{
}

HRESULT CCubeMonsterArm::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_component(), E_FAIL);

	m_pTransform->Set_Scale(0.5f, 0.5f, 1.5f);

	return S_OK;
}

_int CCubeMonsterArm::Update_Object(const _float & fTimeDelta)
{



	Add_RenderGroup(RENDER_NONALPHA, this);

	CGameObject::Update_Object(fTimeDelta);


	return 0;
}

void CCubeMonsterArm::LateUpdate_Object(void)
{

}

void	CCubeMonsterArm::Render_Object(void)
{

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	m_pTexture->Set_Texture(0);
	m_pCubeTexture->Render_Buffer();
}


HRESULT CCubeMonsterArm::Add_component(void)
{
	CComponent* pComponent = nullptr;


	pComponent = m_pTexture = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_CubeMonsterTexture"));
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubeMonsterTexture", pComponent });

	pComponent = m_pCubeTexture = dynamic_cast<CCubeTex*>(Clone_Proto(L"Proto_CubeTexCom"));
	NULL_CHECK_RETURN(m_pCubeTexture, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_CubeTexCom", pComponent });

	pComponent = m_pTransform = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransform, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	return S_OK;
}

CCubeMonsterArm * CCubeMonsterArm::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{

	CCubeMonsterArm* pInstance = new CCubeMonsterArm(pGraphicDev);
	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCubeMonsterArm::Free(void)
{
	CGameObject::Free();
}
