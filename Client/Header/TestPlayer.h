#pragma once
#include "GameObject.h"

namespace Engine
{
	class CTransform;
	class CCubeTex;
	class CTexture;
	class CCalculator;
}

class CWall;

class CTestPlayer : public CGameObject
{
private:
	explicit CTestPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTestPlayer();

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;

private:
	HRESULT				Add_Component(void);
	void				Key_Input(const _float& fTimeDelta);
	void				Set_OnTerrain();

	void				Create_Wall(const _uint& iCnt, const _uint& iTextureNum);

	void				Fire_Bullet(const _vec3* pDir);

	/////////////////////////////////////////////////
	_vec3				Mouse_Peeking(void);
	/////////////////////////////////////////////////

private:
	CCubeTex*			m_pBufferCom = nullptr;
	CTransform*			m_pTransCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CCalculator*		m_pCalculatorCom = nullptr;

	_vec3				m_vDirection;

private:
	list<TCHAR*>		m_liszFinalName;
	_uint				m_iCnt = 0;

public:
	static CTestPlayer*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void	Free(void);
};

