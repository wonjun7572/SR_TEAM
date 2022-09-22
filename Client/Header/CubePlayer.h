#pragma once
#include "GameObject.h"
#include "Export_Function.h"

USING(Engine)

class CCubePlayer : public CGameObject
{
private:
	explicit CCubePlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCubePlayer();

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;
private:
	map<const _tchar*, CGameObject*>	m_mapPlayerBody;

private:
	void			Key_Input(const _float& fTimeDelta);

private:
	HRESULT			Add_Component(void);
	CTransform*		m_pTransform = nullptr;

	CTransform*		m_pHeadWorld = nullptr;

	CTransform*		m_pBodyWorld = nullptr;

	CTransform*		m_pLeftArmWorld = nullptr;
	CTransform*		m_pRightArmWorld = nullptr;

	CTransform*		m_pLeftLegWorld = nullptr;
	CTransform*		m_pRightLegWorld = nullptr;

private:
	_float			m_fLookAngle = 0.f;

	_float			m_fAngle = 0.f;
	_bool			m_bWalkAngle = true;

public:
	static CCubePlayer*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void Free(void);
};

