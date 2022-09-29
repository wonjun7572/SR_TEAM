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
	void			Get_HitboxMin(_vec3* vMin, _vec3* vMax)
	{
		D3DXVec3TransformCoord(vMin, &m_vMin, m_pTransCom->Get_WorldMatrixPointer());
		D3DXVec3TransformCoord(vMax, &m_vMax, m_pTransCom->Get_WorldMatrixPointer());

		//cout << vMin->x << " " << vMin->y << " " << vMin->z << "     " << vMax->x << " " << vMax->y << " " << vMax->z << endl;
	}

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

	CHitBox*			m_pHitBox = nullptr;

	_vec3				m_vDirection;

	_vec3				m_vMin = { 0,0,0 };
	_vec3				m_vMax = { 0,0,0 };

	_vec3				vT1 = { 0,0,0 };
	_vec3				vT2 = { 0,0,0 };

private:
	list<TCHAR*>		m_liszFinalName;
	_uint				m_iCnt = 0;

public:
	static CTestPlayer*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void	Free(void);
};

