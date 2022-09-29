#include "stdafx.h"
#include "..\Header\CubePlayer.h"
#include "PoolMgr.h"
#include "Bullet.h"

CCubePlayer::CCubePlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CCubePlayer::~CCubePlayer()
{
}

HRESULT CCubePlayer::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_tAbility = new ABILITY;
	m_tAbility->iDefence = 10;
	m_tAbility->iHp = 100;

	m_pTransform->Set_Scale(0.2f, 0.5f, 0.2f);

	ShowCursor(false);

	return S_OK;
}

_int CCubePlayer::Update_Object(const _float & fTimeDelta)
{
	m_fTimeDelta = fTimeDelta;

	FAILED_CHECK_RETURN(Get_BodyTransform(), -1);

	Move();

	Animation();

	TransAxis();

	Gun_Check();

	CGameObject::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CCubePlayer::LateUpdate_Object(void)
{
	if (!m_bJump)
		Set_OnTerrain();

	Look_Direction();

	Assemble();

	Fire_Bullet();

	//m_pHitBox->Get_MinMax(&m_vMin, &m_vMax);

	m_pCollision->Check_Collision();

	CGameObject::LateUpdate_Object();
}

void CCubePlayer::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DPMISCCAPS_CULLNONE);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pHitBox->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DPMISCCAPS_CULLCCW);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void CCubePlayer::Set_OnTerrain(void)
{
	m_pBodyWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"BODY", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pBodyWorld, );

	_vec3		vPos;
	m_pBodyWorld->Get_BeforeInfo(INFO_POS, &vPos);

	Engine::CTerrainTex*	pTerrainTexCom = dynamic_cast<Engine::CTerrainTex*>(Engine::Get_Component(L"Layer_Environment", L"Terrain", L"Proto_TerrainTexCom", ID_STATIC));
	NULL_CHECK(pTerrainTexCom);

	_float fHeight = m_pCalculatorCom->HeightOnTerrain(&vPos, pTerrainTexCom->Get_VtxPos(), VTXCNTX, VTXCNTZ) + 0.6f;

	m_pBodyWorld->Set_Pos(vPos.x, fHeight, vPos.z);
}

void CCubePlayer::Assemble(void)
{
	FAILED_CHECK_RETURN(Get_BodyTransform(), );

	_vec3 vBodyPos, vBodyAfterPos;
	m_pBodyWorld->Get_BeforeInfo(INFO_POS, &vBodyPos);
	m_pBodyWorld->Get_Info(INFO_POS, &vBodyAfterPos);

	m_pTransform->Set_Pos(vBodyPos.x, vBodyPos.y, vBodyPos.z);
	m_pHeadWorld->Set_Pos(vBodyPos.x, vBodyPos.y + 0.3f, vBodyPos.z);
	m_pLeftArmWorld->Set_Pos(vBodyPos.x - 0.15f, vBodyPos.y + 0.1f, vBodyPos.z);
	m_pRightArmWorld->Set_Pos(vBodyPos.x + 0.15f, vBodyPos.y + 0.1f, vBodyPos.z);
	m_pLeftLegWorld->Set_Pos(vBodyPos.x - 0.05f, vBodyPos.y - 0.3f, vBodyPos.z);
	m_pRightLegWorld->Set_Pos(vBodyPos.x + 0.05f, vBodyPos.y - 0.3f, vBodyPos.z);

	m_pLeftHandWorld->Set_Pos(vBodyPos.x - 0.15f, vBodyPos.y - 0.1f, vBodyPos.z);
	m_pRightHandWorld->Set_Pos(vBodyPos.x + 0.15f, vBodyPos.y - 0.1f, vBodyPos.z);
	m_pLeftFootWorld->Set_Pos(vBodyPos.x - 0.05f, vBodyPos.y - 0.5f, vBodyPos.z);
	m_pRightFootWorld->Set_Pos(vBodyPos.x + 0.05f, vBodyPos.y - 0.5f, vBodyPos.z);

	if (m_bFirst)
	{
		m_bFirst = false;

		m_pLeftArmWorld->Static_Update();
		m_pRightArmWorld->Static_Update();
		m_pLeftLegWorld->Static_Update();
		m_pRightLegWorld->Static_Update();
		m_pLeftHandWorld->Static_Update();
		m_pRightHandWorld->Static_Update();
		m_pLeftFootWorld->Static_Update();
		m_pRightHandWorld->Static_Update();
	}
}

void CCubePlayer::Animation(void)
{
	if (Get_DIKeyState(DIK_W) || Get_DIKeyState(DIK_A) || Get_DIKeyState(DIK_S) || Get_DIKeyState(DIK_D) || Get_DIKeyState(DIK_SPACE) || Get_DIKeyState(DIK_LSHIFT))
	{
		if (m_fLeftArmAngle > 0.6f)
			m_bWalkAngle = false;
		if (m_fLeftArmAngle < -0.6f)
			m_bWalkAngle = true;

		if (m_bWalkAngle == true)
			m_fLeftArmAngle += m_fTimeDelta * 4.f;
		else if (m_bWalkAngle == false)
			m_fLeftArmAngle -= m_fTimeDelta * 4.f;

		m_fRightArmAngle = -m_fLeftArmAngle;

		if (m_fLeftLegAngle > 0.6f)
			m_bWalkAngle_Leg = false;
		if (m_fLeftLegAngle < -0.6f)
			m_bWalkAngle_Leg = true;

		if (m_bWalkAngle_Leg == true)
			m_fLeftLegAngle += m_fTimeDelta * 4.f;
		else if (m_bWalkAngle_Leg == false)
			m_fLeftLegAngle -= m_fTimeDelta * 4.f;

		m_fRightLegAngle = -m_fLeftLegAngle;

		if (m_fHandAngle > -D3DX_PI / 2.f)
			m_fHandAngle -= m_fTimeDelta * 4;
	}
	if (Get_DIMouseState(DIM_RB))
	{
		m_fLeftArmAngle = D3DXToRadian(-90.f) + m_fDownAngle;
		m_fRightArmAngle = D3DXToRadian(-90.f) + m_fDownAngle;
		m_fHandAngle = 0.f;
	}
	if(!(Get_DIKeyState(DIK_W)		|| 
		Get_DIKeyState(DIK_A)		|| 
		Get_DIKeyState(DIK_S)		|| 
		Get_DIKeyState(DIK_D)		|| 
		Get_DIKeyState(DIK_SPACE)	|| 
		Get_DIKeyState(DIK_LSHIFT)	||
		Get_DIMouseState(DIM_RB)))
	{

		if (m_fLeftArmAngle != 0.f)
		{
			if (m_fLeftArmAngle > 0.f)
			{
				m_fLeftArmAngle -= D3DXToRadian(10.f);
				if (m_fLeftArmAngle < 0.f)
					m_fLeftArmAngle = 0.f;
			}
			else if (m_fLeftArmAngle < 0.f)
			{
				m_fLeftArmAngle += D3DXToRadian(10.f);
				if (m_fLeftArmAngle > 0.f)
					m_fLeftArmAngle = 0.f;
			}
		}

		if (m_fRightArmAngle != 0.f)
		{
			if (m_fRightArmAngle > 0.f)
			{
				m_fRightArmAngle -= D3DXToRadian(10.f);
				if (m_fRightArmAngle < 0.f)
					m_fRightArmAngle = 0.f;
			}
			else if (m_fRightArmAngle < 0.f)
			{
				m_fRightArmAngle += D3DXToRadian(10.f);
				if (m_fRightArmAngle > 0.f)
					m_fRightArmAngle = 0.f;
			}
		}

		if (m_fLeftLegAngle != 0.f)
		{
			if (m_fLeftLegAngle > 0.f)
			{
				m_fLeftLegAngle -= D3DXToRadian(10.f);
				if (m_fLeftLegAngle < 0.f)
					m_fLeftLegAngle = 0.f;
			}
			else if (m_fLeftLegAngle < 0.f)
			{
				m_fLeftLegAngle += D3DXToRadian(10.f);
				if (m_fLeftLegAngle > 0.f)
					m_fLeftLegAngle = 0.f;
			}
		}

		if (m_fRightLegAngle != 0.f)
		{
			if (m_fRightLegAngle > 0.f)
			{
				m_fRightLegAngle -= D3DXToRadian(10.f);
				if (m_fRightLegAngle < 0.f)
					m_fRightLegAngle = 0.f;
			}
			else if (m_fRightLegAngle < 0.f)
			{
				m_fRightLegAngle += D3DXToRadian(10.f);
				if (m_fRightLegAngle > 0.f)
					m_fRightLegAngle = 0.f;
			}
		}

		if (m_fHandAngle != 0.f)
		{
			if (m_fHandAngle > 0.f)
			{
				m_fHandAngle -= D3DXToRadian(10.f);
				if (m_fHandAngle < 0.f)
					m_fHandAngle = 0.f;
			}
			else if (m_fHandAngle < 0.f)
			{
				m_fHandAngle += D3DXToRadian(10.f);
				if (m_fHandAngle > 0.f)
					m_fHandAngle = 0.f;
			}
		}
	}
}

void CCubePlayer::Move()
{
	_vec3	vDir;

	if (Get_DIKeyState(DIK_W))
	{
		m_pBodyWorld->Get_Info(INFO_LOOK, &vDir);
		m_pBodyWorld->Move_Pos(&(vDir * 30.f * m_fTimeDelta));
	}
	if (Get_DIKeyState(DIK_S))
	{
		m_pBodyWorld->Get_Info(INFO_LOOK, &vDir);
		m_pBodyWorld->Move_Pos(&(vDir * -30.f * m_fTimeDelta));

	}
	if (Get_DIKeyState(DIK_A))
	{
		m_pBodyWorld->Get_Info(INFO_RIGHT, &vDir);
		m_pBodyWorld->Move_Pos(&(vDir * -30.f * m_fTimeDelta));
	}
	if (Get_DIKeyState(DIK_D))
	{
		m_pBodyWorld->Get_Info(INFO_RIGHT, &vDir);
		m_pBodyWorld->Move_Pos(&(vDir * 30.f * m_fTimeDelta));
	}

	if (Get_DIKeyState(DIK_SPACE))
	{
		m_bJump = true;
	}

	if (Get_DIKeyState(DIK_LSHIFT))
	{
		m_bJump = false;
	}
}

void CCubePlayer::TransAxis(void)
{
	_vec3	vBefore, vAfter;

	FAILED_CHECK_RETURN(Get_BodyTransform(), );

	m_pBodyWorld->Get_Info(INFO_POS, &vBefore);
	m_pBodyWorld->Get_BeforeInfo(INFO_POS, &vAfter);

	m_pLeftArmWorld->Rotation_Axis_Animation(-0.1f, -0.15f, m_fLeftArmAngle, -m_fLookAngle);
	m_pRightArmWorld->Rotation_Axis_Animation(-0.1f, 0.15f, m_fRightArmAngle, -m_fLookAngle);
	m_pLeftHandWorld->Rotation_Axis_Animation(-0.3f, -0.15f, m_fLeftArmAngle, -m_fLookAngle, -0.1f, m_fHandAngle);
	m_pRightHandWorld->Rotation_Axis_Animation(-0.3f, 0.15f, m_fRightArmAngle, -m_fLookAngle, -0.1f, m_fHandAngle);

	m_pLeftLegWorld->Rotation_Axis_Animation(-0.1f, -0.05f, m_fLeftLegAngle, -m_fLookAngle);
	m_pRightLegWorld->Rotation_Axis_Animation(-0.1f, 0.05f, m_fRightLegAngle, -m_fLookAngle);
	m_pLeftFootWorld->Rotation_Axis_Animation(-0.3f, -0.05f, m_fLeftLegAngle, -m_fLookAngle, -0.1f, fabs(m_fLeftLegAngle));
	m_pRightFootWorld->Rotation_Axis_Animation(-0.3f, 0.05f, m_fRightLegAngle, -m_fLookAngle, -0.1f, fabs(m_fRightLegAngle));
}

void CCubePlayer::Look_Direction(void)
{
	FAILED_CHECK_RETURN(Get_BodyTransform(), );

	_vec3	vHead, vBody;
	m_pHeadWorld->Get_BeforeInfo(INFO_LOOK, &vHead);
	m_pBodyWorld->Get_BeforeInfo(INFO_LOOK, &vBody);

	_long MoveX = Get_DIMouseMove(DIMS_X);
	_long MoveY = Get_DIMouseMove(DIMS_Y);
	_long MoveZ = Get_DIMouseMove(DIMS_Z);
	cout << MoveX << endl;
	cout << MoveY << endl;
	cout << MoveZ << endl;
	m_pBodyWorld->Rotation(ROT_Y, D3DXToRadian(MoveX / 10.f));
	m_fLookAngle -= D3DXToRadian(MoveX / 10.f);

	m_fDownAngle += D3DXToRadian(MoveY / 10.f);
}

void CCubePlayer::Gun_Check()
{
	// ���� ���� ������ UZI�� �浹�� �ߴٸ� m_vecWeapon�� pushback���� ������ ����.
	// ex�ڵ�
	if (m_bUzi == true)
	{
		m_vecWeapon.push_back(dynamic_cast<CWeapon*>(Engine::Get_GameObject(L"Layer_Gun", L"UZI1")));
		m_bUzi = false;
	}

	if (Get_DIKeyState(DIK_1) & 0x80)
	{
		if (!m_vecWeapon.empty())
		{
			if (m_vecWeapon[0] != nullptr)
			{
				m_Weapon = m_vecWeapon[0];
				m_tAbility->iGunTexture = 0; // Ȥ���� �� ���׷��̵��ؼ� �ٸ� ������ ���̰� �ȴٸ� �� ���ڿ� UI/Gun �� ����ִ� ���ڿ� ���ؼ� �������.
			}
		}
	}
	if (Get_DIKeyState(DIK_2) & 0x80)
	{
		if (m_vecWeapon.size() >= 2)
		{
			if (m_vecWeapon[1] != nullptr)
			{
				m_Weapon = m_vecWeapon[1];
				m_tAbility->iGunTexture = 1;
			}
		}
	}
	if (Get_DIKeyState(DIK_3) & 0x80)
	{
		if (m_vecWeapon.size() >= 3)
		{
			if (m_vecWeapon[2] != nullptr)
			{
				m_Weapon = m_vecWeapon[2];
				m_tAbility->iGunTexture = 2;
			}
		}
	}
	if (Get_DIKeyState(DIK_4) & 0x80)
	{
		if (m_vecWeapon.size() >= 4)
		{
			if (m_vecWeapon[3] != nullptr)
			{
				m_Weapon = m_vecWeapon[3];
				m_tAbility->iGunTexture = 3;
			}
		}
	}
	if (Get_DIKeyState(DIK_5) & 0x80)
	{
		if (m_vecWeapon.size() >= 5)
		{
			if (m_vecWeapon[4] != nullptr)
			{
				m_Weapon = m_vecWeapon[4];
				m_tAbility->iGunTexture = 4;
			}
		}
	}
}

void CCubePlayer::Fire_Bullet(void)
{
	if (Get_DIMouseState(DIM_RB))
	{
		FAILED_CHECK_RETURN(Get_BodyTransform(), );

		_vec3	vSrcPos;
		CTransform*	pMuzzle = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Gun", L"Uzi_Part_1_1", L"Proto_TransformCom", ID_STATIC));
		NULL_CHECK(pMuzzle);
		pMuzzle->Get_BeforeInfo(INFO_POS, &vSrcPos);
		CTransform* pTargetTrans = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_GameLogic", L"TestPlayer0", L"Proto_TransformCom", ID_DYNAMIC));
		NULL_CHECK(pTargetTrans);
		CCubeTex* pTestPlayer = dynamic_cast<CCubeTex*>(Engine::Get_Component(L"Layer_GameLogic", L"TestPlayer0", L"Proto_CubeTexCom", ID_STATIC));
		NULL_CHECK(pTestPlayer);

		_vec3	vPos;
		m_pHeadWorld->Get_BeforeInfo(INFO_POS, &vPos);

		if (Get_DIMouseState(DIM_LB))
		{
			if (m_pCalculatorCom->Peek_Cube_Target(g_hWnd, &_vec3(0, 0, 0) , pTestPlayer, pTargetTrans))
			{
				cout << "AAAAAAAAAAAAAAAAAA" << endl;
			}
		}
	}
}

void CCubePlayer::Jump(void)
{
}

HRESULT CCubePlayer::Get_BodyTransform(void)
{
	m_pHeadWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"HEAD", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pHeadWorld, E_FAIL);
	m_pBodyWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"BODY", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pBodyWorld, E_FAIL);
	m_pLeftArmWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"L_ARM", L"Proto_TransformCom", ID_STATIC));
	NULL_CHECK_RETURN(m_pBodyWorld, E_FAIL);
	m_pRightArmWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"R_ARM", L"Proto_TransformCom", ID_STATIC));
	NULL_CHECK_RETURN(m_pBodyWorld, E_FAIL);
	m_pLeftLegWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"L_LEG", L"Proto_TransformCom", ID_STATIC));
	NULL_CHECK_RETURN(m_pBodyWorld, E_FAIL);
	m_pRightLegWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"R_LEG", L"Proto_TransformCom", ID_STATIC));
	NULL_CHECK_RETURN(m_pBodyWorld, E_FAIL);

	m_pLeftHandWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"L_HAND", L"Proto_TransformCom", ID_STATIC));
	NULL_CHECK_RETURN(m_pBodyWorld, E_FAIL);
	m_pRightHandWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"R_HAND", L"Proto_TransformCom", ID_STATIC));
	NULL_CHECK_RETURN(m_pBodyWorld, E_FAIL);
	m_pLeftFootWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"L_FOOT", L"Proto_TransformCom", ID_STATIC));
	NULL_CHECK_RETURN(m_pBodyWorld, E_FAIL);
	m_pRightFootWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"R_FOOT", L"Proto_TransformCom", ID_STATIC));
	NULL_CHECK_RETURN(m_pBodyWorld, E_FAIL);

	return S_OK;
}

void CCubePlayer::Key_Input(const _float & fTimeDelta)
{
}

HRESULT CCubePlayer::Add_Component(void)
{
	CComponent* pInstance = nullptr;

	pInstance = m_pTransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pInstance });

	pInstance = m_pHitBox = dynamic_cast<CHitBox*>(Engine::Clone_Proto(L"Proto_HitboxCom"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_HitboxCom", pInstance });

	pInstance = m_pCollision = dynamic_cast<CCollision*>(Engine::Clone_Proto(L"Proto_CollisionCom"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_CollisionCom", pInstance });

	pInstance = m_pCalculatorCom = dynamic_cast<CCalculator*>(Engine::Clone_Proto(L"Proto_CalculatorCom"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CalculatorCom", pInstance });

	return S_OK;
}

CCubePlayer * CCubePlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCubePlayer* pInstance = new CCubePlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);

	return pInstance;
}

void CCubePlayer::Free(void)
{
	Safe_Delete<ABILITY*>(m_tAbility);
	CGameObject::Free();
}
