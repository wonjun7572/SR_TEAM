#pragma once
#include "GameObject.h"

BEGIN(Engine)

class CTexture;
class CSphereTex;
class CTransform;
class CCalculator;

END

class CItem : public CGameObject
{
protected:
	explicit CItem(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CItem(const CGameObject& rhs);
	virtual ~CItem();

public:
	virtual HRESULT Ready_Object(const _vec3& vPos);
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object() override;
	virtual void	Render_Object()override;

protected:
	CTexture*	 m_pTextureCom = nullptr;
	CTransform*	 m_pTransCom = nullptr;
	CSphereTex*	 m_pBufferCom = nullptr;
	CCalculator* m_pCalculatorCom = nullptr;

protected:
	virtual void Free()override;
};

