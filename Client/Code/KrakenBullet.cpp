#include "stdafx.h"
#include "..\Header\KrakenBullet.h"
#include "PoolMgr.h"
#include "CubePlayer.h"
#include "StaticCamera.h"
#include "HitBarUI.h"
CKrakenBullet::CKrakenBullet(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}


CKrakenBullet::~CKrakenBullet()
{
}

HRESULT CKrakenBullet::Ready_Object(const _vec3 * vPos, const _vec3 * vDir, _float _fSpeed, _float _fDamage)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pKrakenBullet->Set_Scale(2.f, 2.f, 2.f);
	m_pKrakenBullet->m_vInfo[INFO_POS] = *vPos;
	m_pKrakenBullet->Static_Update();


	m_pHitBoxCom->Set_Scale(1.f, 1.f, 1.f);
	m_pHitBoxCom->m_vInfo[INFO_POS] = *vPos;
	m_pHitBoxCom->Static_Update();

	m_vDir = *vDir;
	m_fSpeed = _fSpeed;
	m_fDamage = _fDamage;


	return S_OK;
}

_int CKrakenBullet::Update_Object(const _float & fTimeDelta)
{

	if (m_bDead)
	{
		CPoolMgr::GetInstance()->Collect_KraKenBullet(this);
		return -1;
	}
	CGameObject::Update_Object(fTimeDelta);

	
	D3DXVec3Normalize(&m_vDir, &m_vDir);
	
	m_pKrakenBullet->Move_Pos(&(m_vDir * m_fSpeed * fTimeDelta));

	_vec3 vPos;
	m_pKrakenBullet->Get_Info(INFO_POS, &vPos);
	m_pHitBoxCom->Set_Pos(vPos.x, vPos.y, vPos.z);

	Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CKrakenBullet::LateUpdate_Object(void)
{
	Collision_Check();
	CGameObject::LateUpdate_Object();
}

void CKrakenBullet::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pKrakenBullet->Get_WorldMatrixPointer());
	m_pTexture->Set_Texture(47);
	m_pSphereTex->Render_Buffer();
}

HRESULT CKrakenBullet::Add_Component(void)
{
	
		CComponent* pComponent = nullptr;

		pComponent = m_pKrakenBullet = dynamic_cast<CTransform*>(Engine::Clone_Proto(TRANSFORM_COMP));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });
		

		pComponent = m_pSphereTex = dynamic_cast<CSphereTex*>(Engine::Clone_Proto(SPHERETEX_COMP));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].insert({ SPHERETEX_COMP, pComponent });

		pComponent = m_pHitBoxCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_DYNAMIC].insert({ L"HitboxTransCom", pComponent });

		pComponent = m_pHitBox = dynamic_cast<CHitBox*>(Clone_Proto(HITBOX_COMP));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].insert({ HITBOX_COMP, pComponent });
	





		pComponent = m_pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_CubePlayerTexture"));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].insert({ L"Proto_CubePlayerTexture", pComponent });


	return S_OK;
}

void CKrakenBullet::Set_Pos(const _vec3 & vPos)
{
	m_pKrakenBullet->Set_Pos(vPos.x, vPos.y , vPos.z);
}

void CKrakenBullet::Collision_Check(void)
{
	if (m_pPlayer == nullptr)
		m_pPlayer = Engine::Get_GameObject(STAGE_CHARACTER, L"PLAYER");

	if (m_pPlayerTransCom == nullptr)
		m_pPlayerTransCom = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_CHARACTER, L"BODY", TRANSFORM_COMP, ID_DYNAMIC));

	if (m_pHitBarUI == nullptr)
		m_pHitBarUI = Engine::Get_GameObject(STAGE_UI, L"HitBarUI");

	if (m_pStaticCam == nullptr)
		m_pStaticCam = dynamic_cast<CStaticCamera*>(Engine::Get_GameObject(STAGE_ENVIRONMENT, L"StaticCamera"));

	_vec3 vPos;
	m_pKrakenBullet->Get_Info(INFO_POS, &vPos);
	_vec3 vPlayerPos;
	m_pPlayerTransCom->Get_Info(INFO_POS, &vPlayerPos);
	_vec3 vPlayerScale;
	m_pPlayerTransCom->Get_Scale(&vPlayerScale);
	_vec3 vScale;
	m_pKrakenBullet->Get_Scale(&vScale);
	_vec3 vPlayerLook;
	m_pPlayerTransCom->Get_Info(INFO_LOOK, &vPlayerLook);

	if (m_pCollision->Sphere_Collision(this->m_pKrakenBullet, m_pPlayerTransCom, vPlayerScale.x, vScale.x))
	{
		if (!m_bDamage)
		{
			_vec3 vDir;
			vDir = vPos - vPlayerPos;

			dynamic_cast<CCubePlayer*>(m_pPlayer)->Set_Damaged(m_fDamage);
			m_pStaticCam->HitPlayer();
			vDir.y = 0.f;
			vPlayerLook.y = 0.f;
			D3DXVec3Normalize(&vDir, &vDir);
			D3DXVec3Normalize(&vPlayerLook, &vPlayerLook);

			_float fAngle = acosf(D3DXVec3Dot(&vPlayerLook, &vDir));

			if (vPlayerPos.x < vPos.x || vPlayerPos.z < vPos.z)
			{
				fAngle = D3DX_PI * 2.f - fAngle;
			}

			dynamic_cast<CHitBarUI*>(m_pHitBarUI)->OnSwitch(fAngle);
		}

		m_bDamage = true;
	}
	
}




CKrakenBullet * CKrakenBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 * vPos, const _vec3 * vDir, _float _fSpeed, _float _fDamage)
{
	CKrakenBullet* pInstance = new CKrakenBullet(pGraphicDev);

		if(FAILED(pInstance->Ready_Object(vPos, vDir, _fSpeed, _fDamage)))
		{
			Safe_Release(pInstance);
			return nullptr;

		}
	return pInstance;
}

void CKrakenBullet::Free(void)
{
	CGameObject::Free();

}
