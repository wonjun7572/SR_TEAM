#pragma once
#include "GameObject.h"
#include "MonsterParticle.h"
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
	void				Update_NullCheck();
	
	HRESULT				Interact(void);

private:
	HRESULT				Add_Component(void);

private:
	CCubeTex*			m_pBufferCom = nullptr;
	CTransform*			m_pTransCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	

	CCalculator*		m_pCalculatorCom = nullptr;

	CHitBox*			m_pHitBox = nullptr;

private: // 맵핑 관련
	_bool					m_bMappingInit = false;
	list<TCHAR*>			m_listWallCnt;
	list<TCHAR*>			m_listWallCnt2;
	list<TCHAR*>			m_listLetterCnt;
	CTransform*				m_pWallMapping = nullptr;

private:
	_bool				m_bWireFrame = false;

private: // 문 상호작용 관련
	_int				m_CubeIndex = 0;
	_bool				m_bSwitch = false;
	_bool				m_bLetterboxInit = false;
	_bool				m_bDoorOpen = false;
	wstring				m_strPress;
	CGameObject*		m_pLetterBox = nullptr;

	CMonsterParticle* m_pMonsterParticle = nullptr;

public:
	static CTestCube*		Create(LPDIRECT3DDEVICE9 pGraphicDev, int Posx = 0, int Posy = 0);

protected:
	virtual void Free();
};

