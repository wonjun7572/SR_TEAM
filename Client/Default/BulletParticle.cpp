#include "stdafx.h"
#include "BulletParticle.h"
#include "StaticCamera.h"

CBulletParticle::CBulletParticle(LPDIRECT3DDEVICE9 pGraphicDev)
	:CPSystem(pGraphicDev)
{
	m_fSize = 0.8f;
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
	return S_OK;
}

_int CBulletParticle::Update_Object(const _float & fTimeDelta)
{
	//addParticle();
	update(fTimeDelta);
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
	render();
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
	attribute->vPos.y -= 1.0f; // slightly below camera
	// so its like we're carrying a gun

	// travels in the direction the camera is looking
	attribute->vVelocity = cameraDir * 100.0f;

	// green
	attribute->dwColor = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	attribute->fAge = 0.0f;
	attribute->fLifeTime = 1.0f; // lives for 1 seconds
}

void CBulletParticle::update(_float fTimeDelta)
{
	std::list<ATTRIBUTE>::iterator i;

	for (i = m_particles.begin(); i != m_particles.end(); i++)
	{
		i->vPos += i->vVelocity * fTimeDelta;

		i->fAge += fTimeDelta;

		if (i->fAge > i->fLifeTime) // kill 
			i->bAlive = false;
	}
	removeDeadParticles();
}
