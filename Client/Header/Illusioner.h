#pragma once
#include "Monster.h"
class CIllusioner :
	public CMonster
{
public:
	CIllusioner(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CIllusioner();


public:
	virtual		HRESULT		Ready_Object(const _vec3& vPos, _tchar* Name);
	virtual		_int		Update_Object(const _float& fTimeDelta);
	virtual		void		LateUpdate_Object(void);
	virtual		void		Render_Object(void);

private:
	HRESULT				Add_Component(void);
	HRESULT				Create_Item();

public:
	static CIllusioner*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos, _tchar* Name);
	virtual void	Free(void);

};

