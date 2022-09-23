#pragma once
#include "Component.h"

BEGIN(Engine);

class ENGINE_DLL CCollision : public CComponent
{
private:
	explicit CCollision(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCollision(const CCollision& rhs);
	virtual ~CCollision();

public:
	HRESULT					Ready_Collision(void);
	_bool					Check_Collision(void);

public:
	static CCollision* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(void);
	virtual void Free(void);
};

END