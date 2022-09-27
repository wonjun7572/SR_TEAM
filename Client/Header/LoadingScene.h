#pragma once
#include "Scene.h"
#include "Loading.h"
#include "Stage.h"
#include "BackGround.h"
#include "Texture.h"
class CLoadingScene :	public CScene
{

	enum RESOURCEID { RESOUCELOGO, RESOURCEEND };

public:
	CLoadingScene(LPDIRECT3DDEVICE9 pGraphicDev);
	~CLoadingScene();
public:
	virtual HRESULT Ready_Scene(void) override;
	virtual _int	Update_Scene(const _float& fTimeDelta) override;
	virtual void	Render_Scene(void) override;

private:
	HRESULT			Ready_Environment_Layer(const _tchar* pLayerTag);
	HRESULT			Ready_GameLogic_Layer(const _tchar* pLayerTag);
	HRESULT			Ready_UI_Layer(const _tchar* pLayerTag);
	HRESULT			Ready_Proto(void);
private:
	_matrix			m_matView, m_matProj;
	CLoading*		m_pLoading;
	_float          m_fLoadingCount = 0.f;
	_float			m_fLoadingCnt;


public:
	static CLoadingScene*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void	Free(void) override;
};