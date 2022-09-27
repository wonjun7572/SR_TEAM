#include "stdafx.h"
#include "..\Header\ShotgunPart4.h"


CShotgunPart4::CShotgunPart4(LPDIRECT3DDEVICE9 pGraphicDev)
	:CWeapon(pGraphicDev)
{
}

CShotgunPart4::~CShotgunPart4()
{
}

HRESULT CShotgunPart4::Ready_Object(void)
{
	
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_pTransform->Set_Scale(.8f*1.5f, .15f*1.5f, .21f);
	

	return S_OK;
}

_int CShotgunPart4::Update_Object(const _float & fTimeDelta)
{
	Add_RenderGroup(RENDER_NONALPHA, this);
	CGameObject::Update_Object(fTimeDelta);

	//cout << m_fShotgunSize << endl;
	//cout << m_fUziSize << endl;

	return 0;
}

void CShotgunPart4::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CShotgunPart4::Render_Object(void)
{

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	m_pTexture->Set_Texture(45);
	m_pCube->Render_Buffer();
}

HRESULT CShotgunPart4::Add_Component(void)
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

CShotgunPart4 * CShotgunPart4::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CShotgunPart4* pInstance = new CShotgunPart4(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);


	return pInstance;
}

void CShotgunPart4::Free(void)
{
	CGameObject::Free();
}


