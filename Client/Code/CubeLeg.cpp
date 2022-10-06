#include "stdafx.h"
#include "..\Header\CubeLeg.h"

CCubeLeg::CCubeLeg(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CCubeLeg::~CCubeLeg()
{
}

HRESULT CCubeLeg::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransform->Set_Scale(0.05f, 0.1f, 0.05f);

	return S_OK;
}

_int CCubeLeg::Update_Object(const _float & fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);

	Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CCubeLeg::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CCubeLeg::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	m_pTexture->Set_Texture(0);
	m_pCube->Render_Buffer();
}

HRESULT CCubeLeg::Add_Component(void)
{
	CComponent* pInstance = nullptr;

	pInstance = m_pCube = dynamic_cast<CCubeTex*>(Engine::Clone_Proto(L"Proto_CubeTexCom"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubeTexCom", pInstance });

	pInstance = m_pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_CubePlayerTexture"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubePlayerTexture", pInstance });

	pInstance = m_pTransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pInstance });

	return S_OK;
}

CCubeLeg * CCubeLeg::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCubeLeg* pInstance = new CCubeLeg(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CCubeLeg::Free(void)
{
	CGameObject::Free();
}
