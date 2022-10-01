#include "stdafx.h"
#include "BulletParticle.h"
#include "StaticCamera.h"

CBulletParticle::CBulletParticle(LPDIRECT3DDEVICE9 pGraphicDev)
	:CPSystem(pGraphicDev)
{
	m_fSize = 0.4f;
	m_vbSize = 2048;
	m_vbOffset = 0;
	m_vbBatchSize = 512;
}

CBulletParticle::~CBulletParticle()
{
}

HRESULT CBulletParticle::Ready_Object(void)
{
	CPSystem::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

_int CBulletParticle::Update_Object(const _float & fTimeDelta)
{
	for (list<ATTRIBUTE>::iterator iter = m_particles.begin(); iter != m_particles.end(); iter++)
	{
		iter->vPos += iter->vVelocity * fTimeDelta;

		iter->fAge += fTimeDelta;

		if (iter->fAge > iter->fLifeTime) // kill 
			iter->bAlive = false;
	}
	removeDeadParticles();

	m_tFrame++;
	if (m_tFrame >= 8.f)
		m_tFrame = 0.f;

	Add_RenderGroup(RENDER_PRIORITY, this);

	return 0;
}

void CBulletParticle::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CBulletParticle::Render_Object(void)
{
	_matrix matWorld;
	D3DXMatrixIdentity(&matWorld);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	if (!m_particles.empty())
	{
		m_pTextureCom->Set_Texture(_uint(m_tFrame));
		CPSystem::Render_Object();
	}
}

HRESULT CBulletParticle::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"FLARE_Alpha"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"FLARE_Alpha", pComponent });

	return S_OK;
}

CBulletParticle * CBulletParticle::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBulletParticle *	pInstance = new CBulletParticle(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CBulletParticle::Free(void)
{
	CPSystem::Free();
}

void CBulletParticle::resetParticle(ATTRIBUTE * attribute)
{
	attribute->bAlive = true;

	CStaticCamera* pCam = nullptr;
	pCam = dynamic_cast<CStaticCamera*>(Engine::Get_GameObject(L"Layer_Environment", L"StaticCamera"));

	D3DXVECTOR3 cameraPos;
	pCam->Get_Position(&cameraPos);

	D3DXVECTOR3 cameraDir;
	pCam->Get_Look(&cameraDir);

	// change to camera position
	attribute->vPos = cameraPos;
	attribute->vPos.y += 1.5f; // slightly below camera
	// so its like we're carrying a gun

	// travels in the direction the camera is looking
	attribute->vVelocity = cameraDir * 100.0f;

	// green
	attribute->dwColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	attribute->fAge = 0.0f;
	attribute->fLifeTime = 1.0f; // lives for 1 seconds
}