#pragma once
#include "GameObject.h"

class CTargetCube :	public CGameObject
{
private:
	explicit CTargetCube(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTargetCube();

public:
	virtual HRESULT Ready_Object(const _vec3& vPos);
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;
	void         Set_Damaged(_int iDamage) { m_tAbility->fCurrentHp -= iDamage; }
	MONSTERABILITY* Get_MAbility() { return m_tAbility; }
	void				Update_NullCheck();
private:
	HRESULT				Add_Component(void);
	void				Hit_Check(void);

private:
	CCubeTex*			m_pBufferCom = nullptr;
	CTransform*			m_pTransCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CCalculator*		m_pCalculatorCom = nullptr;
	CCollision*			m_pCollision = nullptr;

	CRcTex*				m_pBufferUICom = nullptr;
	CTexture*			m_pTextureUICom = nullptr;
	CTransform*			m_pTransUICom = nullptr;

	CHitBox*			m_pHitBox = nullptr;
	_float				m_fFrame = 0.f;
	_bool				m_bReFresh = false;

private:
	MONSTERABILITY*		m_tAbility;

public:
	static CTargetCube*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);
	virtual void	Free(void);
};

