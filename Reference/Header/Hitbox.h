#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CHitBox : public CVIBuffer
{
private:
	explicit CHitBox(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CHitBox(const CHitBox& rhs);
	virtual ~CHitBox();

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

public:
	static CHitBox*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	CComponent*	Clone(void);
	virtual void Free(void) override;
};

END