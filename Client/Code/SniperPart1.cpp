#include "stdafx.h"
#include "..\Header\SniperPart1.h"


CSniperPart1::CSniperPart1(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CSniperPart1::~CSniperPart1()
{
}

HRESULT CSniperPart1::Ready_Object(void)
{

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_pTransform->Set_Scale(.8f*1.5f, .1f*1.5f, .2f);

	return S_OK;
}

_int CSniperPart1::Update_Object(const _float & fTimeDelta)
{
	Add_RenderGroup(RENDER_NONALPHA, this);
	CGameObject::Update_Object(fTimeDelta);

	return 0;
}

void CSniperPart1::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CSniperPart1::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	m_pTexture->Set_Texture(1);
	m_pCube->Render_Buffer();
}

HRESULT CSniperPart1::Add_Component(void)
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

CSniperPart1 * CSniperPart1::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSniperPart1* pInstance = new CSniperPart1(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);


	return pInstance;
}

void CSniperPart1::Free(void)
{
	CGameObject::Free();
}


