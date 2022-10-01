//
//#include "..\..\Header\ParticleBuffer.h"
//
//USING(Engine)
//
//CParticleBuffer::CParticleBuffer(LPDIRECT3DDEVICE9 pGraphicDev)
//	: CComponent(pGraphicDev), m_pVB(nullptr)
//{
//}
//
//CParticleBuffer::CParticleBuffer(const CParticleBuffer & rhs)
//	: CComponent(rhs), 
//	m_pVB(rhs.m_pVB), 
//	m_dwVtxSize(rhs.m_dwVtxSize), 
//	m_dwVtxBatchSize(rhs.m_dwVtxBatchSize), 
//	m_dwVtxOffset(rhs.m_dwVtxOffset), 
//	m_ParticleList(rhs.m_ParticleList), 
//	m_fSize(rhs.m_fSize)
//{
//	m_pVB->AddRef();
//}
//
//CParticleBuffer::~CParticleBuffer()
//{
//}
//
//HRESULT CParticleBuffer::Ready_Buffer(void)
//{
//	if (FAILED(m_pGraphicDev->CreateVertexBuffer(
//		m_dwVtxSize * sizeof(PARTICLE),
//		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
//		FVF_PARTICLE,
//		D3DPOOL_DEFAULT,
//		&m_pVB,
//		nullptr)))
//	{
//		return E_FAIL;
//	}
//	return S_OK;
//}
//
//void CParticleBuffer::PreRender_Buffer(void)
//{
//	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, false);
//	m_pGraphicDev->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
//	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALEENABLE, true);
//	m_pGraphicDev->SetRenderState(D3DRS_POINTSIZE, FtoDw(m_fSize));
//	m_pGraphicDev->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.0f));
//
//	// control the size of the particle relative to distance
//	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
//	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
//	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0f));
//
//	// use alpha from texture
//	m_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
//	m_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
//
//	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
//	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//
//	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, true);
//	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0x00);
//	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
//}
//
//void CParticleBuffer::Render_Buffer(void)
//{
//	m_pGraphicDev->SetFVF(FVF_PARTICLE);
//	m_pGraphicDev->SetStreamSource(0, m_pVB, 0, sizeof(PARTICLE));
//
//	if (m_dwVtxOffset >= m_dwVtxSize)
//		m_dwVtxSize = 0;
//
//	PARTICLE* v = 0;
//
//	m_pVB->Lock(m_dwVtxOffset * sizeof(PARTICLE),
//		m_dwVtxBatchSize * sizeof(PARTICLE),
//		(void**)&v,
//		m_dwVtxOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);
//
//	_ulong dwNumParticlesInBatch = 0;
//
//	for (list<ATTRIBUTE>::iterator iter = m_ParticleList.begin();
//		iter != m_ParticleList.end();
//		iter++)
//	{
//		if (iter->bAlive)
//		{
//			v->vPos = iter->vPos;
//			v->dwColor = (D3DCOLOR)iter->dwColor;
//			v++;
//
//			dwNumParticlesInBatch++;
//
//			if (dwNumParticlesInBatch == m_dwVtxBatchSize)
//			{
//				m_pVB->Unlock();
//
//				m_pGraphicDev->DrawPrimitive(D3DPT_POINTLIST,
//					m_dwVtxOffset, m_dwVtxBatchSize);
//
//				m_dwVtxOffset += m_dwVtxBatchSize;
//
//				if (m_dwVtxOffset >= m_dwVtxSize)
//					m_dwVtxOffset = 0;
//
//				m_pVB->Lock(m_dwVtxOffset * sizeof(PARTICLE),
//					m_dwVtxBatchSize * sizeof(PARTICLE),
//					(void**)&v,
//					m_dwVtxOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);
//
//				dwNumParticlesInBatch = 0;
//			}
//		}
//	}
//
//	m_pVB->Unlock();
//
//	if (dwNumParticlesInBatch)
//	{
//		m_pGraphicDev->DrawPrimitive(D3DPT_POINTLIST, m_dwVtxOffset, dwNumParticlesInBatch);
//	}
//
//	m_dwVtxOffset += m_dwVtxBatchSize;
//}
//
//void CParticleBuffer::PostRender_Buffer()
//{
//	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, true);
//	m_pGraphicDev->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
//	m_pGraphicDev->SetRenderState(D3DRS_POINTSCALEENABLE, false);
//	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
//	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, false);
//}
//
//CParticleBuffer * CParticleBuffer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
//{
//	CParticleBuffer*	pInstance = new CParticleBuffer(pGraphicDev);
//
//	if (FAILED(pInstance->Ready_Buffer()))
//	{
//		Safe_Release(pInstance);
//		return nullptr;
//	}
//
//	return pInstance;
//}
//
//CComponent * CParticleBuffer::Clone(void)
//{
//	return new CParticleBuffer(*this);
//}
//
//void CParticleBuffer::Free(void)
//{
//	Safe_Release(m_pVB);
//	CComponent::Free();
//}
