#pragma once
#include "PSystem.h"

class CRainbowCloud : public CPSystem
{
protected:
	explicit CRainbowCloud(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CRainbowCloud();

public:
	virtual		HRESULT		Ready_Object(void);
	virtual		_int		Update_Object(const _float& fTimeDelta);
	virtual		void		LateUpdate_Object(void);
	virtual		void		Render_Object(void);
	void					Set_PclePos(_vec3 _vPos) { vRainbowCloudPos = _vPos; }

public:
	HRESULT						Add_Component(void);
	static CRainbowCloud*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual		void			Free(void);

private:
	_vec3					vRainbowCloudPos = { 0.f, 0.f, 0.f };

public:
	virtual		void		resetParticle(ATTRIBUTE* attribute);
};

