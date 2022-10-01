#pragma once
#include "GameObject.h"
#include "Export_Function.h"
class CLetterBox :
	public CGameObject
{
private:
	explicit CLetterBox(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLetterBox();

public:
	virtual HRESULT Ready_Object(_tchar* tDialogue, _int iIndex) ;
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;

private:
	HRESULT			Add_Component(void);
	void			Begin_OrthoProj();
	void			End_OrthoProj();
private:
	CTransform*		m_TranformCom = nullptr;
	CTexture*		m_pFontTexture = nullptr;
	CTexture*		m_pTexture = nullptr;
	CCubeTex*		m_pCube = nullptr;
	CRcTex*			m_pRcCom = nullptr;
	_matrix			m_matWorld;
	_matrix			m_matView;
	_matrix			m_matProj;
	wstring			m_strLetter2;

	
public:
	static CLetterBox*	Create(LPDIRECT3DDEVICE9 pGraphicDev, _tchar* tDialogue, _int iIndex);
	virtual void Free(void) override;
};


