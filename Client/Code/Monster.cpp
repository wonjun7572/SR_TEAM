#include "stdafx.h"
#include "..\Header\Monster.h"
#include "CubePlayer.h"
#include "Weapon.h"
#include "MonsterParticle.h"
#include "MonsterUI.h"
#include "ComboUI.h"
#include "MonsterMapping.h"
#include "Meteor.h"
#include "Flight.h"

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
	m_vDirection = { 0.f, 0.f, 0.f };
	return S_OK;
}

_int CMonster::Update_Object(const _float & fTimeDelta)
{
	if(m_pMonsterUI == nullptr)
		m_pMonsterUI = dynamic_cast<CMonsterUI*>(Engine::Get_GameObject(STAGE_UI, L"MonsterUI"));
	
	if (m_pPlayerTransCom == nullptr)
		m_pPlayerTransCom = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_CHARACTER, L"PLAYER", TRANSFORM_COMP, ID_DYNAMIC));

	if (m_pComboUI == nullptr)
		m_pComboUI = dynamic_cast<CComboUI*>(Engine::Get_GameObject(STAGE_UI, L"ComboUI"));

	_vec3 vUIPos;
	m_pTransCom->Get_Info(INFO_POS, &vUIPos);
	m_pTransUICom->Set_Pos(vUIPos.x, vUIPos.y + 0.5f, vUIPos.z);

	Engine::CGameObject::Update_Object(fTimeDelta);
	m_pTransUICom->Billboard_Transform(fTimeDelta);
	Add_RenderGroup(RENDER_ALPHA, this);
	Hit_Check(fTimeDelta);
	Hit_SphereCheck(fTimeDelta);
	Skill_SphereCheck(fTimeDelta);
	Monster_Mapping();

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

_bool CMonster::Collision_Wall(const _float& fTimeDelta)
{
	_vec3 vPos;
	m_pTransCom->Get_Info(INFO_POS, &vPos);

	_vec3	vDir(0, 0, 0);
	_vec3	vNormal(0, 0, 0);

	_int iCollision = m_pCollision->Wall_Collision_For_Monster(&vNormal,this->m_pTransCom,this->m_pHitBox);

	if (-1 != iCollision)
	{
		float fDot = D3DXVec3Dot(&vNormal, &vDir);
		float fDiagonal = acosf(fDot);

		if (iCollision == WALL_RIGHT || iCollision == WALL_LEFT || iCollision == WALL_BACK)
		{
			if (D3DXToDegree(fDiagonal) > 90.f)
			{
				_vec3 vSliding = vDir;
				m_pCollision->Wall_Collision_By_DotSliding_For_Monster(&vSliding,this->m_pTransCom,this->m_pHitBox);

				m_pTransCom->Move_Pos(&(vSliding * m_fSpeed * fTimeDelta));
			}
			else
			{
				vDir = _vec3 (1, 0, 0);
				m_pTransCom->Move_Pos(&(vDir * m_fSpeed * fTimeDelta));
			}
			return true;
		}
		if (iCollision == WALL_FRONT)
		{
			if (D3DXToDegree(fDiagonal) < 90.f)
			{
				_vec3 vSliding = vDir;
				m_pCollision->Wall_Collision_By_DotSliding_For_Monster(&vSliding, this->m_pTransCom, this->m_pHitBox);

				m_pTransCom->Move_Pos(&(vSliding * m_fSpeed * fTimeDelta));
			}
			else
			{
				vDir = _vec3(-1, 0, 0);
				m_pTransCom->Move_Pos(&(vDir * m_fSpeed * fTimeDelta));
			}
			return true;
		}
	}
	else	
	{
		m_pTransCom->Move_Pos(&(vDir * m_fSpeed * fTimeDelta));
		return false;
	}

	return false;
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
				m_pComboUI->On_Switch();
				m_pComboUI->ComboCntPlus();
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

	//CFlight* pFlight = dynamic_cast<CFlight*>(Engine::Get_GameObject(STAGE_FLIGHTPLAYER, L"FLIGHTPLAYER"));
	//CTransform* pFlightTransform = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_FLIGHTPLAYER, L"FLIGHTPLAYER", TRANSFORM_COMP, ID_DYNAMIC));
	//if (pFlight)
	//{
	//	_vec3 vDir;
	//	if (m_pCollision->HitScan(g_hWnd, &_vec3(0.f, 0.f, 0.f), this->m_pBufferCom, this->m_pTransCom, &vDir))
	//	{
	//		m_pMonsterUI->Set_Name(m_tAbility->strObjTag);
	//		m_pMonsterUI->Set_Hp(m_tAbility->fCurrentHp);
	//		m_pMonsterUI->Set_MaxHp(m_tAbility->fMaxHp);
	//		m_pMonsterUI->On_Switch();
	//		if (pFlight->Get_Shoot() == true)
	//		{
	//			m_tAbility->fCurrentHp -= 20.f;
	//			Hit_Effect();
	//			pFlight->Set_Shoot(false);
	//		}

	//		if (m_tAbility->fCurrentHp <= 0.f)
	//		{
	//			m_tAbility->fCurrentHp = 0.f;
	//		}
	//	}
	//	else
	//	{
	//		m_fUISwitchTime += _deltaTime;
	//		if (m_fUISwitchTime >= 5.f)
	//		{
	//			m_pMonsterUI->Off_Switch();
	//			m_fUISwitchTime = 0.f;
	//		}
	//	}
	//}
}

void CMonster::Hit_SphereCheck(_float _deltaTime)
{
	if (!Get_Layer(STAGE_SKILL)->Get_GameList().empty())
	{
		m_pTransCom->Static_Update();

		for (auto& iter : Get_Layer(STAGE_SKILL)->Get_GameList())
		{
			if (iter->GetSphereSkill() == true)
			{
				if (m_pCollision->Sphere_Collision(this->m_pSphereTransCom, dynamic_cast<CTransform*>(iter->Get_Component(TRANSFORM_COMP, ID_DYNAMIC)), 1.f, iter->GetSphereScale()*2.f))
				{
					m_tAbility->fCurrentHp -= dynamic_cast<CMeteor*>(iter)->Get_Attack();
				}
			}
		}
	}
}

void CMonster::Skill_SphereCheck(_float _deltaTime)
{
	if (!Get_Layer(STAGE_SKILL)->Get_GameList().empty())
	{
		m_pTransCom->Static_Update();
		for (auto& iter : Get_Layer(STAGE_SKILL)->Get_GameList())
		{
			if (iter->GetSphereSkillTag() != 0)
			{
				if (m_pCollision->Sphere_Collision(this->m_pSphereTransCom, dynamic_cast<CTransform*>(iter->Get_Component(TRANSFORM_COMP, ID_DYNAMIC)), 1.f, iter->GetSphereScale()))
				{
					m_iSphereSkillTag = iter->GetSphereSkillTag();
				}
			}
		}
	}
	else
		m_iSphereSkillTag = 0;
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
