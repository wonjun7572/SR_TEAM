#include "stdafx.h"
#include "..\Header\CubeHand.h"

CCubeHand::CCubeHand(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CCubeHand::~CCubeHand()
{
}

HRESULT CCubeHand::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransform->Set_Scale(0.5f, 1.f, 0.5f);

	return S_OK;
}

_int CCubeHand::Update_Object(const _float & fTimeDelta)
{
	Add_RenderGroup(RENDER_NONALPHA, this);

	CGameObject::Update_Object(fTimeDelta);

	return 0;
}

void CCubeHand::LateUpdate_Object(void)
{
	Key_Input(0.1f);

	CGameObject::LateUpdate_Object();
}

void CCubeHand::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	m_pTexture->Set_Texture(0);
	m_pCube->Render_Buffer();
}

void CCubeHand::Key_Input(const _float & fTimeDelta)
{
}

HRESULT CCubeHand::Add_Component(void)
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
	m_mapComponent[ID_STATIC].insert({ L"Proto_TransformCom", pInstance });

	return S_OK;
}

CCubeHand * CCubeHand::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCubeHand* pInstance = new CCubeHand(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CCubeHand::Free(void)
{
	CGameObject::Free();
}