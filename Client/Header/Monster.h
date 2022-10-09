#pragma once
#include "GameObject.h"

class CMonsterUI;

class CMonster : public CGameObject
{
protected:
	explicit CMonster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMonster();

protected:
	virtual HRESULT		Ready_Object(const _vec3& vPos, wstring _strObjTag);
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object(void) override;
	virtual void		Render_Object(void) override;

	MONSTERABILITY*		Get_MAbility() { return m_tAbility; }

protected:
	void				Hit_Check(_float _deltaTime);

protected:
	CCubeTex*			m_pBufferCom = nullptr;
	CTransform*			m_pTransCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CCalculator*		m_pCalculatorCom = nullptr;
	CCollision*			m_pCollision = nullptr;

	CRcTex*				m_pBufferUICom = nullptr;
	CTexture*			m_pTextureUICom = nullptr;
	CTransform*			m_pTransUICom = nullptr;

	CHitBox*			m_pHitBox = nullptr;
	CTransform*			m_pHitBoxTransCom = nullptr;

	CMonsterUI*			m_pMonsterUI = nullptr;

	CTransform*			m_pPlayerTransCom = nullptr;

	CSphereTex*			m_pSphereBufferCom = nullptr;
	CTransform*			m_pSphereTransCom = nullptr;

	MONSTERABILITY*		m_tAbility;
	
	_float				m_fUISwitchTime = 0.f;

protected:
	virtual void	Free(void)override;
};

