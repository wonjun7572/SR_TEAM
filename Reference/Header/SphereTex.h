#pragma once
#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CSphereTex : public CVIBuffer
{
private:
	explicit CSphereTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSphereTex(const CSphereTex& rhs);
	virtual ~CSphereTex();

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

public:
	static CSphereTex*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	CComponent*	Clone(void);
	virtual void Free(void) override;
};

END