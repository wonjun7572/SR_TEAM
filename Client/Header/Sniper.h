#pragma once
#include "Weapon.h"
#include "Wall.h"
#include "SniperPart1.h"
#include "SniperPart2.h"
#include "SniperPart3.h"
#include "SniperPart4.h"
#include "Export_Function.h"
USING(Engine)

class CSniper : public CWeapon
{
private:
	explicit CSniper(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSniper();

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;

private:
	HRESULT			Add_Component(void);
	HRESULT			Add_Parts();
	HRESULT			Get_Parts(void);
	void			Set_OnTerrain(void);						//	���� Ÿ��

	void			Assemble(void);								//	��ü ����

	void			Animation_Fire(void);						//	�ȴ� ���

private:


public:
	static CSniper*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void Free(void);
};



