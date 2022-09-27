#pragma once
#include "Scene.h"
#include "BackGround.h"
#include "Logo.h"
class CMovieScene :	public CScene
{
public:
	CMovieScene(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMovieScene();

public:
	virtual HRESULT Ready_Scene(void) override;
	virtual _int	Update_Scene(const _float& fTimeDelta) override;
	virtual void	Render_Scene(void) override;

private:
	HRESULT			Ready_Environment_Layer(const _tchar* pLayerTag);
	HRESULT			Ready_GameLogic_Layer(const _tchar* pLayerTag);
	HRESULT			Ready_UI_Layer(const _tchar* pLayerTag);
	HRESULT			Ready_Proto(void);

public:

	static CMovieScene*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	CLoading*	 m_pLoading = nullptr;
private: 
	virtual void		Free(void);

};

