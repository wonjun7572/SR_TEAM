#include "stdafx.h"
#include "..\Header\MiddleBoss.h"
#include "PoolMgr.h"
#include "ObtainBullet.h"
#include "ObtainDefense.h"
#include "HealthPotion.h"
#include "MonsterUI.h"
#include "CubePlayer.h"
#include "Weapon.h"
#include "ComboUI.h"
#include "MonsterMapping.h"

static _int m_iCnt = 0;

CMiddleBoss::CMiddleBoss(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}


CMiddleBoss::~CMiddleBoss()
{
}

HRESULT CMiddleBoss::Ready_Object(const _vec3 & vPos)
{
	m_tAbility = new MIDDLEBOSSABILITY;
	m_tAbility->fMaxHp = 200.f;
	m_tAbility->fCurrentHp = m_tAbility->fMaxHp;
	m_tAbility->fDamage = 5.f;
	m_tAbility->strObjTag = L"MiddleBoss";
	m_fDetectRange = 10.f;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	//크기 설정 및 위치설정.
	m_pTransCom->Set_Scale(&_vec3(2.f, 6.f, 1.f));
	m_pTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
	m_pTransCom->Static_Update();

	m_eCurPattern = MIDDLE_IDLE;

	//UI가져와야하고 
	m_pTransUICom->Set_Scale(2.f, 1.f, 1.5f);
	

	//애니메이션 넣으려면 나중에 이쪽에 넣어주어야한다. 
	m_pHitBoxTransCom->Set_Scale(&_vec3(1.2f, 1.2f, 1.2f));
	m_pHitBoxTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
	m_pHitBoxTransCom->Static_Update();

	m_pSphereTransCom->Set_Scale(&_vec3(20.f, 20.f, 20.f));
	m_pSphereTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
	m_pSphereTransCom->Static_Update();




	return S_OK;
}

_int CMiddleBoss::Update_Object(const _float & fTimeDelta)
{

	if (m_bDead)
	{
		_float fMiddle_death = 1.5f;
		PlaySoundGun(L"Middle_Death.wav", SOUND_EFFECT, fMiddle_death);
		m_eCurPattern = MIDDLE_DEATH;
		Create_Item();
		m_pComboUI->KillCntPlus();
		Monster_DeleteMapping();
		return -1;
	}
	Update_Pattern(fTimeDelta);
	
	

	CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_NONALPHA, this);
	m_pTransUICom->Billboard_Transform(fTimeDelta);
	Hit_Check(fTimeDelta);

	_vec3 vMonsterPos;
	m_pTransCom->Get_Info(INFO_POS, &vMonsterPos);
	m_pHitBoxTransCom->Set_Pos(vMonsterPos.x, vMonsterPos.y, vMonsterPos.z);
	m_pSphereTransCom->Set_Pos(vMonsterPos.x, vMonsterPos.y, vMonsterPos.z);
	m_pTransCom->Get_Info(INFO_POS, &vUIPos);
	m_pTransUICom->Set_Pos(vUIPos.x, vUIPos.y + 1.4f, vUIPos.z);
	return 0;
}

void CMiddleBoss::LateUpdate_Object(void)
{
	Monster_Mapping();

	if (m_tAbility->fCurrentHp <= 0.f)
	{
		m_pMonsterUI->Off_Switch();
		this->Kill_Obj();
	}
	CGameObject::LateUpdate_Object();
}


void CMiddleBoss::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pTextureCom->Set_Texture(10);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pHitBoxTransCom->Get_WorldMatrixPointer());
	m_pHitBox->Render_Buffer();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pSphereTransCom->Get_WorldMatrixPointer());

	m_pSphereBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransUICom->Get_WorldMatrixPointer());

	m_pTextureUICom->Set_Texture(0);
	m_pBufferUICom->Resize_Buffer(m_tAbility->fCurrentHp / m_tAbility->fMaxHp);
	m_pBufferUICom->Render_Buffer();
}

void CMiddleBoss::Change_Pattern(HP_Pattern ePattern)
{
	m_eCurPattern = ePattern;
	if (m_ePrePattern != m_eCurPattern)
	{
		m_ePrePattern = m_eCurPattern;
	}

}

_int CMiddleBoss::Update_Pattern(_float fTimeDelta)
{


	if (m_pPlayerTransCom == nullptr)
	{
		m_pPlayerTransCom = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_CHARACTER, L"PLAYER", TRANSFORM_COMP, ID_DYNAMIC));
	}
	if (m_pMonsterUI == nullptr)
		m_pMonsterUI = dynamic_cast<CMonsterUI*>(Engine::Get_GameObject(STAGE_UI, L"MonsterUI"));
	if (m_pComboUI == nullptr)
		m_pComboUI = dynamic_cast<CComboUI*>(Engine::Get_GameObject(STAGE_UI, L"ComboUI"));
	
	
	_vec3 vPlayerPos;
	m_pPlayerTransCom->Get_Info(INFO_POS, &vPlayerPos);
	_vec3 vPlayerScale;
	m_pPlayerTransCom->Get_Scale(&vPlayerScale);
	_vec3 vScale;
	m_pSphereTransCom->Get_Scale(&vScale);
	_vec3 vPos;
	m_pTransCom->Get_Info(INFO_POS, &vPos);
	_vec3 m_vDir;
	m_vDir = vPlayerPos - vPos;
	_float m_fPlayerCurrent = D3DXVec3Length(&m_vDir);

	_float HP = m_tAbility->fCurrentHp / m_tAbility->fMaxHp;
	if (m_fDetectRange >= m_fTargetLength && m_eCurPattern != MIDDLE_DEATH)
	{
		if (HP >= 0.9f)
		{
	
			if (m_pCollision->Sphere_Collision(this->m_pSphereTransCom, m_pPlayerTransCom, vPlayerScale.x, vScale.x) && m_fFrame < 2.f)
			{//패턴1
				m_pTransCom->Chase_Target(&vPlayerPos, 1.f, fTimeDelta);
				m_eCurPattern = MIDDLE_WALK;
			}
		}
		else if (HP >= 0.6f)
		{


			_vec3 vDir{ 1.f, 0.f, 0.f };
			if (m_pCollision->Sphere_Collision(this->m_pSphereTransCom, m_pPlayerTransCom, vPlayerScale.x, vScale.x) && m_fFrame < 2.f)
			{//패턴2


				m_eCurPattern = MIDDLE_ATTACK_1;
				CPoolMgr::GetInstance()->Reuse_Obj(m_pGraphicDev, &vPos, &m_vDir, m_tAbility->fDamage);

			}
		}
		else if (HP >= 0.01f)
		{
			//패턴3

			D3DXVECTOR3		vDir{ 1.f, 0.f, 0.f };
			if (m_pCollision->Sphere_Collision(this->m_pSphereTransCom, m_pPlayerTransCom, vPlayerScale.x, vScale.x))
			{
			m_eCurPattern = MIDDLE_ATTACK_2;
				m_pTransCom->Chase_Target(&vPlayerPos, 1.f, fTimeDelta);
				m_fFrame += fTimeDelta;
				_matrix matRotY, matTrans, matWorld;

				if (m_fFrame >= 1.f)
				{
					for (m_fFireAngle = 0.f; m_fFireAngle < 360.f; m_fFireAngle += 2)
					{
						D3DXMatrixRotationY(&matRotY, D3DXToRadian(-m_fFireAngle));
						D3DXMatrixTranslation(&matTrans, vPos.x, 0.f, vPos.y);

						m_pTransCom->Get_WorldMatrix(&matWorld);
						matWorld = matRotY * matTrans;

						D3DXVec3TransformNormal(&vDir, &vDir, &matWorld);

						CPoolMgr::GetInstance()->Reuse_Obj(m_pGraphicDev, &vPos, &vDir, m_tAbility->fDamage);
					}
					m_fFrame = 0.f;
				}
			}
			

		}
		
	}
	return 0;
}

void CMiddleBoss::Hit_Check(_float _deltaTime)
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

HRESULT CMiddleBoss::Create_Item()
{
	CGameObject*		pGameObject = nullptr;
	_vec3 vItemPos;
	m_pTransCom->Get_Info(INFO_POS, &vItemPos);

	srand((unsigned int)time(NULL));
	_int iRand = rand() % 3;

	switch (iRand)
	{
	case 0:
		pGameObject = CHealthPotion::Create(m_pGraphicDev, vItemPos);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		Get_Layer(STAGE_ITEM)->Add_GameList(pGameObject);
		break;

	case 1:
		pGameObject = CObtainBullet::Create(m_pGraphicDev, vItemPos);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		Get_Layer(STAGE_ITEM)->Add_GameList(pGameObject);
		break;

	case 2:
		pGameObject = CObtainDefense::Create(m_pGraphicDev, vItemPos);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		Get_Layer(STAGE_ITEM)->Add_GameList(pGameObject);
		break;
	}

	return S_OK;
}

HRESULT CMiddleBoss::Monster_Mapping(void)
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

HRESULT CMiddleBoss::Monster_DeleteMapping(void)
{
	Delete_GameObject(STAGE_MAPPING, m_szCntName);

	return S_OK;
}


HRESULT CMiddleBoss::Add_Component(void)
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

	pComponent = m_pHitBoxTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"HitBox_Transform", pComponent });


	pComponent = m_pTransUICom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransUICom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformUICom", pComponent });

	pComponent = m_pBufferUICom = dynamic_cast<CRcTex*>(Clone_Proto(RCTEX_MONTER_HP_COMP));
	NULL_CHECK_RETURN(m_pBufferUICom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ RCTEX_MONTER_HP_COMP, pComponent });

	pComponent = m_pTextureUICom = dynamic_cast<CTexture*>(Clone_Proto(L"Monster_General_HP"));
	NULL_CHECK_RETURN(m_pTextureUICom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Monster_General_HP", pComponent });


	pComponent = m_pSphereBufferCom = dynamic_cast<CSphereTex*>(Clone_Proto(SPHERETEX_COMP));
	NULL_CHECK_RETURN(m_pSphereBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ SPHERETEX_COMP, pComponent });

	pComponent = m_pSphereTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pSphereBufferCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Sphere_TransCom", pComponent });

	return S_OK;
}

CMiddleBoss * CMiddleBoss::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos)
{
	CMiddleBoss * pInstance = new CMiddleBoss(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CMiddleBoss::Free(void)
{
	CGameObject::Free();
}
