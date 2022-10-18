#include "..\..\Header\PSystem.h"

USING(Engine)

//const DWORD PARTICLE::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

CPSystem::CPSystem(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_origin({ 0.f,0.f,0.f })
	, m_fEmitRate(0.f)
	, m_fSize(0.f)
	, m_pTextureCom(nullptr)
	, m_vb(nullptr)
	, m_maxParticles(0)
	, m_vbSize(0)
	, m_vbOffset(0)
	, m_vbBatchSize(0)
{
}

CPSystem::~CPSystem()
{

}

HRESULT CPSystem::Ready_Object(void)
{
	// D3D��ġ ������ �ʱ�ȭ �۾��� ó��
	FAILED_CHECK_RETURN(m_pGraphicDev->CreateVertexBuffer(
		m_vbSize * sizeof(PARTICLE),	// ���ؽ� ���� ũ��
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		// _DYNAMIC : ���� ���ؽ����۸� ����Ѵ�.
		// _POINTS	: ���ؽ� ���۰� ����Ʈ ��������Ʈ�� ������ ������ ����
		FVF_PARTICLE,
		D3DPOOL_DEFAULT,
		&m_vb,
		0), E_FAIL);

	return S_OK;
}

_int CPSystem::Update_Object(const _float & fTimeDelta)
{
	return CGameObject::Update_Object(fTimeDelta);
}

void CPSystem::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CPSystem::Render_Object(void)
{
	render();
}

void CPSystem::Free(void)
{
	m_particles.clear();

	Safe_Release(m_vb);

	CGameObject::Free();
}

void CPSystem::reset()
{
	// ��� ��ƼŬ �Ӽ��� ����
	for (auto& iter = m_particles.begin(); iter != m_particles.end(); ++iter)
	{
		resetParticle(&(*iter));
	}
}

void CPSystem::addParticle()
{
	// �ý��ۿ� ��ƼŬ�� �߰�.
	ATTRIBUTE tAttribute;

	resetParticle(&tAttribute);

	m_particles.push_back(tAttribute);
}

void CPSystem::preRender()
{
	// �������� �ռ� ������ �ʱ� ���� ����
	// ���� ������ ��ü �ؽ�ó ����Ʈ ��������Ʈ�� �ؽ�ó ���ο� �̿��� ����
	m_pGraphicDev->SetRenderState(D3DRS_POINTSPRITEENABLE, true);

	// ����Ʈ ũ�⸦ �佺���̽� ������ �ؼ��� ���ΰ�?
	// �佺���̽� ���� : ī�޶� ������ 3D ����Ʈ. ī�޶���� �Ÿ��� ���� ũ�Ⱑ ������.
	// false : ��ũ�������̽� ����
	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALEENABLE, true);

	m_pGraphicDev->SetRenderState(D3DRS_POINTSIZE, FtoDw(m_fSize));
	m_pGraphicDev->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.0f));

	// �Ÿ�(����Ʈ�� ī�޶� ���� �Ÿ�)�� ���� ��ƼŬ ũ�� ����
	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0f));

	// �ؽ�ó�� ���ĸ� �̿��Ѵ�.
	m_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0x00);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
}

void CPSystem::render()
{
		// ���� ���� ����
		preRender();
		
		m_pGraphicDev->SetFVF(FVF_PARTICLE);
		m_pGraphicDev->SetStreamSource(0, m_vb, 0, sizeof(PARTICLE));

		// ���ؽ� ���۸� ��� ��� ó������ �����Ѵ�.
		if (m_vbOffset >= m_vbSize)
			m_vbOffset = 0;

		PARTICLE* v = 0;

		m_vb->Lock(
			m_vbOffset * sizeof(PARTICLE),
			m_vbBatchSize * sizeof(PARTICLE),
			(void**)&v,
			m_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		DWORD numParticlesInBatch = 0;

		// ��� ��ƼŬ�� ������ �ɶ�����
		for (auto iter = m_particles.begin(); iter != m_particles.end(); ++iter)
		{
			if (iter->bAlive)
			{
				// �Ѵܰ��� ������ ��ƼŬ�� ���� ���ؽ� ���� ���׸�Ʈ�� ����
				v->vPos = iter->vPos;
				v->dwColor = (D3DCOLOR)iter->dwColor;
				v++; // next element;

				numParticlesInBatch++; // �ܰ� ī���͸� ������Ų��.

									   // ���� �ܰ谡 ��� ä�����ִ°�?
				if (numParticlesInBatch == m_vbBatchSize)
				{
					// ���ؽ� ���۷� ����� ������ �ܰ��� ��ƼŬ���� �׸���.
					m_vb->Unlock();

					m_pGraphicDev->DrawPrimitive(
						D3DPT_POINTLIST,
						m_vbOffset,
						m_vbBatchSize);

					// �ܰ谡 �׷����� ���� ���� �ܰ踦 ��ƼŬ�� ä���.

					// ���� �ܰ��� ó�� ���������� �̵��Ѵ�.
					m_vbOffset += m_vbBatchSize;

					// ���ؽ� ������ ��踦 �Ѵ� �޸𸮷� �������� �������� �����´�.
					// ��踦 ���� ��� ó������ ����
					if (m_vbOffset >= m_vbSize)
						m_vbOffset = 0;

					m_vb->Lock(
						m_vbOffset * sizeof(PARTICLE),
						m_vbBatchSize * sizeof(PARTICLE),
						(void**)&v,
						m_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					numParticlesInBatch = 0; // �����ܰ踦 ���� ����
				}
			}
		}

		m_vb->Unlock();

		// numParticleInBatch == vbBatchSize ������ �������� �ʾ�
		// �������ܰ谡 ���������� �ʴ� ��찡 �߻��� �� ����.
		// �Ϻθ� ä���� �ܰ�� �̰����� ��������.
		if (numParticlesInBatch)
		{
			m_pGraphicDev->DrawPrimitive(
				D3DPT_POINTLIST,
				m_vbOffset,
				numParticlesInBatch);
		}

		// �������
		m_vbOffset += m_vbBatchSize;

		postRender();
}

void CPSystem::postRender() // �������¸� �����ϱ� ���� �ʿ��� �Լ�
{
	m_pGraphicDev->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}

_bool CPSystem::isEmpty()
{
	return m_particles.empty();
}

_bool CPSystem::isDead()
{
	for (auto& pt : m_particles)
	{
		if (true == pt.bAlive)
		{
			return false;
		}
	}
	return true;
}

void CPSystem::removeDeadParticles()
{
	std::list<ATTRIBUTE>::iterator i;

	i = m_particles.begin();

	while (i != m_particles.end())
	{
		if (i->bAlive == false)
		{
			// erase returns the next iterator, so no need to
			// incrememnt to the next one ourselves.
			i = m_particles.erase(i);
		}
		else
		{
			i++; // next in list
		}
	}
}
