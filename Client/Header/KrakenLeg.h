#pragma once
#include "GameObject.h"

class CMonsterUI;
class CComboUI;

class CKrakenLeg :
	public CGameObject
{
private:
	explicit CKrakenLeg(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CKrakenLeg();

public:
	virtual	HRESULT Ready_Object(const _vec3& vPos, _tchar* Name);
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	Render_Object(void) override;
	virtual void	LateUpdate_Object(void) override;

private:
	void				Look_Direction(void);
	virtual _int		Update_Pattern(_float fTimeDelta);
	void				Hit_Check(_float _deltaTime);

private:
	HRESULT				Build(void);
	void				Load_Animation(wstring FileName, _uint AnimationID);
	void				Run_Animation(const _float& AnimationSpeed);

	void				Lurker_Pattern(void);

private:
	void				APPEAR(void);
	void				IDLE_Animation_Run(void);
	void				SMASH_Animation_Run(void);
	void				SHAKE_Animation_Run(void);

private:
	KRAKENSTATEID		m_STATE;
	KRAKENIDLEID		m_IDLE;
	KRAKENAPPEARID		m_APPEAR;
	KRAKENSMASHID		m_SMASH;
	KRAKENINKSHOTID		m_INKSHOT;
	KRAKENROLLINGID		m_ROLLING;
	KRAKENLURKERID		m_LURKER;
	KRAKENSKILLID		m_PATTERN;

	KRAKENLEGIDLEID		m_LEGIDLE;
	KRAKENLEGSHAKEID	m_LEGSHAKE;

protected:
	HRESULT				Add_Component(void);
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
	CCalculator*		m_pCalculatorCom = nullptr;
	CTexture*			m_pTextureUICom = nullptr;
	CHitBox*			m_pHitBox = nullptr;
	CCollision*			m_pCollision = nullptr;
	CComboUI*			m_pComboUI = nullptr;
	CLayer*				pMyLayer;
	CCubeCol*			m_pAnimationBox = nullptr;

private:
	KRAKENABILITY*		m_tAbility;
	_tchar*				m_MonsterName;
	_bool				m_bFirst = true;
	list<_tchar*>		m_TcharList;

	vector<KRAKENSKILLID>	m_vPattern;

private:
	_float				m_ReloadTimer = 0.f;
	_float				m_AnimationTime = 0.f;
	_float				m_fTimeDelta = 0.f;
	_float				m_fUISwitchTime = 0.f;
	_vec3				vUIPos;
	_bool				m_bLurker = true;
	_float				m_fLurkerTime = 0.f;
	_vec3				vDir;
	_float				m_fLerpTime = 0.f;
	_vec3				m_vOriginPos;
	vector<_float>		m_ShufflePos;

public:
	static CKrakenLeg*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos, _tchar* Name);
	virtual void		Free(void);
};
