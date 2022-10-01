#pragma once
#include "Item.h"
class CMaxPlusHp :	public CItem
{
public:
	explicit CMaxPlusHp(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMaxPlusHp(const CGameObject& rhs);
	virtual ~CMaxPlusHp();

public:
	HRESULT Ready_Object(const _vec3& vPos) override;
	_int	Update_Object(const _float& fTimeDelta) override;
	void	LateUpdate_Object() override;
	void	Render_Object() override;

private:
	HRESULT			Add_Component(void);
	CHitBox*		m_pHitBox = nullptr;

public:
	static CMaxPlusHp* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);

protected:
	void Free() override;


};

