#include "stdafx.h"
#include "..\Header\CubePlayer.h"

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

	CGameObject::Update_Object(fTimeDelta);

	Move();
	Walk_Animation();

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CCubePlayer::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();

	Assemble();

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
	m_pBodyWorld->Get_Info(INFO_POS, &vPos);

	Engine::CTerrainTex*	pTerrainTexCom = dynamic_cast<Engine::CTerrainTex*>(Engine::Get_Component(L"Layer_Environment", L"Terrain", L"Proto_TerrainTexCom", ID_STATIC));
	NULL_CHECK(pTerrainTexCom);

	_float fHeight = m_pCalculatorCom->HeightOnTerrain(&vPos, pTerrainTexCom->Get_VtxPos(), VTXCNTX, VTXCNTZ);

	m_pBodyWorld->Set_Pos(vPos.x, fHeight, vPos.z);
}

void CCubePlayer::Assemble(void)
{
	FAILED_CHECK_RETURN(Get_BodyTransform(), );

	_vec3 vBodyPos;
	m_pBodyWorld->Get_BeforeInfo(INFO_POS, &vBodyPos);
	m_pTransform->Set_Pos(vBodyPos.x, vBodyPos.y, vBodyPos.z);
	m_pHeadWorld->Set_Pos(vBodyPos.x, vBodyPos.y + 3.f, vBodyPos.z);
	m_pLeftArmWorld->Set_Pos(vBodyPos.x - 1.5f, vBodyPos.y, vBodyPos.z);
	m_pRightArmWorld->Set_Pos(vBodyPos.x + 1.5f, vBodyPos.y, vBodyPos.z);
	m_pLeftLegWorld->Set_Pos(vBodyPos.x - 0.5f, vBodyPos.y - 4.f, vBodyPos.z);
	m_pRightLegWorld->Set_Pos(vBodyPos.x + 0.5f, vBodyPos.y - 4.f, vBodyPos.z);

	//cout << vBodyPos.y << endl;
}

void CCubePlayer::Walk_Animation(void)
{
	if (Get_DIKeyState(DIK_W) || Get_DIKeyState(DIK_A) || Get_DIKeyState(DIK_S) || Get_DIKeyState(DIK_D) || Get_DIKeyState(DIK_SPACE) || Get_DIKeyState(DIK_LSHIFT))
	{
		if (m_fAngle > 0.3f)
			m_bWalkAngle = false;
		if (m_fAngle < -0.3f)
			m_bWalkAngle = true;

		if (m_bWalkAngle == true)
		{
			m_fAngle += m_fTimeDelta * 4;

			m_pLeftArmWorld->Rotation_Axis_X(2.f, m_fAngle);
			m_pRightArmWorld->Rotation_Axis_X(2.f, -m_fAngle);

			m_pLeftLegWorld->Rotation_Axis_X(2.f, -m_fAngle);
			m_pRightLegWorld->Rotation_Axis_X(2.f, +m_fAngle);
		}
		else if (m_bWalkAngle == false)
		{
			m_fAngle -= m_fTimeDelta * 4;

			m_pLeftArmWorld->Rotation_Axis_X(2.f, m_fAngle);
			m_pRightArmWorld->Rotation_Axis_X(2.f, -m_fAngle);

			m_pLeftLegWorld->Rotation_Axis_X(2.f, -m_fAngle);
			m_pRightLegWorld->Rotation_Axis_X(2.f, +m_fAngle);
		}
	}
	else if (m_fAngle != 0)
	{
		if (m_fAngle > 0)
		{
			m_fAngle -= m_fTimeDelta;
			if (m_fAngle < 0)
				m_fAngle = 0;

			m_pLeftArmWorld->Rotation_Axis_X(2.f, m_fAngle);
			m_pRightArmWorld->Rotation_Axis_X(2.f, -m_fAngle);

			m_pLeftLegWorld->Rotation_Axis_X(2.f, -m_fAngle);
			m_pRightLegWorld->Rotation_Axis_X(2.f, m_fAngle);
		}
		else if (m_fAngle < 0)
		{
			m_fAngle += m_fTimeDelta;
			if (m_fAngle > 0)
				m_fAngle = 0;

			m_pLeftArmWorld->Rotation_Axis_X(2.f, m_fAngle);
			m_pRightArmWorld->Rotation_Axis_X(2.f, -m_fAngle);

			m_pLeftLegWorld->Rotation_Axis_X(2.f, -m_fAngle);
			m_pRightLegWorld->Rotation_Axis_X(2.f, m_fAngle);
		}

	}
}

void CCubePlayer::Move()
{
	_vec3	vDir;

	if (Get_DIKeyState(DIK_W))
	{
		m_pTransform->Get_Info(INFO_LOOK, &vDir);
		m_pBodyWorld->Move_Pos(&(vDir * 10.f * m_fTimeDelta));
	}
	if (Get_DIKeyState(DIK_S))
	{
		m_pTransform->Get_Info(INFO_LOOK, &vDir);
		m_pBodyWorld->Move_Pos(&(vDir * -10.f * m_fTimeDelta));

	}
	if (Get_DIKeyState(DIK_A))
	{
		m_pTransform->Get_Info(INFO_RIGHT, &vDir);

		if (m_fLookAngle > -0.2f)
		{
			m_fLookAngle -= m_fTimeDelta * 5.f;
			m_pBodyWorld->Rotation(ROT_Y, -(m_fTimeDelta * 5.f));
		}
		m_pBodyWorld->Move_Pos(&(vDir * -10.f * m_fTimeDelta));
	}
	if (Get_DIKeyState(DIK_D))
	{
		m_pTransform->Get_Info(INFO_RIGHT, &vDir);

		if (m_fLookAngle < 0.2f)
		{
			m_fLookAngle += m_fTimeDelta * 5.f;
			m_pBodyWorld->Rotation(ROT_Y, m_fTimeDelta * 5.f);
		}
		m_pBodyWorld->Move_Pos(&(vDir * 10.f * m_fTimeDelta));
	}

	if (Get_DIKeyState(DIK_SPACE))
	{
		m_pBodyWorld->Get_Info(INFO_UP, &vDir);
		m_pBodyWorld->Move_Pos(&(vDir * 10.f * m_fTimeDelta));
	}

	if (Get_DIKeyState(DIK_LSHIFT))
	{
		m_pBodyWorld->Get_Info(INFO_UP, &vDir);
		m_pBodyWorld->Move_Pos(&(vDir * -10.f * m_fTimeDelta));
	}
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
