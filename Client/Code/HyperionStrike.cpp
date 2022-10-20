#include "stdafx.h"
#include "..\Header\HyperionStrike.h"
#include "PoolMgr.h"
#include "BattleCursier.h"
CHyperionStrike::CHyperionStrike(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CHyperionStrike::~CHyperionStrike()
{
}

HRESULT CHyperionStrike::Ready_Object(const _vec3 & Position, DIRRECTIONSTATE _eDir)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_eDir = _eDir;
	m_iSphereSkillTag = SKILL_HYPERIONSTRIKE;
	m_fSphereScale = 20.f;							//ũ��
	m_fDuration = 10.f;								//���ӽð�
	m_fSpeed = 0.05f;								//�ӵ�
	m_vDirection = { 1.f,0.f,0.f };					//����
	if (m_eDir == DIR_PX)
		m_vDirection = { 1.f,0.f,0.f };					//����
	if (m_eDir == DIR_MX)
		m_vDirection = { -1.f,0.f,0.f };					//����
	if (m_eDir == DIR_PZ)
		m_vDirection = { 0.f,0.f,1.f };					//����
	if (m_eDir == DIR_MZ)
		m_vDirection = { 0.f,0.f,-1.f };					//����
	m_vDirection *= m_fSpeed;
	m_pTransCom->Set_Pos(Position.x, Position.y, Position.z);
	m_pTransCom->Set_Scale(&_vec3(m_fSphereScale, m_fSphereScale, m_fSphereScale));
	m_pTransCom->Get_Info(INFO_POS, &m_vPos);
	_float fGunSound = 1.f;
	Engine::PlaySoundGun(L"BattleCruiser.wav", SOUND_EFFECT, fGunSound);
	Engine::PlaySoundGun(L"BattleCruiser2.wav", SOUND_EFFECT, fGunSound);
	return S_OK;
}

_int CHyperionStrike::Update_Object(const _float & fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_UI, this);

	m_fAge += fTimeDelta;
	m_fBlinkTimer += fTimeDelta;
	m_pTransCom->Get_Info(INFO_POS, &m_vPos);
	Recall_BattleCruiser();
	Bullet_Rain();
	Move_Location();
	

	if (m_fAge > m_fDuration)
	{			
		m_bDead = true;
		for (auto& iter : Engine::Get_Layer(STAGE_SKILLCRUISER)->Get_GameList())
		{
			dynamic_cast<CBattleCursier*>(iter)->Replace({ 0.f,0.f,0.f }, { 3.f,0.f, 3.f }, m_vDirection);//Z��-
		}
		return -1;
	}
	return 0;
}

void CHyperionStrike::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CHyperionStrike::Render_Object(void)
{
	if (m_fBlinkTimer < 0.25f)	 // �����ִ� �ð�
	{
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);
		m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
		m_pTexture->Set_Texture();
		m_pSphereTex->Render_Buffer();

		m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
		m_pSphereTex2->Render_Buffer();
		m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}
	if (m_fBlinkTimer > .75f)	// �����ִ� �ð�
	{
		m_fBlinkTimer = 0.f;
	}
}

HRESULT CHyperionStrike::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });

	pComponent = m_pSphereTex = dynamic_cast<CSphereTex*>(Engine::Clone_Proto(SPHERETEX_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ SPHERETEX_COMP, pComponent });

	pComponent = m_pSphereTex2 = dynamic_cast<CSphereTex*>(Engine::Clone_Proto(SPHERETEX_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_SphereTexCom2", pComponent });

	pComponent = m_pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Brown_Tex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Brown_Tex", pComponent });

	return S_OK;
}

void CHyperionStrike::Recall_BattleCruiser(void)
{
	CGameObject* pGameObject = nullptr;
	m_vBattlePos = m_vPos;
	//m_vBattlePos.y = 8.f;
	m_vBattlePos.y = 12.f;

	for (auto& iter : Engine::Get_Layer(STAGE_SKILLCRUISER)->Get_GameList())
	{
		if (m_eDir == DIR_PX || m_eDir == DIR_END)
			dynamic_cast<CBattleCursier*>(iter)->Replace(m_vBattlePos, { 2.f,1.5f, 2.f }, m_vDirection); // X��+ �ٶ󺸴°�
		if (m_eDir == DIR_MX)
			dynamic_cast<CBattleCursier*>(iter)->Replace(m_vBattlePos, { 10,55, 10}, m_vDirection);//X��- �ٶ󺸴°�
		if (m_eDir == DIR_PZ)
			dynamic_cast<CBattleCursier*>(iter)->Replace(m_vBattlePos, { 1.f , 0.f, 0.f }, m_vDirection); // Z��+		
		if (m_eDir == DIR_MZ)
			dynamic_cast<CBattleCursier*>(iter)->Replace(m_vBattlePos, {3,0, 3 }, m_vDirection);//Z��-
	}	
}

void CHyperionStrike::Bullet_Rain(void)
{
	
	_float fRnd = (-50.f + rand() % 100) *0.015f;
	_float fRnd2 = (-50.f + rand() % 100) *0.015f;

	_vec3 vDir = { fRnd, -1.f, fRnd2 };	

	//CPoolMgr::GetInstance()->Reuse_Obj(m_pGraphicDev, &m_vBattlePos, &vDir, 10.f);
	CPoolMgr::GetInstance()->Reuse_Laser(m_pGraphicDev, &(m_vBattlePos+ m_vDirection*100.f), &vDir, 5,1);
	_float fGunSound = .3f;
	Engine::PlaySoundGun(L"BattleCruiserAtk.wav", SOUND_EFFECT, fGunSound);
	
}

void CHyperionStrike::Move_Location(void)
{
	if (!m_bMove)
	{		
		m_pTransCom->Move_Pos(&m_vDirection);
	}
}

CHyperionStrike * CHyperionStrike::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & Position, DIRRECTIONSTATE _eDir)
{
	CHyperionStrike* pInstance = new CHyperionStrike(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(Position, _eDir)))
	{
		MSG_BOX("CHyperionStrike Object Create Fail");
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CHyperionStrike::Free(void)
{
	CGameObject::Free();
}
