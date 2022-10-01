#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer : public CComponent
{
protected:
	explicit CVIBuffer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CVIBuffer(const CVIBuffer& rhs);
	virtual ~CVIBuffer();

public:
	virtual HRESULT		Ready_Buffer(void);
	virtual void		Render_Buffer(void);

protected:

	LPDIRECT3DVERTEXBUFFER9		m_pVB;		// �������� �����ϰ� �����ϱ� ���� �İ�ü
	LPDIRECT3DINDEXBUFFER9		m_pIB;		// �������� �ε��� ���� �����ϱ� ���� �İ�ü

	_ulong						m_dwVtxCnt;			// ���ؽ� ����
	_ulong						m_dwVtxSize;		// ���ؽ� ũ��
	_ulong						m_dwFVF;			// ���ؽ��� �Ӽ� ������ �����ϴ� �ɼ�
	_ulong						m_dwTriCnt;			// �ﰢ���� ����

	_ulong						m_dwIdxSize;
	D3DFORMAT					m_IdxFmt;
	
public:
	virtual void		Free(void);

};

END