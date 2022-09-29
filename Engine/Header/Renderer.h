#pragma once


#include "Engine_Include.h"
#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CRenderer : public CComponent
{
	DECLARE_SINGLETON(CRenderer)

private:
	explicit CRenderer();
	virtual ~CRenderer();

public:
	void		Add_RenderGroup(RENDERID eID, CGameObject* pGameObject);
	void		Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev);
	void		Clear_RenderGroup(void);

	void		On_Minimap(void) { m_bMinimap = true; }
	void		Off_Minimap(void) { m_bMinimap = false; }

	list<CGameObject*>			Get_GameObjectGroup(RENDERID eId)
	{
		return m_RenderGroup[eId];
	}

private:
	list<CGameObject*>			m_RenderGroup[RENDER_END];
	_bool						m_bMinimap = false;

private:
	virtual CComponent*	Clone(void) { return nullptr; }
	virtual void Free(void);
};
END