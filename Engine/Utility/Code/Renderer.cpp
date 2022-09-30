#include "..\..\Header\Renderer.h"

USING(Engine)
IMPLEMENT_SINGLETON(CRenderer)

CRenderer::CRenderer()
{
}


CRenderer::~CRenderer()
{
	Free();
}

void CRenderer::Add_RenderGroup(RENDERID eID, CGameObject * pGameObject)
{
	if (eID >= RENDER_END || nullptr == pGameObject)
		return;

	m_RenderGroup[eID].push_back(pGameObject);
	pGameObject->AddRef();
}

void CRenderer::Render_GameObject(LPDIRECT3DDEVICE9 & pGraphicDev)
{
	for (auto& iter : m_RenderGroup[RENDER_PRIORITY])
	{
		iter->Render_Object();
		Safe_Release(iter);			
	}
	m_RenderGroup[RENDER_PRIORITY].clear();

	if (m_bMinimap)
	{
		for (auto& iter : m_RenderGroup[RENDER_MINIMAP])
		{
			iter->Render_Object();
			Safe_Release(iter);
		}
		m_RenderGroup[RENDER_MINIMAP].clear();
	}
	for (auto& iter : m_RenderGroup[RENDER_NONALPHA])
	{
		iter->Render_Object();
		Safe_Release(iter);
	}
	m_RenderGroup[RENDER_NONALPHA].clear();

	for (auto& iter : m_RenderGroup[RENDER_ALPHA])
	{
		iter->Render_Object();
		Safe_Release(iter);
	}
	m_RenderGroup[RENDER_ALPHA].clear();

	for (auto& iter : m_RenderGroup[RENDER_UI])
	{
		pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0xcc);
		pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		iter->Render_Object();
		pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		Safe_Release(iter);
	}
	m_RenderGroup[RENDER_UI].clear();
}

void CRenderer::Clear_RenderGroup(void)
{
	for (_uint i = 0; i < RENDER_END; ++i)
	{
		for_each(m_RenderGroup[i].begin(), m_RenderGroup[i].end(), CDeleteObj());
		m_RenderGroup[i].clear();
	}
}


void Engine::CRenderer::Free(void)
{
	Clear_RenderGroup();
}
