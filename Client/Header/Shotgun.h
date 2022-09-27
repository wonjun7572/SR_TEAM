#pragma once
#include "Weapon.h"
#include "Wall.h"
#include "ShotgunPart1.h"
#include "ShotgunPart2.h"
#include "ShotgunPart3.h"
#include "ShotgunPart4.h"
#include "ShotgunPart5.h"
#include "Export_Function.h"
USING(Engine)

class CShotgun : public CWeapon
{
private:
	explicit CShotgun(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CShotgun();

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;

private:
	HRESULT			Add_Component(void);
	HRESULT			Add_Parts();
	HRESULT			Get_Parts(void);
	void			Set_OnTerrain(void);						//	지형 타기

	void			Assemble(void);								//	몸체 조립

	void			Animation_Fire(void);						//	걷는 모션

public:
	static CShotgun*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void Free(void);
};



