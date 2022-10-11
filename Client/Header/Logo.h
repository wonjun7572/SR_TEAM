#pragma once

#include "Scene.h"

class CLoading;
class CPlayButton;
class COptionButton;
class CExitButton;
class CLogoUI;

class CLogo : public Engine::CScene
{
private:
	explicit CLogo(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLogo();

public:
	virtual HRESULT Ready_Scene(void) override;
	virtual _int Update_Scene(const _float& fTimeDelta) override;
	virtual void LateUpdate_Scene(void) override;
	virtual void Render_Scene(void) override;

private:
	HRESULT         Ready_Layer_Environment(const _tchar* pLayerTag);
	HRESULT         Ready_Layer_GameLogic(const _tchar* pLayerTag) { return S_OK; }
	HRESULT         Ready_Layer_UI(const _tchar* pLayerTag);
	HRESULT         Ready_Proto(void);

private:
	CLoading*         m_pLoading = nullptr;
	CPlayButton*      m_PlayButton = nullptr;
	COptionButton*    m_OptionButton = nullptr;
	CExitButton*      m_ExitButton = nullptr;
	CLogoUI*          m_LogoUI = nullptr;

	_bool            m_bWireFrame = false;

	wstring			 m_strPB;
public:
	static CLogo*      Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void   Free(void);
};
