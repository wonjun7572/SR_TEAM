#include "stdafx.h"
#include "..\Header\Zombie.h"
#include "CubePlayer.h"
#include "Weapon.h"
#include "HealthPotion.h"

CZombie::CZombie(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev)
{
}

CZombie::~CZombie()
{
}

HRESULT CZombie::Ready_Object(const _vec3& vPos, wstring _strObjTag)
{
	// 수치 값 넣어주기
	m_tAbility->iLevel = 0;
	m_tAbility->fMaxHp = 100.f;
	m_tAbility->fCurrentHp = m_tAbility->fMaxHp;
	m_tAbility->fDamage = 0.f;
	m_tAbility->strObjName = _strObjTag;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	
	m_pTransCom->Set_Scale(&_vec3(0.3f, 0.3f, 0.3f));
	m_pTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
	m_pTransUICom->Set_Scale(1.f, 0.1f, 0.f);
	
	return S_OK;
}

_int CZombie::Update_Object(const _float & fTimeDelta)
{
	if (m_bDead)
	{
		CGameObject*		pGameObject = nullptr;
		_vec3 vItemPos;
		m_pTransCom->Get_Info(INFO_POS, &vItemPos);
		pGameObject = CHealthPotion::Create(m_pGraphicDev, vItemPos);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		wstring strHpItem;
		strHpItem = m_tAbility->strObjName + L"HP";
		Engine::Add_GameObject(STAGE_ITEM, pGameObject, strHpItem.c_str());
		return -1;
	}

	CMonster::Update_Object(fTimeDelta);
	return 0;
}

void CZombie::LateUpdate_Object(void)
{
	CMonster::LateUpdate_Object();
}

void CZombie::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pTextureCom->Set_Texture(16);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pHitBox->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransUICom->Get_WorldMatrixPointer());
	m_pTextureUICom->Set_Texture(0);
	m_pBufferUICom->Resize_Buffer(m_tAbility->fCurrentHp / m_tAbility->fMaxHp);
	m_pBufferUICom->Render_Buffer();
}


HRESULT CZombie::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CCubeTex*>(Clone_Proto(L"Proto_CubeTexCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubeTexCom", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_CubePlayerTexture"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubePlayerTexture", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });

	pComponent = m_pHitBox = dynamic_cast<CHitBox*>(Engine::Clone_Proto(HITBOX_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ HITBOX_COMP, pComponent });

	pComponent = m_pCollision = dynamic_cast<CCollision*>(Engine::Clone_Proto(COLLISION_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ COLLISION_COMP, pComponent });

	// FOR UI
	pComponent = m_pTransUICom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransUICom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformUICom", pComponent });

	pComponent = m_pBufferUICom = dynamic_cast<CRcTex*>(Clone_Proto(RCTEX_MONTER_HP_COMP));
	NULL_CHECK_RETURN(m_pBufferUICom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ RCTEX_MONTER_HP_COMP, pComponent });

	pComponent = m_pTextureUICom = dynamic_cast<CTexture*>(Clone_Proto(L"Monster_HP"));
	NULL_CHECK_RETURN(m_pTextureUICom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Monster_HP", pComponent });

	return S_OK;
}

CZombie * CZombie::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos, wstring _strObjTag)
{
	CZombie *	pInstance = new CZombie(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(vPos, _strObjTag)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CZombie::Free(void)
{
	CMonster::Free();
}
