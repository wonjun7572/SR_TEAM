#include "stdafx.h"
#include "..\Header\GetSniper.h"
#include "CubePlayer.h"

CGetSniper::CGetSniper(LPDIRECT3DDEVICE9 pGraphicDev)
	: CItem(pGraphicDev)
{
}

CGetSniper::~CGetSniper()
{
}

HRESULT CGetSniper::Ready_Object(const _vec3 & vPos)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_pTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
	m_pTransCom->Set_Scale(1.f, 1.f, 1.f);
	m_pTransCom->Static_Update();
	return S_OK;
}

_int CGetSniper::Update_Object(const _float & fTimeDelta)
{
	if (m_bDead)
	{
		dynamic_cast<CCubePlayer*>(Engine::Get_GameObject(L"Layer_Character", L"PLAYER"))->Capture_Sniper();
		return -1;
	}

	CItem::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_NONALPHA, this);
	return 0;
}

void CGetSniper::LateUpdate_Object()
{
	CItem::LateUpdate_Object();
}

void CGetSniper::Render_Object()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pTextureCom->Set_Texture(0);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DPMISCCAPS_CULLNONE);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//m_pHitBox->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DPMISCCAPS_CULLCCW);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

HRESULT CGetSniper::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CSphereTex*>(Clone_Proto(L"Proto_SphereTexCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_SphereTexCom", pComponent });

	pComponent = m_pHitBox = dynamic_cast<CHitBox*>(Clone_Proto(L"Proto_HitboxCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_HitboxCom", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_PlayerTexture"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_PlayerTexture", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	pComponent = m_pCalculatorCom = dynamic_cast<CCalculator*>(Clone_Proto(L"Proto_CalculatorCom"));
	NULL_CHECK_RETURN(m_pCalculatorCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CalculatorCom", pComponent });

	return S_OK;
}

CGetSniper * CGetSniper::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos)
{
	CGetSniper* pInstance = new CGetSniper(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(vPos)))
	{
		MSG_BOX("GetSniper Item Create Fail");
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CGetSniper::Free()
{
	CItem::Free();
}
