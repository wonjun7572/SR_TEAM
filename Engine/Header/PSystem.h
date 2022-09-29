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

	virtual void Reset();
	virtual void ResetParticle(ATTRIBUTE* attribute)PURE;
	virtual void AddParticle();

	virtual void Update();

	virtual void PreRender();
	virtual void PostRender();

	bool isEmpty();
	bool isDead();

protected:
	virtual void RemoveDeadParticles();

public:
	static CPSystem*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	CComponent*	Clone(void);
	virtual void Free(void) override;

protected:
	_vec3			m_vOrigin;
	BoundingBox		m_bBoundingBox;
	_float			m_fEmitRate;
	_float			m_fSize;
	list<ATTRIBUTE> m_Pariclelist;
	_int			m_iMaxParticles;
	 
	_ulong	m_dwVbSize;
	_ulong  m_dwVbOffset;
	_ulong	m_dwVbBatachSize;
};

END