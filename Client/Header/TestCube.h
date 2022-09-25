#pragma once
#include "GameObject.h"

BEGIN(Engine)

class CTexture;
class CCubeTex;
class CTransform;
class CCalculator;

END

class CTestCube : public CGameObject
{
private:
	explicit CTestCube(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTestCube(const CGameObject& rhs);

public:
	HRESULT Ready_Object(int PosX, int PosY);
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	Render_Object(void) override;

	void				Set_TransformPositon();
	bool				Set_SelectGizmo();

	_bool*	Get_WireFrame() { return &m_bWireFrame; }
	void	Set_WireFrame(_bool bWireFrame) { m_bWireFrame = bWireFrame; }

private:
	HRESULT				Add_Component(void);

public:
	CCubeTex*			m_pBufferCom = nullptr;
	CTransform*			m_pTransCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CCalculator*		m_pCalculatorCom = nullptr;

private:
	_bool				m_bWireFrame = false;

public:
	static CTestCube*		Create(LPDIRECT3DDEVICE9 pGraphicDev, int Posx = 0, int Posy = 0);
};
