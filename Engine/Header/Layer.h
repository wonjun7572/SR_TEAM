#pragma once

#include "GameObject.h"
#include "Engine_Include.h"

BEGIN(Engine)

class ENGINE_DLL CLayer : public CBase
{
private:
	explicit CLayer();
	virtual ~CLayer();

public:
	CComponent*				Get_Component(const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID);
	CGameObject*			Get_GameObject(const _tchar* pObjTag);

	map<const _tchar*, CGameObject*>	Get_GameObjectMap()	{return m_mapObject;}

public:
	HRESULT			Add_GameObject(const _tchar* pObjTag, CGameObject* pInstance);
	HRESULT			Delete_GameObject(const _tchar * pObjTag);
	HRESULT			Add_GameList(CGameObject* pInstance);

	HRESULT			Ready_Layer(void);
	_int			Update_Layer(const _float& fTimeDelta);
	void			LateUpdate_Layer(void);

private:
	map<const _tchar*, CGameObject*>			m_mapObject;
	list<CGameObject*>							m_ObjectList;

public:
	static CLayer*		Create(void);
	virtual void		Free(void);

};

END