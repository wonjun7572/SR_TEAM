#pragma once
#include "ItemIcon.h"
#include "GameObject.h"

USING(Engine)

class CInventory :
	public CGameObject
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

private:
	HRESULT		Add_Component();
	void		Begin_OrthoProj();
	void		End_OrthoProj();	
	void		Key_Input();
	void		Mouse();
	void		Equipment();
	void		Sorting();
	void		Get_Item();


private:
	CGameObject*		m_pPlayer = nullptr;
	CGameObject*		m_pItemIcon = nullptr;
	CItemIcon*			m_pIconGrab = nullptr;

	CTransform*			m_pTransformCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CRcTex*				m_pRcTexCom = nullptr;

	_matrix		 		m_matWorld;
	_matrix				m_matView;
	_matrix				m_matProj;	

	list<CGameObject*>	  m_listEqiupments;
	vector<CGameObject*>  m_vecContents;
	vector<CGameObject*>  m_vecEquipments;
private:
	_bool				m_bInit = false;
	_bool				m_bNull = false;
	_bool				m_bInvSwitch = false;
	_bool				m_bKeyDown = false;
	_bool				m_bRBDown = false;
	_bool				m_bLBDown = false;
	_bool				m_bSorting = false;
	_bool				m_bNullSorting = false;
	_int				m_iItemCnt = 0;
	_int				iVectorNumb = 0;


public:
	static CInventory*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	void				Free(void)	override;

};
