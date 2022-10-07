#pragma once
#include "Monster.h"
class CZombie :	public CMonster
{
private:
	explicit CZombie(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CZombie();

	virtual	HRESULT Ready_Object(const _vec3& vPos, wstring _strObjTag);
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;

private:
	HRESULT				Add_Component(void);

public:
	static CZombie*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos, wstring _strObjTag);
	virtual void	Free(void);
};
