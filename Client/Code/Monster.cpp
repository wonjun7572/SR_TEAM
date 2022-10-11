#include "stdafx.h"
#include "..\Header\Monster.h"
#include "CubePlayer.h"
#include "Weapon.h"
#include "MonsterParticle.h"
#include "MonsterUI.h"
#include "MonsterMapping.h"

static _int m_iCnt = 0;



CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
	
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
	
	if (m_pPlayerTransCom == nullptr)
		m_pPlayerTransCom = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_CHARACTER, L"PLAYER", TRANSFORM_COMP, ID_DYNAMIC));

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

HRESULT CMonster::Monster_Mapping(void)
{
	_vec3		vPos;
	m_pHitBoxTransCom->Get_Info(INFO_POS, &vPos);
	if (!m_MappingInit)
	{
		CGameObject*	m_pMapMonster = CMonsterMapping::Create(m_pGraphicDev);
		wsprintf(m_szCntName, L"");
		const _tchar*	szNumbering = L"MapMonster_%d";
		wsprintf(m_szCntName, szNumbering, m_iCnt);
		Engine::Add_GameObject(STAGE_MAPPING, m_pMapMonster, m_szCntName);
		m_listMonsterCnt.push_back(m_szCntName);

		m_pMonsterMapping = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_MAPPING, m_szCntName, TRANSFORM_COMP, ID_DYNAMIC));
		NULL_CHECK_RETURN(m_pMonsterMapping, E_FAIL);
		++m_iCnt;
		m_MappingInit = true;
		
	}
	m_pMonsterMapping->Set_Pos(vPos.x, vPos.y, vPos.z);	
	return S_OK;
	
}

HRESULT CMonster::Monster_DeleteMapping(void)
{
	Delete_GameObject(STAGE_MAPPING, m_szCntName);
	
	return S_OK;
}

void CMonster::Hit_Effect()
{
	_vec3 vPos;
	m_pTransCom->Get_Info(INFO_POS, &vPos);
	if (!m_pHitParicle)
		m_pHitParicle = dynamic_cast<CMonsterParticle*>(Engine::Get_GameObject(STAGE_ENVIRONMENT, L"MonsterParticle"));

	m_pHitParicle->Set_PclePos(vPos);
	m_pHitParicle->addParticle();
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
				Hit_Effect();
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
			if (m_fUISwitchTime >= 5.f)
			{
				m_pMonsterUI->Off_Switch();
				m_fUISwitchTime = 0.f;
			}
		}
	} 
}

void CMonster::Free(void)
{
	for (auto& iter : m_listMonsterCnt)
	{
		if (iter != nullptr)
			delete iter;
	}

	m_listMonsterCnt.clear();
	CGameObject::Free();
}
