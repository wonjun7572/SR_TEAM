#pragma once
#include "GameObject.h"
#include "Engine_Include.h"
#include "Loading.h"

#include "Scene.h"
#include "Loading.h"
BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;
class CScene;


class CPlayButton :	public CGameObject
{

public:
	CPlayButton(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPlayButton();



public:
	virtual HRESULT Ready_Object() override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void LateUpdate_Object(void) override;
	virtual void Render_Object(void) override;

public:

	_bool	Get_MouseCheck(void) { return Mouse_check; }

private:
	HRESULT				Add_Component(void);

private:
	CRcTex*			m_RcTexCom = nullptr;
	CTransform*		m_TranformCom = nullptr;
	CTexture*		m_TextureCom = nullptr;

	CLoading*		m_pLoading = nullptr;



public:
	static CPlayButton*		Create(LPDIRECT3DDEVICE9 pGraphicDev);



private:
	_bool		Mouse_check = false;
	_bool		PointMouse(void);
private:

	virtual void Free(void);
};

END
