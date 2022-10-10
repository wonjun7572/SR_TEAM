#pragma once
#include "GameObject.h"

namespace Engine
{
	class CTransform;
	class CCubeTex;
	class CTexture;
	class CCalculator;
	class CQuarternion;
}

class CTransAxisBox : public CGameObject
{
private:
	explicit CTransAxisBox(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTransAxisBox();

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;

public:
	bool			Set_SelectGizmo(void);
	CTransform*		Get_Transform(void) { return m_pTransCom; }
	CTransform*		Get_Parent(void) { return m_pParentTransform; }
	void			Set_Parent(CTransform* pTransform) { m_pParentTransform = pTransform; }
	void			ParentSettingStart(void) { bParentSetting = true; }

public:
	void			Set_Axis(_float& fX, _float fY, _float fZ) { m_fX = fX, m_fY = fY, m_fZ = fZ; }
	_float			Get_X(void) { return m_fX; }
	_float			Get_Y(void) { return m_fY; }
	_float			Get_Z(void) { return m_fZ; }

public:
	list<CTransAxisBox*>	m_ParentList;
	list<_tchar*>			m_ParentKey;
	list<_tchar*>			m_ChildKey;
	_bool					m_bIsRoot;

private:
	HRESULT				Add_Component(void);
	CFlexibleAxisCube*	m_pBufferCom = nullptr;
	CTransform*			m_pTransCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CCalculator*		m_pCalculatorCom = nullptr;

	CTransform*			m_pParentTransform = nullptr;

	CQuarternion*		m_pQuaternion = nullptr;

private:
	_matrix				m_FinalWorldMatrix;

	_matrix				m_AxisMoveMatrix;		//	�� ������, ���� ���� ���� �ش� �̵����� ������
	void				AxisMatrixCreate(void);

	_float				m_fX, m_fY, m_fZ;

	_bool				bParentSetting;

public:
	static CTransAxisBox* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void Free(void);
};
