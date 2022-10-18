#pragma once
#include "Supporter.h"

class CSupporter_Sniper :
	public CSupporter
{
private:
	explicit CSupporter_Sniper(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSupporter_Sniper();

public:
	virtual HRESULT		Ready_Object(const _vec3& vPos, _tchar* Name);
	virtual _int		Update_Object(const _float& fTimeDelta);
	virtual void		LateUpdate_Object(void);
	virtual void		Render_Object(void);
	void				SetOrdered(_bool bGetOrder) { m_bGetOrder = bGetOrder; }

	_bool				Get_setcam() { return m_bSetCam; }
	void				Set_setcam(_bool bcam) { m_bSetCam = bcam; }
private:
	HRESULT				Add_Component(void);
	void				Look_Direction(void);
	void				Find_Target(void);

private:	//	애니메이션 관련
	HRESULT				Build(void);
	void				Load_Animation(wstring FileName, _uint AnimationID);
	void				Run_Animation(const _float& AnimationSpeed);

	void				IDLE_Animation_Run(void);
	void				WALK_Animation_Run(void);
	void				ATTACK_Animation_Run(void);

	void				DROP_Animation_Run(void);

	_float				m_fTimeDelta = 0.f;
	_bool				m_bFirst = true;
	_float				m_AnimationTime = 0.f;

	CLayer*				pMyLayer;
	_tchar*				m_SupporterName;

	_bool				m_bGetOrder = false;
	_bool				m_bOrdering = false;

	_vec3				m_vOrderPos = _vec3(0.f, 0.f, 0.f);

	_bool				m_bSetCam = true;

	SNIPERSUPPORTSTATEID	m_STATE;
	SNIPERSUPPORTIDLEID		m_IDLE;
	SNIPERSUPPORTWALKID		m_WALK;
	SNIPERSUPPORTATTACKID	m_ATTACK;
	SUPPORTDROPID			m_DROP;

public:
	static CSupporter_Sniper*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos, _tchar* Name);
	virtual void				Free(void);
};

