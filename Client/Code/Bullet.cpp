#include "stdafx.h"
#include "..\Header\Bullet.h"

#include "Export_Function.h"
#include "CubePlayer.h"
#include "PoolMgr.h"
#include "HitBarUI.h"
#include "StaticCamera.h"

CBullet::CBullet(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}

CBullet::~CBullet()
{
}

HRESULT CBullet::Ready_Object(const _vec3* pPos, const _vec3* pDir, _float _fDamage)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_pTransCom->Set_Scale(0.05f, 0.05f, 0.05f);
	m_pTransCom->m_vInfo[INFO_POS] = *pPos;
	m_vDirection = *pDir;
	m_fDamage = _fDamage;
	return S_OK;
}

_int CBullet::Update_Object(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta;
	Before_Update();

	if (m_fTimeDelta >= 5.f)
	{
		m_bDamage = false;
		dynamic_cast<CHitBarUI*>(m_pHitBarUI)->OffSwitch();
		CPoolMgr::GetInstance()->Collect_Obj(this);
		m_fTimeDelta = 0.f;
		return -1;
	}

	_vec3 vPos;
	m_pTransCom->Get_Info(INFO_POS, &vPos);
	_vec3 vPlayerPos;
	m_pPlayerTransCom->Get_Info(INFO_POS, &vPlayerPos);
	_vec3 vPlayerScale;
	m_pPlayerTransCom->Get_Scale(&vPlayerScale);
	_vec3 vScale;
	m_pTransCom->Get_Scale(&vScale);
	_vec3 vPlayerLook;
	m_pPlayerTransCom->Get_Info(INFO_LOOK, &vPlayerLook);

	if (m_pCollision->Sphere_Collision(this->m_pTransCom, m_pPlayerTransCom, vPlayerScale.x, vScale.x))
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

	Engine::CGameObject::Update_Object(fTimeDelta);

	m_pTransCom->Move_Pos(&(m_vDirection * fTimeDelta * m_fSpeed));

	return 0;
}

void CBullet::LateUpdate_Object(void)
{
	Engine::Add_RenderGroup(RENDER_NONALPHA, this);
	Engine::CGameObject::LateUpdate_Object();
}

void CBullet::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	m_pTextureCom->Set_Texture();

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

HRESULT CBullet::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"BULLET_TEX"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"BULLET_TEX", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });

	pComponent = m_pBufferCom = dynamic_cast<CSphereTex*>(Clone_Proto(SPHERETEX_COMP));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ SPHERETEX_COMP, pComponent });

	pComponent = m_pCollision = dynamic_cast<CCollision*>(Engine::Clone_Proto(COLLISION_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ COLLISION_COMP, pComponent });

	return S_OK;
}

void CBullet::Set_Pos(const _vec3 & vPos)
{
	m_pTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
}

void CBullet::MoveToDir(const _vec3 & vDir)
{
	m_pTransCom->m_vInfo[INFO_POS] += vDir * m_fTimeDelta * m_fSpeed;
}

void CBullet::Before_Update()
{
	if (m_pPlayer == nullptr)
		m_pPlayer = Engine::Get_GameObject(STAGE_CHARACTER, L"PLAYER");

	if (m_pPlayerTransCom == nullptr)
		m_pPlayerTransCom = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_CHARACTER, L"BODY", TRANSFORM_COMP, ID_DYNAMIC));

	if (m_pHitBarUI == nullptr)
		m_pHitBarUI = Engine::Get_GameObject(STAGE_UI, L"HitBarUI");

	if(m_pStaticCam == nullptr)
		m_pStaticCam = dynamic_cast<CStaticCamera*>(Engine::Get_GameObject(STAGE_ENVIRONMENT, L"StaticCamera"));
}

CBullet * CBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3* pPos, const _vec3* pDir, _float _fDamage)
{
	CBullet *   pInstance = new CBullet(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(pPos, pDir, _fDamage)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CBullet::Free(void)
{
	CGameObject::Free();
}