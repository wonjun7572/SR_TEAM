#include "..\..\Header\PSystem.h"
#include "Export_Function.h"

USING(Engine)

CPSystem::CPSystem(LPDIRECT3DDEVICE9 pGraphicDev)
	:CVIBuffer(pGraphicDev)
{
}

CPSystem::CPSystem(const CPSystem & rhs)
	:CVIBuffer(rhs)
{
}

CPSystem::~CPSystem()
{
}

HRESULT CPSystem::Ready_Buffer(void)
{
	m_pGraphicDev->CreateVertexBuffer(
		sizeof(PARTICLE) *m_dwVtxCnt,
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		m_dwFVF,
		D3DPOOL_DEFAULT,
		&m_pVB,
		NULL);

	return S_OK;
}

void CPSystem::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

void CPSystem::Reset()
{
	list<ATTRIBUTE>::iterator iter;
	for (iter = m_Pariclelist.begin; iter != m_Pariclelist.end(); i++)
		ResetParticle(&(*iter));
}

void CPSystem::ResetParticle(ATTRIBUTE * attribute)
{
}

void CPSystem::AddParticle()
{
}

void CPSystem::Update()
{
}

void CPSystem::PreRender()
{
}

void CPSystem::PostRender()
{
}

bool CPSystem::isEmpty()
{
	return false;
}

bool CPSystem::isDead()
{
	return false;
}

void CPSystem::RemoveDeadParticles()
{
}

CPSystem * CPSystem::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPSystem* pInstance = new CPSystem(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CPSystem::Clone(void)
{
	return new CPSystem(*this);
}

void CPSystem::Free(void)
{
	CVIBuffer::Free();
}
