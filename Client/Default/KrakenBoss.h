#pragma once
#include "GameObject.h"
class CKrakenBoss :
	public CGameObject
{
public:
	CKrakenBoss(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CKrakenBoss();


public:
	virtual	HRESULT Ready_Object(const _vec3& vPos, _tchar* Name);
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	Render_Object(void) override;
	virtual void	LateUpdate_Object(void) override;



	//애니메이션 관련
private:
	KRAKENSTATEID	m_STATE;
	KRAKENSTATEID   m_BeforeState;
	KRAKENWALKID	m_WALK;
	KRAKENIDLEID	m_IDLE;
	KRAKENATTACKID	m_ATTACK;
	KRAKENSHOTID	m_SHOT;


protected:
	CTransform*			m_pTransCom = nullptr;
	CTransform*			m_pTransUICom = nullptr;
	CTransform*			m_pHitBoxTransCom = nullptr;
	CTransform*			m_pSphereTransCom = nullptr;
	CTransform*			m_pMonsterMapping = nullptr;
	CTransform*			m_pPlayerTransCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CCubeTex*			m_pBufferCom = nullptr;
	CSphereTex*			m_pSphereBufferCom = nullptr;
	CMonsterUI*			m_pMonsterUI = nullptr;
	CRcTex*				m_pBufferUICom = nullptr;
	CTexture*			m_pTextureUICom = nullptr;
	CHitBox*			m_pHitBox = nullptr;
	CCollision*			m_pCollision = nullptr;
	CComboUI*			m_pComboUI = nullptr;


	//기능관련 
private:
	HRESULT				Add_Component(void);
	KRAKENABILITY*		m_tAbility;
	_tchar*				m_MonsterName;




public:
	static CKrakenBoss*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos, _tchar* Name);
	virtual void	Free(void);
};

