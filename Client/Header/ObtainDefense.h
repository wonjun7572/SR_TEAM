#pragma once
#include "Item.h"
class CObtainDefense :
	public CItem
{
private:
	explicit CObtainDefense(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CObtainDefense(const CGameObject& rhs);
	virtual ~CObtainDefense();

public:
	HRESULT Ready_Object(const _vec3& vPos) override;
	_int	Update_Object(const _float& fTimeDelta) override;
	void	LateUpdate_Object() override;
	void	Render_Object() override;

private:
	HRESULT			Add_Component(void);
	CHitBox*		m_pHitBox = nullptr;

public:
	static CObtainDefense* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);

protected:
	void Free() override;

};

