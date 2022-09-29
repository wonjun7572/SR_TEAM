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
	void			TransAxisUzi1(void);
	void			TransAxisUzi2(void);

	HRESULT			Add_Component(void);
	HRESULT			Add_Parts();
	HRESULT			Get_Parts(void);

	void			Set_OnTerrain(void);
	
	void			Assemble(void);

	void			Animation_Fire(void);
	
private:
	CTransform*		m_pTransform = nullptr;	

	CTransform*		m_pUziPart1 = nullptr;
	CTransform*		m_pUziPart2 = nullptr;
	CTransform*		m_pUziPart3 = nullptr;
	CTransform*		m_pUziPart4 = nullptr;
	CTransform*		m_pUziPart5 = nullptr;

	CCalculator*	m_pCalculatorCom = nullptr;
	CCubeTex*		m_pBufferCom = nullptr;
	CTexture*		m_pTextureCom = nullptr;

	_float			m_fTimeDelta = 0.f;
	_float			m_fUnit = 0.1f;

public:
	static CUzi*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void Free(void);
};



