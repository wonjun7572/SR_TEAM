#include "stdafx.h"
#include "..\Header\UziPart4.h"
#include "Uzi.h"

CUziPart4::CUziPart4(LPDIRECT3DDEVICE9 pGraphicDev)
	:CWeapon(pGraphicDev)
{
}

CUziPart4::~CUziPart4()
{
}

HRESULT CUziPart4::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_pTransform->Set_Scale(.02f, .02f, .06f);

	return S_OK;
}

_int CUziPart4::Update_Object(const _float & fTimeDelta)
{
	if (dynamic_cast<CUzi*>(Engine::Get_GameObject(L"Layer_Gun", L"UZI1"))->Get_State() ||
		dynamic_cast<CUzi*>(Engine::Get_GameObject(L"Layer_Gun", L"UZI2"))->Get_State())
	{
		Add_RenderGroup(RENDER_NONALPHA, this);
		CGameObject::Update_Object(fTimeDelta);
	}
	return 0;
}

void CUziPart4::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CUziPart4::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	m_pTexture->Set_Texture(47);
	m_pCube->Render_Buffer();
}

HRESULT CUziPart4::Add_Component(void)
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
	//m_mapComponent[ID_STATIC].insert({ L"Proto_TransformCom", pInstance });


	return S_OK;
}

CUziPart4 * CUziPart4::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CUziPart4* pInstance = new CUziPart4(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);


	return pInstance;
}

void CUziPart4::Free(void)
{
	CGameObject::Free();
}
