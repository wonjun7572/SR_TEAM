#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CCubeCol : public CVIBuffer
{
private:
	explicit CCubeCol(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCubeCol(const CCubeCol& rhs);
	virtual ~CCubeCol();

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

	const _vec3*		Get_VtxPos(void) const { return m_vPos; }
	//	해당 함수 사용시 변수에 넘겨받아서 사용할 것!
	_vec3*				Get_Flexible_Vtx(void) { return m_vPos; }

private:
	_vec3*		m_vPos;
	_bool		m_bClone;

public:
	static CCubeCol*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	CComponent*	Clone(void);
	virtual void Free(void) override;
};

END