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
	virtual ~CTestCube();
public:
	HRESULT				Ready_Object(int PosX, int PosY);
	HRESULT				Wall_Mapping(void);

	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		Render_Object(void) override;

	void				Set_TransformPositon();
	bool				Set_SelectGizmo();

	_bool*				Get_WireFrame() { return &m_bWireFrame; }
	void				Set_WireFrame(_bool bWireFrame) { m_bWireFrame = bWireFrame; }

private:
	HRESULT				Add_Component(void);

private:
	CCubeTex*			m_pBufferCom = nullptr;
	CTransform*			m_pTransCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CCalculator*		m_pCalculatorCom = nullptr;

	CHitBox*			m_pHitBox = nullptr;


	_bool					m_MappingInit = false;
	list<TCHAR*>			m_listWallCnt;
	CTransform*				m_pWallMapping = nullptr;

private:
	_bool				m_bWireFrame = false;

public:
	static CTestCube*		Create(LPDIRECT3DDEVICE9 pGraphicDev, int Posx = 0, int Posy = 0);

protected:
	virtual void Free();
};

