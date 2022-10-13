#include "stdafx.h"
#include "ProjectileParticle.h"
#include "StaticCamera.h"
#include "CubePlayer.h"
#include "FlameEffect.h"
#include "IceEffect.h"

CProjectileParticle::CProjectileParticle(LPDIRECT3DDEVICE9 pGraphicDev)
	:CPSystem(pGraphicDev)
{
	m_fSize = 1.f;
	m_vbSize = 2048;
	m_vbOffset = 0;
	m_vbBatchSize = 512;
}

CProjectileParticle::~CProjectileParticle()
{
}

HRESULT CProjectileParticle::Ready_Object(void)
{
	CPSystem::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

_int CProjectileParticle::Update_Object(const _float & fTimeDelta)
{
	for (list<ATTRIBUTE>::iterator iter = m_particles.begin(); iter != m_particles.end(); iter++)
	{
		iter->vPos += (iter->vVelocity) * fTimeDelta;
		iter->vPos.y -= 0.01f* (Gravity*iter->fAge)*(Gravity* iter->fAge) * fTimeDelta;
		iter->fAge += fTimeDelta;
		
		m_fTextureTime += fTimeDelta;
		if (m_fTextureTime > 0.05f)
		{
			m_fTextureTime = 0.f;
			if (m_iTextureIndex == 1)
			{
				m_iTextureIndex = 0;
			}
			else if (m_iTextureIndex == 0)
			{
				m_iTextureIndex = 1;
			}
			m_fTextureTime = 0.f;
		}/*
		if (iter->fAge > .3f*(m_iTextureIndex+1))
		{
			if (m_iTextureIndex < 2)
			{
				m_iTextureIndex ++;
			}
		}*/
		if ((iter->fAge > iter->fLifeTime)|| iter->vPos.y<0.5f)
		{
			m_vDeadPos = iter->vPos;
			iter->bAlive = false;
			Dead_Effect();
		}
		
	}
	removeDeadParticles();

	Add_RenderGroup(RENDER_PRIORITY, this);

	return 0;
}

void CProjectileParticle::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CProjectileParticle::Render_Object(void)
{
	_matrix matWorld;
	D3DXMatrixIdentity(&matWorld);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	if (!m_particles.empty())
	{
		m_pTextureCom->Set_Texture(m_iTextureIndex);
		CPSystem::Render_Object();
	}
}

HRESULT CProjectileParticle::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(BLUEBOMB_TEX));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ BLUEBOMB_TEX, pComponent });

	return S_OK;
}

CProjectileParticle * CProjectileParticle::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CProjectileParticle *	pInstance = new CProjectileParticle(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CProjectileParticle::Free(void)
{
	CPSystem::Free();
}

void CProjectileParticle::resetParticle(ATTRIBUTE * attribute)
{
	attribute->bAlive = true;
	_float  m_fTextureTime = 0.3f;
	m_iTextureIndex = 0;


	CTransform* pTransform = nullptr;
	Gravity = 75.f;
	//m_fDeadTime = 0;
		
		CTransform*		pPlayerTransformCom = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_CHARACTER, L"HEAD", TRANSFORM_COMP, ID_DYNAMIC));

		D3DXVECTOR3 vPos;
		pPlayerTransformCom->Get_Info(INFO_POS, &vPos);

		D3DXVECTOR3 vDir;
		pPlayerTransformCom->Get_Info(INFO_LOOK, &vDir);

		attribute->vPos = vPos ;
		attribute->vVelocity = (vDir * 200.f);

		attribute->dwColor = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);

		attribute->fAge = 0.0f;
		attribute->fLifeTime = 5.f;
		
}

void CProjectileParticle::Dead_Effect()
{
	for (list<ATTRIBUTE>::iterator iter = m_particles.begin(); iter != m_particles.end(); iter++)
	{
		/*if (!m_pFlameEffectParticle)
			m_pFlameEffectParticle = dynamic_cast<CFlameEffect*>(Engine::Get_GameObject(STAGE_ENVIRONMENT, L"FlameEffect"));
		m_pFlameEffectParticle->Set_PclePos(m_vDeadPos);
		
		
		for (_int i = 0; i < 25; ++i)
		{
			m_pFlameEffectParticle->addParticle();
		}
*/


		if (!m_pIceEffectParticle)
			m_pIceEffectParticle = dynamic_cast<CIceEffect*>(Engine::Get_GameObject(STAGE_ENVIRONMENT, L"IceEffect"));
		m_pIceEffectParticle->Set_PclePos(m_vDeadPos);


		for (_int i = 0; i < 150; ++i)
		{
			m_pIceEffectParticle->addParticle();
		}
	}
}
