#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CCubeTex : public CVIBuffer
{
private:
	explicit CCubeTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCubeTex(const CCubeTex& rhs);
	virtual ~CCubeTex();

public:
	virtual HRESULT Ready_Buffer(void) override;
	virtual void Render_Buffer(void) override;

	const _vec3*		Get_VtxPos(void) const { return m_vPos; }
	//	�ش� �Լ� ���� ������ �Ѱܹ޾Ƽ� ����� ��!
	_vec3*				Get_Flexible_Vtx(void) { return m_vPos; }

private:
	_vec3*		m_vPos;
	_bool		m_bClone;
public:
	static CCubeTex*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	CComponent*	Clone(void);
	virtual void Free(void) override;
};

END