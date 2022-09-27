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

	m_pTransform->Set_Scale(2.f, 5.f, 2.f);

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

	_vec3	vLook;
	m_pHeadWorld->Get_BeforeInfo(INFO_LOOK, &vLook);

	CGameObject::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CCubePlayer::LateUpdate_Object(void)
{
	if (!m_bJump)
		Set_OnTerrain();

	//TransAxis();

	Look_Direction();

	Assemble();

	Fire_Bullet();

	//m_pHitBox->Get_MinMax(&m_vMin, &m_vMax);

	//Get_HitboxMin(&vT1, &vT2);

	//m_pCollision->Check_Collision();

	//cout << m_vMin.x << " " << m_vMin.y << " " << m_vMin.z << "     " << m_vMax.x << " " << m_vMax.y << " " << m_vMax.z << endl;

	CGameObject::LateUpdate_Object();
}

void CCubePlayer::Render_Object(void)
{
	/*m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DPMISCCAPS_CULLNONE);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pHitBox->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DPMISCCAPS_CULLCCW);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);*/
}

void CCubePlayer::Set_OnTerrain(void)
{
	m_pBodyWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"BODY", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pBodyWorld, );

	_vec3		vPos;
	m_pBodyWorld->Get_BeforeInfo(INFO_POS, &vPos);

	Engine::CTerrainTex*	pTerrainTexCom = dynamic_cast<Engine::CTerrainTex*>(Engine::Get_Component(L"Layer_Environment", L"Terrain", L"Proto_TerrainTexCom", ID_STATIC));
	NULL_CHECK(pTerrainTexCom);

	_float fHeight = m_pCalculatorCom->HeightOnTerrain(&vPos, pTerrainTexCom->Get_VtxPos(), VTXCNTX, VTXCNTZ) + 6.f;

	m_pBodyWorld->Set_Pos(vPos.x, fHeight, vPos.z);
}

void CCubePlayer::Assemble(void)
{
	FAILED_CHECK_RETURN(Get_BodyTransform(), );

	_vec3 vBodyPos;
	m_pBodyWorld->Get_BeforeInfo(INFO_POS, &vBodyPos);
	m_pTransform->Set_Pos(vBodyPos.x, vBodyPos.y, vBodyPos.z);
	m_pHeadWorld->Set_Pos(vBodyPos.x, vBodyPos.y + 3.f, vBodyPos.z);
	m_pLeftArmWorld->Set_Pos(vBodyPos.x - 1.5f, vBodyPos.y + 1.f, vBodyPos.z);
	m_pRightArmWorld->Set_Pos(vBodyPos.x + 1.5f, vBodyPos.y + 1.f, vBodyPos.z);
	m_pLeftLegWorld->Set_Pos(vBodyPos.x - 0.5f, vBodyPos.y - 3.f, vBodyPos.z);
	m_pRightLegWorld->Set_Pos(vBodyPos.x + 0.5f, vBodyPos.y - 3.f, vBodyPos.z);

	m_pLeftHandWorld->Set_Pos(vBodyPos.x - 1.5f, vBodyPos.y - 1.f, vBodyPos.z);
	m_pRightHandWorld->Set_Pos(vBodyPos.x + 1.5f, vBodyPos.y - 1.f, vBodyPos.z);
	m_pLeftFootWorld->Set_Pos(vBodyPos.x - 0.5f, vBodyPos.y - 5.f, vBodyPos.z);
	m_pRightFootWorld->Set_Pos(vBodyPos.x + 0.5f, vBodyPos.y - 5.f, vBodyPos.z);

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

	//cout << vBodyPos.y << endl;
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
	if (Get_DIMouseState(DIM_RB))//////////////////////////////////////////////////////////////////////
	{
		m_fLeftArmAngle = D3DXToRadian(-90.f) + m_fDownAngle;
		m_fRightArmAngle = D3DXToRadian(-90.f) + m_fDownAngle;
		m_fHandAngle = 0.f;
	}///////////////////////////////////////////////////////////////////////////////////////////////////
	if(!(Get_DIKeyState(DIK_W)		|| 
		Get_DIKeyState(DIK_A)		|| 
		Get_DIKeyState(DIK_S)		|| 
		Get_DIKeyState(DIK_D)		|| 
		Get_DIKeyState(DIK_SPACE)	|| 
		Get_DIKeyState(DIK_LSHIFT)	||
		Get_DIMouseState(DIM_RB)))
	{
		//	왼팔복귀
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
		//	오른팔복귀
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
		//	왼다리복귀
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
		//	오른다리복귀
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
		//	손 복귀
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

	m_pLeftArmWorld->Rotation_Axis_Animation(-1.f, -1.5f, m_fLeftArmAngle, -m_fLookAngle);
	m_pRightArmWorld->Rotation_Axis_Animation(-1.f, 1.5f, m_fRightArmAngle, -m_fLookAngle);
	m_pLeftHandWorld->Rotation_Axis_Animation(-3.f, -1.5f, m_fLeftArmAngle, -m_fLookAngle, -1.f, m_fHandAngle);
	m_pRightHandWorld->Rotation_Axis_Animation(-3.f, 1.5f, m_fRightArmAngle, -m_fLookAngle, -1.f, m_fHandAngle);

	m_pLeftLegWorld->Rotation_Axis_Animation(-1.f, -0.5f, m_fLeftLegAngle, -m_fLookAngle);
	m_pRightLegWorld->Rotation_Axis_Animation(-1.f, 0.5f, m_fRightLegAngle, -m_fLookAngle);
	m_pLeftFootWorld->Rotation_Axis_Animation(-3.f, -0.5f, m_fLeftLegAngle, -m_fLookAngle, -1.f, fabs(m_fLeftLegAngle));
	m_pRightFootWorld->Rotation_Axis_Animation(-3.f, 0.5f, m_fRightLegAngle, -m_fLookAngle, -1.f, fabs(m_fRightLegAngle));
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

	m_pBodyWorld->Rotation(ROT_Y, D3DXToRadian(MoveX / 10.f));
	m_fLookAngle -= D3DXToRadian(MoveX / 10.f);

	m_fDownAngle += D3DXToRadian(MoveY / 10.f);
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

	/*	_vec3	vEye;
		_matrix	matView;
		m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
		D3DXMatrixInverse(&matView, nullptr, &matView);
		vEye = { matView.m[3][0], matView.m[3][1], matView.m[3][2] };
		D3DXVec3Normalize(&vEye, &vEye);
		cout << vEye.x << " " << vEye.y << " " << vEye.z << endl;*/

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
	_vec3	vDir;

	// 몸의 방향이 원래대로 돌아오도록 구현해야 함
	// 다리 회전 적용해야 함
	// 움직임의 기준을 바디? 히트박스?

	//#pragma region 팔다리회전
	//
	//	if (Get_DIKeyState(DIK_W) || Get_DIKeyState(DIK_A) || Get_DIKeyState(DIK_S) || Get_DIKeyState(DIK_D))
	//	{
	//		if (m_fAngle > 0.3f)
	//			m_bWalkAngle = false;
	//		if (m_fAngle < -0.3f)
	//			m_bWalkAngle = true;
	//
	//		if (m_bWalkAngle == true)
	//		{
	//			m_fAngle += fTimeDelta * 4;
	//
	//			m_pLeftArmWorld->Rotation_Axis_X(2.f, m_fAngle);
	//			m_pRightArmWorld->Rotation_Axis_X(2.f, -m_fAngle);
	//
	//			m_pLeftLegWorld->Rotation_Axis_X(2.f, -m_fAngle);
	//			m_pRightLegWorld->Rotation_Axis_X(2.f, +m_fAngle);
	//		}
	//		else if (m_bWalkAngle == false)
	//		{
	//			m_fAngle -= fTimeDelta * 4;
	//
	//			m_pLeftArmWorld->Rotation_Axis_X(2.f, m_fAngle);
	//			m_pRightArmWorld->Rotation_Axis_X(2.f, -m_fAngle);
	//
	//			m_pLeftLegWorld->Rotation_Axis_X(2.f, -m_fAngle);
	//			m_pRightLegWorld->Rotation_Axis_X(2.f, +m_fAngle);
	//		}
	//	}
	//	else if (m_fAngle != 0)
	//	{
	//		if (m_fAngle > 0)
	//		{
	//			m_fAngle -= fTimeDelta;
	//			if (m_fAngle < 0)
	//				m_fAngle = 0;
	//
	//			m_pLeftArmWorld->Rotation_Axis_X(2.f, m_fAngle);
	//			m_pRightArmWorld->Rotation_Axis_X(2.f, -m_fAngle);
	//			m_pLeftLegWorld->Rotation_Axis_X(2.f, -m_fAngle);
	//			m_pRightLegWorld->Rotation_Axis_X(2.f, m_fAngle);
	//		}
	//		else if (m_fAngle < 0)
	//		{
	//			m_fAngle += fTimeDelta;
	//			if (m_fAngle > 0)
	//				m_fAngle = 0;
	//
	//			m_pLeftArmWorld->Rotation_Axis_X(2.f, m_fAngle);
	//			m_pRightArmWorld->Rotation_Axis_X(2.f, -m_fAngle);
	//			m_pLeftLegWorld->Rotation_Axis_X(2.f, -m_fAngle);
	//			m_pRightLegWorld->Rotation_Axis_X(2.f, m_fAngle);
	//		}
	//
	//	}
	//
	//#pragma endregion 팔다리움직임

	//if (Get_DIKeyState(DIK_W))
	//{
	//	m_pTransform->Get_Info(INFO_LOOK, &vDir);

	//	m_pBodyWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
	//	m_pHeadWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
	//	//m_pLeftArmWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
	//	//m_pRightArmWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
	//	m_pLeftLegWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
	//	m_pRightLegWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
	//}
	//if (Get_DIKeyState(DIK_S))
	//{
	//	m_pTransform->Get_Info(INFO_LOOK, &vDir);

	//	m_pBodyWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
	//	m_pHeadWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
	//	//m_pLeftArmWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
	//	//m_pRightArmWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
	//	m_pLeftLegWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
	//	m_pRightLegWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
	//}
	//if (Get_DIKeyState(DIK_A))
	//{
	//	m_pTransform->Get_Info(INFO_RIGHT, &vDir);

	//	if (m_fLookAngle > -0.2f)
	//	{
	//		m_fLookAngle -= fTimeDelta * 5.f;
	//		m_pBodyWorld->Rotation(ROT_Y, -(fTimeDelta * 5.f));
	//	}

	//			m_pBodyWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
	//			m_pHeadWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));

	//	/*m_pLeftArmWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
	//	m_pRightArmWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));*/

	//	m_pLeftArmWorld->Rotation_Axis_Y(-1.5f, m_fLookAngle);
	//	m_pRightArmWorld->Rotation_Axis_Y(1.5f, m_fLookAngle);

	//			m_pLeftLegWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
	//			m_pRightLegWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
	//}
	//if (Get_DIKeyState(DIK_D))
	//{
	//	m_pTransform->Get_Info(INFO_RIGHT, &vDir);

	//	if (m_fLookAngle < 0.2f)
	//	{
	//		m_fLookAngle += fTimeDelta * 5.f;
	//		m_pBodyWorld->Rotation(ROT_Y, fTimeDelta * 5.f);
	//	}

	//	m_pLeftArmWorld->Rotation_Axis_Y(-1.5f, m_fLookAngle);
	//	m_pRightArmWorld->Rotation_Axis_Y(1.5f, m_fLookAngle);

	//	m_pBodyWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
	//	m_pHeadWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
	//	//m_pLeftArmWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
	//	//m_pRightArmWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
	//	m_pLeftLegWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
	//	m_pRightLegWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
	//}

	//if (Get_DIKeyState(DIK_SPACE))
	//{
	//	m_pBodyWorld->Get_Info(INFO_UP, &vDir);

	//	m_pBodyWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
	//	m_pHeadWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
	//	m_pLeftArmWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
	//	m_pRightArmWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
	//	m_pLeftLegWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
	//	m_pRightLegWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
	//}

	//if (Get_DIKeyState(DIK_LSHIFT))
	//{
	//	m_pBodyWorld->Get_Info(INFO_UP, &vDir);

	//	m_pBodyWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
	//	m_pHeadWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
	//	m_pLeftArmWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
	//	m_pRightArmWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
	//	m_pLeftLegWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
	//	m_pRightLegWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
	//}
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
	CGameObject::Free();
}
