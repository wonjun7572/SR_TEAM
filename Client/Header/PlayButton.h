#pragma once
#include "GameObject.h"
#include "Engine_Include.h"

#include "Scene.h"
#include "Loading.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;
class CScene;

END

class CPlayButton :	public CGameObject
{
public:
	CPlayButton(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPlayButton();

public:
	virtual HRESULT Ready_Object() override;
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;

public:
	_bool	Get_MouseCheck(void) { return Mouse_check; }
	_bool	Get_Checking(void) { return Checking; }
private:
	HRESULT				Add_Component(void);

private:
	CRcTex*			m_RcTexCom = nullptr;
	CTransform*		m_TranformCom = nullptr;
	CTexture*		m_TextureCom = nullptr;
	CTexture*		m_CheckTextureCom = nullptr; 
	CLoading*		m_pLoading = nullptr;


private:
	void		Begin_OrthoProj();
	void		End_OrthoProj();



public:
	static CPlayButton*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	_bool		Mouse_check = false;
	_bool		Checking = false; 
	_bool		PointMouse(void);
	_matrix m_matWorld;
	_matrix m_matView;
	_matrix m_matProj;
	//텍스처 인덱스 번
	_int	m_iIndex = 0;
	wstring m_strPB;
private:
	virtual void Free(void);
};

