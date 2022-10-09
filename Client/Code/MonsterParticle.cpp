#include "stdafx.h"
#include "..\Header\MonsterParticle.h"
#include "CubePlayer.h"
#include "Weapon.h"
#include "TargetCube.h"
CMonsterParticle::CMonsterParticle(LPDIRECT3DDEVICE9 pGraphicDev)
	:CPSystem(pGraphicDev)
{

	m_fSize = 0.1f;
	m_vbSize = 2048;
	m_vbOffset = 0;
	m_vbBatchSize = 512;
}


CMonsterParticle::~CMonsterParticle()
{
}

HRESULT CMonsterParticle::Ready_Object(void)
{
	CPSystem::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

_int CMonsterParticle::Update_Object(const _float & fTimeDelta)
{
	for (list<ATTRIBUTE>::iterator iter = m_particles.begin(); iter != m_particles.end(); iter++)
	{
		iter->vPos += iter->vVelocity * fTimeDelta;

		iter->fAge += fTimeDelta;

		if (iter->fAge > iter->fLifeTime)
			iter->bAlive = false;
	}

	removeDeadParticles();

	Add_RenderGroup(RENDER_PRIORITY, this);

	return 0;
}

void CMonsterParticle::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CMonsterParticle::Render_Object(void)
{
	_matrix matWorld;
	D3DXMatrixIdentity(&matWorld);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	if (!m_particles.empty())
	{
		m_pTextureCom->Set_Texture(0);
		CPSystem::Render_Object();
	}
}

HRESULT CMonsterParticle::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_MonsterParticle"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_MonsterParticle", pComponent });

	return S_OK;
}

CMonsterParticle * CMonsterParticle::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMonsterParticle *	pInstance = new CMonsterParticle(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CMonsterParticle::Free(void)
{
	CPSystem::Free();
}

void CMonsterParticle::resetParticle(ATTRIBUTE * attribute)
{
	attribute->bAlive = true;
	CGameObject* pMonster = nullptr;
	pMonster = Engine::Get_GameObject(STAGE_MONSTER, L"TargetCube1");
	NULL_CHECK_RETURN(pMonster, );

	CTransform* pTransform = nullptr;

	if (dynamic_cast<CTargetCube*>(pMonster)->Get_MAbility()->fCurrentHp <= 90)
	{
		pTransform = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_MONSTER, L"TargetCube1", TRANSFORM_COMP, ID_DYNAMIC));
		NULL_CHECK_RETURN(pTransform, );
		D3DXVECTOR3 vPos;
		pTransform->Get_Info(INFO_POS, &vPos);

		D3DXVECTOR3 vDir;
		pTransform->Get_Info(INFO_LOOK, &vDir);

		attribute->vPos = vPos;

		attribute->dwColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		attribute->fAge = 0.0f;
		attribute->fLifeTime = 5.f;
	}
}
