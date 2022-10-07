#include "stdafx.h"
#include "..\Header\Monster.h"
#include "CubePlayer.h"
#include "Weapon.h"
#include "MonsterUI.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
	m_tAbility = new MONSTERABILITY;
}

CMonster::~CMonster()
{
}

HRESULT CMonster::Ready_Object(const _vec3 & vPos, wstring _strObjTag)
{
	return S_OK;
}

_int CMonster::Update_Object(const _float & fTimeDelta)
{
	if(m_pMonsterUI == nullptr)
		m_pMonsterUI = dynamic_cast<CMonsterUI*>(Engine::Get_GameObject(STAGE_UI, L"MonsterUI"));
	
	_vec3 vUIPos;
	m_pTransCom->Get_Info(INFO_POS, &vUIPos);
	m_pTransUICom->Set_Pos(vUIPos.x, vUIPos.y + 0.5f, vUIPos.z);

	Engine::CGameObject::Update_Object(fTimeDelta);
	m_pTransUICom->Billboard_Transform(fTimeDelta);
	Add_RenderGroup(RENDER_NONALPHA, this);
	Hit_Check(fTimeDelta);

	return 0;
}

void CMonster::LateUpdate_Object(void)
{
	if (m_tAbility->fCurrentHp <= 0.f)
	{
		m_pMonsterUI->Off_Switch();
		this->Kill_Obj();
	}
}

void CMonster::Render_Object(void)
{
}

void CMonster::Hit_Check(_float _deltaTime)
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
			m_pMonsterUI->Set_Name(m_tAbility->strObjTag);
			m_pMonsterUI->Set_Hp(m_tAbility->fCurrentHp);
			m_pMonsterUI->Set_MaxHp(m_tAbility->fMaxHp);
			m_pMonsterUI->On_Switch();
			if (pWeapon->Get_Shoot() == true)
			{
				m_tAbility->fCurrentHp -= pWeapon->Get_Ability()->fBulletAttack;
				pWeapon->Set_Shoot(false);
			}

			if (m_tAbility->fCurrentHp <= 0.f)
			{
				m_tAbility->fCurrentHp = 0.f;
			}
		}
		else
		{
			m_fUISwitchTime += _deltaTime;
			if (m_fUISwitchTime >= 2.f)
			{
				m_pMonsterUI->Off_Switch();
				m_fUISwitchTime = 0.f;
			}
		}
	} 
}

void CMonster::Free(void)
{
	Safe_Delete<MONSTERABILITY*>(m_tAbility);
	CGameObject::Free();
}
