#include "stdafx.h"
#include "..\Header\HealthPotion.h"

#include "CubePlayer.h"

CHealthPotion::CHealthPotion(LPDIRECT3DDEVICE9 pGraphicDev)
	: CItem(pGraphicDev)
{
}

CHealthPotion::~CHealthPotion()
{
}

HRESULT CHealthPotion::Ready_Object(const _vec3& vPos)
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

Engine::_int CHealthPotion::Update_Object(const _float& fTimeDelta)
{
	if (m_bDead)
	{
		dynamic_cast<CCubePlayer*>(Engine::Get_GameObject(STAGE_CHARACTER, L"PLAYER"))->Get_Hp();
		return -1;
	}

	CItem::Move_Item(fTimeDelta);
	CItem::Update_Object(fTimeDelta);

	return 0;
}

void CHealthPotion::LateUpdate_Object()
{
	CItem::LateUpdate_Object();
}

void CHealthPotion::Render_Object()
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

HRESULT CHealthPotion::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pDBufferCom = dynamic_cast<CDynamicBuffer*>(Clone_Proto(ADDHP_ITEM_BUFFER));
	NULL_CHECK_RETURN(m_pDBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ ADDHP_ITEM_BUFFER, pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(ADDHP_ITEM_TEX));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ ADDHP_ITEM_TEX, pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });

	pComponent = m_pHitBox = dynamic_cast<CHitBox*>(Clone_Proto(HITBOX_COMP));
	NULL_CHECK_RETURN(m_pHitBox, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ HITBOX_COMP, pComponent });

	pComponent = m_pHitBoxTransCom = dynamic_cast<CTransform*>(Clone_Proto(ITEM_TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pHitBoxTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ ITEM_TRANSFORM_COMP, pComponent });

	pComponent = m_pCalculatorCom = dynamic_cast<CCalculator*>(Clone_Proto(CALCULATOR_COMP));
	NULL_CHECK_RETURN(m_pCalculatorCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ CALCULATOR_COMP, pComponent });

	return S_OK;
}

CHealthPotion * CHealthPotion::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos)
{
	CHealthPotion* pInstance = new CHealthPotion(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CHealthPotion::Free()
{
	CItem::Free();
}
