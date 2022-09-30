#pragma once

#include "Scene.h"
#include "SkyBox.h"
#include "Terrain.h"
#include "TestPlayer.h"
#include "StaticCamera.h"
#include "DynamicCamera.h"
#include "DynamicCamera.h"
class CStage : public Engine::CScene
{
private:
	explicit CStage(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CStage();

public:
	virtual HRESULT Ready_Scene(void) override;
	virtual _int Update_Scene(const _float& fTimeDelta) override;
	virtual void LateUpdate_Scene(void) override;
	virtual void Render_Scene(void) override;

private:
	HRESULT			Ready_Layer_Environment(const _tchar* pLayerTag);
	HRESULT			Ready_Layer_GameLogic(const _tchar* pLayerTag);
	HRESULT			Ready_Layer_UI(const _tchar* pLayerTag);

	HRESULT			Ready_Layer_Wall(const _tchar* pLayerTag);
	HRESULT			Ready_Layer_Character(const _tchar* pLayerTag);
	HRESULT			Ready_Layer_Monster(const _tchar* pLayerTag);
	HRESULT			Ready_Layer_Bullet(const _tchar* pLayerTag);

	HRESULT			Ready_Layer_Gun(const _tchar* pLayerTag);

	HRESULT			Ready_Layer_Item(const _tchar* pLayerTag);

	HRESULT			Ready_Proto(void);
	HRESULT			Ready_Light(void);

private:
	////////////¸Ê ÆÄ½Ì
	_int			m_iIndex = 0;
	list<_tchar* >	NameList;

public:
	static CStage*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	CDynamicCamera* m_pCam = nullptr;

private:
	virtual void	Free(void);
};

