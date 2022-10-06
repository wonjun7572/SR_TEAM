#pragma once
#include "GameObject.h"

USING(Engine)
class CInventory;

class CItemIcon :
	public CGameObject
{
private:
	explicit CItemIcon(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CItemIcon();

public:
	virtual HRESULT Ready_Object(_int iIndex) ;
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;

	

public:
	void		Maker(CItemIcon* pInstance)
	{
		Engine::Add_GameObject(STAGE_UI, pInstance, szCntName);
	}
	void		Set_block(_vec3 vBlockPos) { m_vBlockPos = vBlockPos; }
	void		Set_block(_float vBlockPosX, _float vBlockPosY, _float vBlockPosZ) { m_vBlockPos.x = vBlockPosX, m_vBlockPos.y = vBlockPosY, m_vBlockPos.z = vBlockPosZ; }
	void 		Set_Texture(_int iTexIndex) { m_iTexIndex = iTexIndex; }
	void		Cursor_fix(void) { m_bFix = true; }
	void		Cursor_free(void) { m_bFix = false; }
	_tchar*		Get_Name() { return szCntName; }

private:
	HRESULT		Add_Component();
	void		Begin_OrthoProj();
	void		End_OrthoProj();
	void		Index();
	void		FixOnCursor();
private:
	
	CGameObject*	 m_pPlayer = nullptr;
	CTransform*		 m_pTransformCom = nullptr;
	CTexture*		 m_pTextureCom = nullptr;
	CTexture*		 m_pCursorTextureCom = nullptr;

	CRcTex*			 m_pRcTexCom = nullptr;	
	CItemIcon*		 m_pDeleter = nullptr;

	_matrix	 		 m_matWorld;
	_matrix			 m_matView;
	_matrix			 m_matProj;

	list<TCHAR*>	 m_listItemIcon;
	_tchar			 szCntName[64];



private:
	_int			m_iIndex = 0;
	_int			m_iTexIndex = 0;
	_bool			m_bInit = false;
	_bool			m_bFix =  false;
	_vec3			m_vBlockPos;

	_vec3			m_vIconPos;
	_float			m_fImgX = 0.f;
	_float			m_fImgY = 0.f;
	_float			m_fImgZ = 0.002f;
public:
	static CItemIcon*	Create(LPDIRECT3DDEVICE9 pGraphicDev, _int iIndex);
	void				Free(void)	override;

};

