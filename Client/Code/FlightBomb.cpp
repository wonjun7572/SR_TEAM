#include "stdafx.h"
#include "..\Header\FlightBomb.h"
#include "PoolMgr.h"

CFlightBomb::CFlightBomb(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}


CFlightBomb::~CFlightBomb()
{
}

HRESULT CFlightBomb::Ready_Object(const _vec3 & vPos)
{

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_vPosition = vPos;

	m_pTransCom->Set_Pos(vPos.x, vPos.y -0.2f , vPos.z);

	m_pTransCom->Set_Scale(&_vec3(1.f, 1.f, 1.f));

	
	m_vDirection = { 0.f, -1.f, 0.f };

	return S_OK;
}

_int CFlightBomb::Update_Object(const _float & fTimeDelta)
{

	CGameObject::Update_Object(fTimeDelta);

	Add_RenderGroup(RENDER_NONALPHA, this);
	Bombing();
	return _int();
}

void CFlightBomb::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CFlightBomb::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pTexture->Set_Texture(1);
	m_pSphereTex->Render_Buffer();
}

HRESULT CFlightBomb::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });

	pComponent = m_pSphereTex = dynamic_cast<CSphereTex*>(Engine::Clone_Proto(SPHERETEX_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ SPHERETEX_COMP, pComponent });

	pComponent = m_pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_CubePlayerTexture"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubePlayerTexture", pComponent });

	return S_OK;
}


void CFlightBomb::Bombing(void)
{
	m_pTransCom->Move_Pos(&m_vDirection);

	

}
CFlightBomb * CFlightBomb::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos)
{
	CFlightBomb* pInstance = new CFlightBomb(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(vPos)))
	{
		Safe_Release(pInstance);

		return nullptr;
	}

	return pInstance;
}

void CFlightBomb::Free(void)
{
	CGameObject::Free();
}
