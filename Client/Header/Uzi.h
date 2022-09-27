#pragma once
#include "Weapon.h"
#include "Wall.h"
#include "UziPart1.h"
#include "UziPart2.h"
#include "UziPart3.h"
#include "UziPart4.h"
#include "UziPart5.h"
#include "Export_Function.h"
USING(Engine)

class CUzi : public CWeapon
{
private:
	explicit CUzi(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CUzi();

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
	
public:
	static CUzi*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void Free(void);
};



