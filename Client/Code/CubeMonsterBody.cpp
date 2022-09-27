#include "stdafx.h"
#include "..\Header\CubeMonsterBody.h"


CCubeMonsterBody::CCubeMonsterBody(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}


CCubeMonsterBody::~CCubeMonsterBody()
{
}

HRESULT CCubeMonsterBody::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_component(), E_FAIL);

	m_pTransform->Set_Scale(1.f, 1.5f, 1.f);

	return S_OK;
}

_int CCubeMonsterBody::Update_Object(const _float & fTimeDelta)
{

	Add_RenderGroup(RENDER_NONALPHA, this);

	CGameObject::Update_Object(fTimeDelta);


	return 0;
}

void CCubeMonsterBody::LateUpdate_Object(void)
{	
	/*CTransform*		pPlayerTransformCom = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"BODY", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK(pPlayerTransformCom);
	

	_vec3		vPlayerPos;
	pPlayerTransformCom->Get_Info(INFO_POS, &vPlayerPos);

	m_pTransform->Chase_Target(&vPlayerPos, 1.f, 0.1f);

	CGameObject::LateUpdate_Object();*/
}

void CCubeMonsterBody::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	m_pTexture->Set_Texture(0);
	m_pCubeTexture->Render_Buffer();

}


HRESULT CCubeMonsterBody::Add_component(void)
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
	m_mapComponent[ID_STATIC].insert({ L"Proto_TransformCom", pComponent });

	return S_OK;
}

CCubeMonsterBody * CCubeMonsterBody::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCubeMonsterBody* pInstance = new CCubeMonsterBody(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
	}


	return pInstance;
}

void CCubeMonsterBody::Free(void)
{
	CGameObject::Free();
}
