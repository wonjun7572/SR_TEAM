#include "stdafx.h"
#include "..\Header\CubeBody.h"

CCubeBody::CCubeBody(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CCubeBody::~CCubeBody()
{
}

HRESULT CCubeBody::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransform->Set_Scale(0.1f, 0.2f, 0.05f);
	m_pTransform->Set_Pos(10.f, 10.f, 10.f);

	return S_OK;
}

_int CCubeBody::Update_Object(const _float & fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);

	Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CCubeBody::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CCubeBody::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	m_pTexture->Set_Texture(1);
	m_pCube->Render_Buffer();
}

HRESULT CCubeBody::Add_Component(void)
{
	CComponent* pInstance = nullptr;

	pInstance = m_pCube = dynamic_cast<CCubeTex*>(Engine::Clone_Proto(L"Proto_CubeTexCom"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubeTexCom", pInstance });

	pInstance = m_pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_CubePlayerTexture"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubePlayerTexture", pInstance });

	pInstance = m_pTransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pInstance });

	return S_OK;
}

CCubeBody * CCubeBody::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCubeBody* pInstance = new CCubeBody(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CCubeBody::Free(void)
{
	CGameObject::Free();
}
