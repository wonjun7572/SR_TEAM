#pragma once

#include "Camera.h"
#include "Engine_Include.h"
#include "Export_Function.h"

class CStaticCamera : public Engine::CCamera
{
private:
	explicit CStaticCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CStaticCamera();

public:
	HRESULT Ready_Object(const _vec3* pEye, const _vec3* pAt, const _vec3* pUp,
		const _float& fFov,
		const _float& fAspect,
		const _float& fNear,
		const _float& fFar);


	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void LateUpdate_Object(void) override;

	const _matrix* GetViewmatrix()  { return &m_matView; }
	const _matrix* GetProjmatrix()  { return &m_matProj; }

	void		HitPlayer() { m_bPlayerHit = true; }

private:
	void		Key_Input(const _float& fTimeDelta);
	void		Mouse_Fix();
	void		Look_Target(const _float& _fTimeDelta);
	void		Camera_Shaking(const _float& _fTimeDelta);

private:
	CTransform*		m_pTransform_Target = nullptr;
	CTransform*		m_pBombTransform	= nullptr;

	_float			m_fDistance;
	_float			m_fSpeed = 10.f;
	_float			m_fAngle = 0.f;
	_bool			m_bChangePOV = false;

	_int			m_iReverse = 1;
	_float			m_fFrame = 0.f;
	_bool			m_bPlayerHit = false;

public:
	static CStaticCamera*		Create(LPDIRECT3DDEVICE9 pGraphicDev,
		const _vec3* pEye,
		const _vec3* pAt,
		const _vec3* pUp,
		const _float& fFov = D3DXToRadian(60.f),
		const _float& fAspect = (float)WINCX / WINCY,
		const _float& fNear = 0.1f,
		const _float& fFar = 1000.f);

private:
	virtual void Free(void) override;
};