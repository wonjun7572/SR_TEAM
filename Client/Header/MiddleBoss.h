#pragma once
#include "GameObject.h"

class CMonsterUI;
class CComboUI;

class CMiddleBoss :
	public CGameObject
{
public:
	explicit CMiddleBoss(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMiddleBoss();

public:
	enum HP_Pattern { MIDDLE_IDLE, MIDDLE_WALK, MIDDLE_ATTACK_1, MIDDLE_ATTACK_2, MIDDLE_ATTACK_3, MIDDLE_DEATH, MIDDLE_END  };

	virtual	HRESULT Ready_Object(const _vec3& vPos);
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;
	void			Change_Pattern(HP_Pattern ePattern);
	virtual _int	Update_Pattern(_float fTimeDelta);
	void			Hit_Check(_float _deltaTime);

private:
	HRESULT				Create_Item();
	HRESULT				Monster_Mapping(void);
	HRESULT				Monster_DeleteMapping(void);

protected:
	CTransform*			m_pTransCom = nullptr;
	CTransform*			m_pTransUICom = nullptr;
	CTransform*			m_pHitBoxTransCom = nullptr;
	CTransform*			m_pSphereTransCom = nullptr;
	CTransform*			m_pMonsterMapping = nullptr;
	CTransform*			m_pPlayerTransCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CCubeTex*			m_pBufferCom = nullptr;
	CSphereTex*			m_pSphereBufferCom = nullptr;
	CMonsterUI*			m_pMonsterUI = nullptr;
	CRcTex*				m_pBufferUICom = nullptr;
	CTexture*			m_pTextureUICom = nullptr;
	CHitBox*			m_pHitBox = nullptr;
	CCollision*			m_pCollision = nullptr;
	CComboUI*			m_pComboUI = nullptr;


private:
	_float				m_fFrame = 0.f;
	_float				m_fTargetLength;
	_float				m_fDetectRange;
	_float				m_fAttackRange;
	_float				m_fUISwitchTime = 0.f;
	_float				m_fFireAngle = 0.f;
	_vec3				vUIPos;
	_bool				m_MappingInit = false;
	TCHAR*				m_szCntName = new TCHAR[64];
	list<TCHAR*>		m_listMonsterCnt;
private:
	HRESULT				Add_Component(void);
	MIDDLEBOSSABILITY*		m_tAbility;
	CMiddleBoss::HP_Pattern m_eCurPattern;
	CMiddleBoss::HP_Pattern m_ePrePattern;

public:
	static CMiddleBoss*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);
	virtual void	Free(void);


};

