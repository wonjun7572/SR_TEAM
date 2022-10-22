#include "stdafx.h"
#include "..\Header\DeadParticle.h"


CDeadParticle::CDeadParticle(LPDIRECT3DDEVICE9 pGraphicDev)
	:CPSystem(pGraphicDev)
{
	m_fSize = .05f;
	m_vbSize = 2048;
	m_vbOffset = 0;
	m_vbBatchSize = 512;
}


CDeadParticle::~CDeadParticle()
{
}

HRESULT CDeadParticle::Ready_Object(void)
{
	CPSystem::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

_int CDeadParticle::Update_Object(const _float & fTimeDelta)
{
	for (list<ATTRIBUTE>::iterator iter = m_particles.begin(); iter != m_particles.end(); iter++)
	{
		iter->fAge += fTimeDelta;
		iter->vPos += (iter->vVelocity) * fTimeDelta * 3.5f;
		iter->vPos.y += 0.01f* (m_fGravity*iter->fAge)*(m_fGravity* iter->fAge) * fTimeDelta;

		if (iter->fAge > iter->fLifeTime)
		{
			iter->bAlive = false;
		}
	}
	removeDeadParticles();

	Add_RenderGroup(RENDER_PRIORITY, this);
	return 0;
}

void CDeadParticle::LateUpdate_Object(void)
{
	CPSystem::LateUpdate_Object();
}

void CDeadParticle::Render_Object(void)
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

HRESULT CDeadParticle::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Red_Tex"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Red_Tex", pComponent });

	return S_OK;
}

CDeadParticle * CDeadParticle::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDeadParticle *	pInstance = new CDeadParticle(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CDeadParticle::Free(void)
{
	CPSystem::Free();
}

void CDeadParticle::resetParticle(ATTRIBUTE * attribute)
{
	attribute->bAlive = true;



	_vec3 min = _vec3(-0.50f, -1.0f, -1.0f);
	_vec3 max = _vec3(1.0f, 1.0f, 1.0f);


	//	GetRandomVector(&attribute->vVelocity, &min, &max);
	D3DXVec3Normalize(&attribute->vVelocity, &attribute->vVelocity);
	attribute->vPos = m_pDeadParticle;
	attribute->vPos.x = m_pDeadParticle.x;
	attribute->vPos.y = m_pDeadParticle.y;
	attribute->vVelocity = m_vDir / 2.f;
	attribute->dwColor = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	attribute->dwColor = D3DXCOLOR(GetRandomFloat(0.8f, 1.0f), GetRandomFloat(0.f, 0.2f), GetRandomFloat(0.f, .2f), 1.0f);

	attribute->fAge = 0.0f;
	attribute->fLifeTime = 0.5f;
}
