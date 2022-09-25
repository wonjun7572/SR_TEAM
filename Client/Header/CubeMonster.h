#pragma once
#include "GameObject.h"
#include "Export_Function.h"

USING(Engine)

class  CCubeMonster : public CGameObject
{
public:
	explicit CCubeMonster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCubeMonster();


public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;

private:
	map<const _tchar*, CGameObject*>	m_mapMonsterBody;
private:

	void	Set_OnTerrain(void);
	void			Assemble(void);
	HRESULT			Get_BodyTransform(void);

private:
	HRESULT  Add_Component(void);

	CTransform*			m_pTransform = nullptr;
	//ÆÈ
	CTransform*			m_pMleftArm = nullptr;
	CTransform*			m_pMrightArm = nullptr;

	//¸öÅë
	CTransform*			m_pMbody = nullptr;

	//¶Ò¹è±â
	CTransform*			m_pMhead = nullptr;

	CCalculator*		m_pCalculator = nullptr;



public:
	static CCubeMonster*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void Free(void);

};

