#include "stdafx.h"
#include "..\Header\TargetCube.h"
#include "CubePlayer.h"
#include "Weapon.h"

CTargetCube::CTargetCube(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}

CTargetCube::~CTargetCube()
{
}

HRESULT CTargetCube::Ready_Object(const _vec3& vPos)
{
	m_tAbility = new MONSTERABILITY;
	
	m_tAbility->iLevel = 0;
	m_tAbility->fMaxHp = 20.f;
	m_tAbility->fCurrentHp = m_tAbility->fMaxHp;
	m_tAbility->fDamage = 0.f;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransCom->Set_Scale(&_vec3(0.3f,0.3f,0.3f));
	m_pTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);

	return S_OK;
}

_int CTargetCube::Update_Object(const _float & fTimeDelta)
{
	m_fFrame += fTimeDelta;

	if(m_bReFresh)
	{
		//m_tAbility->fCurrentHp = m_tAbility->fMaxHp;
		m_fFrame = 0.f;
		m_bReFresh = false;
	}

	if (m_fFrame >= 5.f)
	{
		Engine::CGameObject::Update_Object(fTimeDelta);
		Add_RenderGroup(RENDER_NONALPHA, this);
		Hit_Check();

	}
	
	return 0;
}

void CTargetCube::LateUpdate_Object(void)
{
	if (m_tAbility->fCurrentHp <= 0.f)
	{
		this->Kill_Obj();
	}
}

void CTargetCube::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pTextureCom->Set_Texture(13);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pHitBox->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

HRESULT CTargetCube::Add_Component(void)
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

	return S_OK;
}

void CTargetCube::Hit_Check(void)
{
	m_pTransCom->Static_Update();

	CCubePlayer* pPlayer = dynamic_cast<CCubePlayer*>(Engine::Get_GameObject(STAGE_CHARACTER, L"PLAYER"));
	CWeapon* pWeapon = pPlayer->Get_Weapon();
	if (pWeapon)
	{
		_vec3 vSrcPos;
		pWeapon->Get_Transform()->Get_Info(INFO_POS, &vSrcPos);

		_vec3 vDir;
		if (m_pCollision->HitScan(g_hWnd, &vSrcPos, this->m_pBufferCom, this->m_pTransCom, &vDir))
		{
			if (pWeapon->Get_Shoot() == true)
			{
				m_tAbility->fCurrentHp -= pWeapon->Get_Ability()->fBulletAttack;
				cout << "HP: " << m_tAbility->fCurrentHp << "\n";
				pWeapon->Set_Shoot(false);
			}

			if (m_tAbility->fCurrentHp < 0.f)
			{
				m_tAbility->fCurrentHp = 0.f;
				m_bReFresh = true;
			}
		}
	}
}

CTargetCube * CTargetCube::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos)
{
	CTargetCube *	pInstance = new CTargetCube(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CTargetCube::Free(void)
{
	Safe_Delete<MONSTERABILITY*>(m_tAbility);
	CGameObject::Free();
}
