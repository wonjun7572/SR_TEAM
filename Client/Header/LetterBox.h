#pragma once
#include "GameObject.h"
#include "Export_Function.h"
class CLetterBox : public CGameObject
{
private:
	explicit CLetterBox(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLetterBox();

public:
	virtual HRESULT Ready_Object(_tchar* tDialogue, _int iSize, _int iIndex);
	virtual _int   Update_Object(const _float& fTimeDelta) override;
	virtual void   LateUpdate_Object(void) override;
	virtual void   Render_Object(void) override;

	void	ChangeLetterContents(const wstring& str , _int iSize)
	{
		m_strLetterContents = str;
		m_iTextAmount = iSize - 3;
	}

	void	LetterDead() { m_bDead = true; }

public:
	void         On_Switch() { m_bPowerSwitch = true; };
	void         Off_Switch() { m_bPowerSwitch = false; };
	void      Maker(CLetterBox* pInstance)
	{
		Engine::Add_GameObject(STAGE_UI, pInstance, szCntName);
	}
private:
	HRESULT        Add_Component(void);
	void         Alpha_Effect();
	void         Begin_OrthoProj();
	void         End_OrthoProj();
	// ��Ʈ ���� â �ε���
	// 0 : ȭ�� �߾� �Ʒ����� �����Ÿ��� ���ڿ� (�÷��̾� �˸�)
	// 1 : ȭ�� ������ ������ �����ϴ� ���ڿ� (�޺� ����ִ� ����)
	// 2 : ȭ�� �Ʒ��ʿ��� ���������� �ؽ��� ���� �������� ���ڿ� (��ȭ��, ����Ʈ)
	void         PlayerNotice();
	void         BoxText();
	void         Index1();
	void         HitCombo();
	void         DialogueBox();

private:
	CTransform*      m_TranformCom = nullptr;
	CTexture*		 m_pFontTexture = nullptr;
	CTexture*		 m_pTexture = nullptr;
	CCubeTex*		 m_pCube = nullptr;
	CRcTex*			 m_pRcCom = nullptr;
	_matrix			 m_matWorld;
	_matrix			 m_matView;
	_matrix			 m_matProj;
	wstring			 m_strLetterContents;
	_float			 m_fFontSize;
	_float			 m_fFontAlpha;
	//_tchar         m_strLetterName[64];
	_tchar           szCntName[64];

	_bool			m_bPowerSwitch = true;
	_bool			m_bAlphaSwitch = false;
	_int			m_iTextAmount;
	_int			m_iIndex;

public:
	static CLetterBox*   Create(LPDIRECT3DDEVICE9 pGraphicDev, _tchar* tDialogue, _int iSize, _int iIndex);
	virtual void Free(void) override;
};

