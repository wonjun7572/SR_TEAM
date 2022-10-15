#include "stdafx.h"
#include "..\Header\Alien.h"
#include "ComboUI.h"
#include "HealthPotion.h"
#include "ObtainDefense.h"
#include "ObtainBullet.h"
CAlien::CAlien(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev)
{
}


CAlien::~CAlien()
{
}

HRESULT CAlien::Ready_Object(const _vec3 & vPos, _tchar * Name)
{
	m_tAbility = new MONSTERABILITY;
	m_tAbility->iLevel = 0;
	m_tAbility->fMaxHp = 100.f;
	m_tAbility->fCurrentHp = m_tAbility->fMaxHp;
	m_tAbility->fDamage = 20.f;
	m_tAbility->strObjTag = L"Alien";

	m_MonsterName = Name;


	m_STATE = ALIEN_IDLE;
	m_BeforeState = ALIEN_IDLE;
	m_WALK = ALIENWALK_START;
	m_ATTACK = ALIENATTACK_START;
	m_IDLE = ALIENIDLE_1;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


	m_pTransCom->Set_Scale(0.3f, 0.3f, 0.3f);
	m_pTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
	m_pTransCom->Static_Update();


	m_pTransUICom->Set_Scale(1.0f, 0.1f, 0.f);

	m_pHitBoxTransCom->Set_Scale(&_vec3(0.3f, 0.3f, 0.3f));
	m_pHitBoxTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
	m_pHitBoxTransCom->Static_Update();

	m_pSphereTransCom->Set_Scale(&_vec3(10.f, 10.f, 10.f));
	m_pSphereTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
	m_pSphereTransCom->Static_Update();

	//Å½Áö¹üÀ§ 
	m_pSearchRange_TransCom->Set_Scale(&_vec3(20.f, 20.f, 20.f));
	m_pSearchRange_TransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
	m_pSearchRange_TransCom->Static_Update();



	m_pAttackRange_TransCom->Set_Scale(&_vec3(17.f, 17.f, 17.f));
	m_pAttackRange_TransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
	m_pAttackRange_TransCom->Static_Update();


	m_pRunawayRange_TransCom->Set_Scale(&_vec3(7.f, 7.f, 7.f));
	m_pRunawayRange_TransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
	m_pRunawayRange_TransCom->Static_Update();

	

	return S_OK;
}

_int CAlien::Update_Object(const _float & fTimeDelta)
{
	if (m_bDead)
	{
		m_pComboUI->KillCntPlus();
		Create_Item();
		Monster_DeleteMapping();

		return -1;
	}

	m_fTimeDelta = fTimeDelta;

	CMonster::Update_Object(fTimeDelta);

	_vec3 vPlayerPos;
	m_pPlayerTransCom->Get_Info(INFO_POS, &vPlayerPos);

	_vec3 vPlayerScale;
	m_pPlayerTransCom->Get_Scale(&vPlayerScale);

	_vec3 vScale;
	m_pSphereTransCom->Get_Scale(&vScale);

	_vec3 vSearchScale, vAttackScale, vRunScale;
	m_pSearchRange_TransCom->Get_Scale(&vSearchScale);
	m_pAttackRange_TransCom->Get_Scale(&vAttackScale);
	m_pRunawayRange_TransCom->Get_Scale(&vRunScale);



	_vec3 vPos;
	m_pTransCom->Get_Info(INFO_POS, &vPos);
	_vec3 vDir;
	vDir = vPlayerPos - vPos;
	D3DXVec3Normalize(&vDir, &vDir);

	
	if (!Collision_Wall(fTimeDelta))
	{
		if (m_pCollision->Sphere_Collision(this->m_pRunawayRange_TransCom, m_pPlayerTransCom, vPlayerScale.x, vRunScale.x))
		{
			m_pTransCom->Chase_Target(&vPlayerPos, -5.f, fTimeDelta);
			m_STATE = ALIEN_WALK;
		}
		else if (m_pCollision->Sphere_Collision(this->m_pAttackRange_TransCom, m_pPlayerTransCom, vPlayerScale.x, vAttackScale.x))
		{
			m_pTransCom->Chase_Target(&vPlayerPos, 0.f, fTimeDelta);
			m_STATE = ALIEN_ATTACK;

		}
	}

	m_fFrame += fTimeDelta;


	CMonster::Update_Object(fTimeDelta);
	return 0;
}

void CAlien::LateUpdate_Object(void)
{
	Monster_Mapping();


	CMonster::LateUpdate_Object();
}

void CAlien::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pTextureCom->Set_Texture(11);
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

HRESULT CAlien::Add_Component(void)
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

	// FOR HITBOX
	pComponent = m_pHitBox = dynamic_cast<CHitBox*>(Engine::Clone_Proto(HITBOX_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ HITBOX_COMP, pComponent });

	pComponent = m_pCollision = dynamic_cast<CCollision*>(Engine::Clone_Proto(COLLISION_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ COLLISION_COMP, pComponent });

	pComponent = m_pHitBoxTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"HitBox_Transform", pComponent });

	// FOR UI
	pComponent = m_pTransUICom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransUICom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformUICom", pComponent });

	pComponent = m_pBufferUICom = dynamic_cast<CRcTex*>(Clone_Proto(RCTEX_MONTER_HP_COMP));
	NULL_CHECK_RETURN(m_pBufferUICom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ RCTEX_MONTER_HP_COMP, pComponent });

	pComponent = m_pTextureUICom = dynamic_cast<CTexture*>(Clone_Proto(L"Monster_General_HP"));
	NULL_CHECK_RETURN(m_pTextureUICom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Monster_General_HP", pComponent });

	// For Sphere
	pComponent = m_pSphereBufferCom = dynamic_cast<CSphereTex*>(Clone_Proto(SPHERETEX_COMP));
	NULL_CHECK_RETURN(m_pSphereBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ SPHERETEX_COMP, pComponent });

	pComponent = m_pSphereTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pSphereBufferCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Sphere_TransCom", pComponent });



	//Å½Áö °ø°Ý µµ¸Á ¹üÀ§
	pComponent = m_pSearchRange_TransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pSphereBufferCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"SearchRange", pComponent });

	pComponent = m_pAttackRange_TransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pSphereBufferCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"AttackRange", pComponent });

	pComponent = m_pRunawayRange_TransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pSphereBufferCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"RunawayRange", pComponent });


	return S_OK;
}

HRESULT CAlien::Create_Item(void)
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

CAlien * CAlien::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos, _tchar * Name)
{
	CAlien* pInstance = new CAlien(pGraphicDev);

	if (FAILED(pInstance ->Ready_Object(vPos, Name)))
	{
		Safe_Release(pInstance);
		return nullptr;

	}

	return pInstance;
}

void CAlien::Free(void)
{
	CMonster::Free();
}
