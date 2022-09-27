#pragma once
#include "Item.h"

class CHealthPotion : public CItem
{
private:
	explicit CHealthPotion(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CHealthPotion(const CGameObject& rhs);
	virtual ~CHealthPotion();

public:
	HRESULT Ready_Object(const _vec3& vPos) override;
	_int	Update_Object(const _float& fTimeDelta) override;
	void	LateUpdate_Object() override;
	void	Render_Object() override;

private:
	HRESULT			Add_Component(void);

public:
	static CHealthPotion* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);

protected:
	void Free() override;

};

