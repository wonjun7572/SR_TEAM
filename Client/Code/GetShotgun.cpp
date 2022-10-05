#include "stdafx.h"
#include "..\Header\GetShotgun.h"
#include "CubePlayer.h"

CGetShotgun::CGetShotgun(LPDIRECT3DDEVICE9 pGraphicDev)
	: CItem(pGraphicDev)
{
}

CGetShotgun::~CGetShotgun()
{
}

HRESULT CGetShotgun::Ready_Object(const _vec3 & vPos)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_pTransCom->Set_Scale(1.f, 1.f, 1.f);
	m_pTransCom->Set_Rotation(ROT_Z, D3DXToRadian(270.f));
	m_pTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
	m_pTransCom->Static_Update();

	m_pHitBoxTransCom->Set_Scale(0.5f, 0.5f, 0.5f);
	m_pHitBoxTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
	m_pHitBoxTransCom->Static_Update();

	return S_OK;
}

_int CGetShotgun::Update_Object(const _float & fTimeDelta)
{
	if (m_bDead)
	{
		dynamic_cast<CCubePlayer*>(Engine::Get_GameObject(L"Layer_Character", L"PLAYER"))->Capture_Shotgun();
		return -1;
	}
	
	CItem::Move_Item(fTimeDelta);
	CItem::Update_Object(fTimeDelta);
	
	return 0;
}

void CGetShotgun::LateUpdate_Object()
{
	CItem::LateUpdate_Object();
}

void CGetShotgun::Render_Object()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pTextureCom->Set_Texture(0);
	m_pDBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DPMISCCAPS_CULLNONE);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pHitBoxTransCom->Get_WorldMatrixPointer());
	m_pHitBox->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DPMISCCAPS_CULLCCW);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

HRESULT CGetShotgun::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pDBufferCom = dynamic_cast<CDynamicBuffer*>(Clone_Proto(L"SHOTGUN_ITEM"));
	NULL_CHECK_RETURN(m_pDBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"SHOTGUN_ITEM", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"SHOTGUN_ITEM_TEX"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"SHOTGUN_ITEM_TEX", pComponent });
	
	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	pComponent = m_pHitBox = dynamic_cast<CHitBox*>(Clone_Proto(L"Proto_HitboxCom"));
	NULL_CHECK_RETURN(m_pHitBox, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_HitboxCom", pComponent });

	pComponent = m_pHitBoxTransCom = dynamic_cast<CTransform*>(Clone_Proto(L"ITEM_HITBOX_TransformCom"));
	NULL_CHECK_RETURN(m_pHitBoxTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"ITEM_HITBOX_TransformCom", pComponent });

	pComponent = m_pCalculatorCom = dynamic_cast<CCalculator*>(Clone_Proto(L"Proto_CalculatorCom"));
	NULL_CHECK_RETURN(m_pCalculatorCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CalculatorCom", pComponent });

	return S_OK;
}

CGetShotgun * CGetShotgun::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos)
{
	CGetShotgun* pInstance = new CGetShotgun(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(vPos)))
	{
		MSG_BOX("GetShotgun Item Create Fail");
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CGetShotgun::Free()
{
	CItem::Free();
}
