#include "stdafx.h"
#include "..\Header\UziPart1.h"


CUziPart1::CUziPart1(LPDIRECT3DDEVICE9 pGraphicDev)
	:CWeapon(pGraphicDev)
{
}

CUziPart1::~CUziPart1()
{
}

HRESULT CUziPart1::Ready_Object(void)
{
	
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_pTransform->Set_Scale(.3f, .1f, .2f) ;

	return S_OK;
}

_int CUziPart1::Update_Object(const _float & fTimeDelta)
{
	Add_RenderGroup(RENDER_NONALPHA, this);
	CGameObject::Update_Object(fTimeDelta);

	return 0;
}

void CUziPart1::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CUziPart1::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	m_pTexture->Set_Texture(0);
	m_pCube->Render_Buffer();
}

HRESULT CUziPart1::Add_Component(void)
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

CUziPart1 * CUziPart1::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CUziPart1* pInstance = new CUziPart1(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);


	return pInstance;
}

void CUziPart1::Free(void)
{
	CGameObject::Free();
}


