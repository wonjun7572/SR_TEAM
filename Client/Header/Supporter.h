#pragma once
#include "GameObject.h"

class CShotParticle;
class CBulletParticle;

class CSupporter :public CGameObject
{
protected:
	explicit CSupporter(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSupporter();

protected:
	virtual HRESULT		Ready_Object(const _vec3& vPos, wstring _strObjTag);
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object(void) override;
	virtual void		Render_Object(void) override;

protected:
	CTransform*			m_pTransform = nullptr;

	CHitBox*			m_pHitBox = nullptr;
	CTransform*			m_pHitBoxTransform = nullptr;

	CCalculator*		m_pCalculatorCom = nullptr;
	CCollision*			m_pCollision = nullptr;

	CSphereTex*			m_pSphereBufferCom = nullptr;
	CTransform*			m_pSphereTransCom = nullptr;

	CTransform*			m_pPlayerTransCom = nullptr;


	CBulletParticle*	m_pBulletParicle = nullptr;
	CShotParticle*		m_pShotParicle = nullptr;

protected:
	list<_tchar*>		m_TcharList;

protected:
	virtual void	Free(void)override;
};

