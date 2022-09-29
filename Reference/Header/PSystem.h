#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class CPSystem : public CVIBuffer
{
private:
	explicit CPSystem(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPSystem(const CPSystem& rhs);
	virtual ~CPSystem();

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;


public:
	static CPSystem*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	CComponent*	Clone(void);
	virtual void Free(void) override;

protected:
	_vec3			m_vOrigin;
	BoundingBox		m_bBoundingBox;
	_float			m_fEmitRate;
	_float			m_fSize;
	list<ATTRIBUTE> m_aParicle;
	_int			m_iMaxParticles;
	 
	_ulong	m_dwVbSize;
	_ulong  m_dwVbOffset;
	_ulong	m_dwVbBatachSize;
};

END