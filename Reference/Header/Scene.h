#pragma once

#include "Base.h"
#include "Engine_Include.h"
#include "Layer.h"

BEGIN(Engine)

class ENGINE_DLL CScene :	public CBase
{
protected:
	explicit CScene(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CScene();

public:
	CLayer*					Get_Layer(const _tchar* pLayerTag);
	CComponent*				Get_Component(const _tchar* pLayerTag, const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID);
	CGameObject*			Get_GameObject(const _tchar* pLayerTag, const _tchar* pObjTag); 

	map<const _tchar*, CLayer*> Get_MapLayer() { return m_mapLayer; }

public:
	virtual		HRESULT		Ready_Scene(void);
	virtual		_int Update_Scene(const _float& fTimeDelta);
	virtual		void LateUpdate_Scene(void);
	virtual		void Render_Scene(void) {}


protected:
	LPDIRECT3DDEVICE9				m_pGraphicDev;
	map<const _tchar*, CLayer*>		m_mapLayer;

public:
	virtual void	Free(void);
};

END