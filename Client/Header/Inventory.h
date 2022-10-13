#pragma once
#include "ItemIcon.h"
#include "RcEffect.h"
#include "GameObject.h"
#include "Weapon.h"
USING(Engine)

class CInventory : public CGameObject
{
private:
	explicit CInventory(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CInventory();

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;
	_bool			Get_Switch(void)  { return m_bInvSwitch; }
	_int			Get_EnforceCheck(void) { return m_iEnforceCheck; }

	void         ItemCreate(_int iItemIndex) 
	{ 
		m_bItemCreate = true; 
		m_iItemIndex = iItemIndex; 
	}
	void         WeaponCreate(_int iItemIndex)
	{
		m_bWeaponCreate = true;
		m_iItemIndex = iItemIndex;
	}

private:
	HRESULT		Add_Component();
	void		Begin_OrthoProj();
	void		End_OrthoProj();	
	void		Key_Input();
	void		Mouse();
	void		Sorting();
	void		Equipment_Sorting();
	void		Weapon_Sorting();
	void		Get_Item();
	void		Equipment_Function();
	//void		Gun_Change();

private:
	CGameObject*		m_pPlayer = nullptr;
	CGameObject*		m_pItemIcon = nullptr;
	CItemIcon*			m_pIconGrab = nullptr;
	CTransform*			m_pTransformCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CRcTex*				m_pRcTexCom = nullptr;
	CWeapon*			m_pWeapon = nullptr;
	_matrix		 		m_matWorld;
	_matrix				m_matView;
	_matrix				m_matProj;	

	vector<CGameObject*>  m_vecContents;
	vector<CGameObject*>  m_vecEquipments;
	vector<CGameObject*>  m_vecWeapon;
	vector<CGameObject*>  m_vecParts;
private:
	_bool				m_bInit = false;
	_bool				m_bNull = false;
	_bool				m_bInvSwitch = false;
	_bool				m_bSorting = false;
	_bool				m_bNullSorting = false;
	_bool				m_bItemCreate = false;
	_bool				m_bWeaponCreate = false;
	_int				m_iItemCnt = 0;
	_int				m_iWeaponCnt = 0;
	_int				m_iEnforceCheck = 0;
	_int				iVectorNumb = 0;
	_int				iWeaponNumb = 0;
	_int				m_iItemIndex = 1;
	_float				m_fInvPosX = 0.f;
	_float				m_fInvPosY = 0.f;
	// m_fInvPosX + WINCX / 2  인벤토리 원점의 위치

public:
	static CInventory*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	void				Free(void)	override;

};

