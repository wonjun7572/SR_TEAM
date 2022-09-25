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

	_vec3	vLook;
	m_pHeadWorld->Get_BeforeInfo(INFO_LOOK, &vLook);

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CCubePlayer::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
	if (!m_bJump)
		Set_OnTerrain();

	Look_Direction();

	TransAxis();

	Assemble();
	
	cout << D3DXToDegree(m_fAngle) << endl;
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

void CCubePlayer::Walk_Animation(void)
{
	if (Get_DIKeyState(DIK_W) || Get_DIKeyState(DIK_A) || Get_DIKeyState(DIK_S) || Get_DIKeyState(DIK_D) || Get_DIKeyState(DIK_SPACE) || Get_DIKeyState(DIK_LSHIFT))
	{
		if (m_fAngle > 0.6f)
			m_bWalkAngle = false;
		if (m_fAngle < -0.6f)
			m_bWalkAngle = true;

		if (m_bWalkAngle == true)
			m_fAngle += m_fTimeDelta * 4;
		else if (m_bWalkAngle == false)
			m_fAngle -= m_fTimeDelta * 4;
	}
	else if (m_fAngle != 0)
	{
		if (m_fAngle > 0)
		{
			m_fAngle -= m_fTimeDelta;
			if (m_fAngle < 0)
				m_fAngle = 0;
		}
		else if (m_fAngle < 0)
		{
			m_fAngle += m_fTimeDelta;
			if (m_fAngle > 0)
				m_fAngle = 0;
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

		if (m_fLookAngle < 0.4f)
		{
			m_fLookAngle += m_fTimeDelta * 5.f;
			m_pBodyWorld->Rotation(ROT_Y, -(m_fTimeDelta * 5.f));
		}

		m_pBodyWorld->Move_Pos(&(vDir * -10.f * m_fTimeDelta));
	}
	if (Get_DIKeyState(DIK_D))
	{
		m_pTransform->Get_Info(INFO_RIGHT, &vDir);

		if (m_fLookAngle > -0.4f)
		{
			m_fLookAngle -= m_fTimeDelta * 5.f;
			m_pBodyWorld->Rotation(ROT_Y, m_fTimeDelta * 5.f);
		}

		m_pBodyWorld->Move_Pos(&(vDir * 10.f * m_fTimeDelta));
	}

	if (Get_DIKeyState(DIK_SPACE))
	{
		/*m_pBodyWorld->Get_Info(INFO_UP, &vDir);
		m_pBodyWorld->Move_Pos(&(vDir * 10.f * m_fTimeDelta));*/

		m_bJump = true;
	}

	if (Get_DIKeyState(DIK_LSHIFT))
	{
		/*m_pBodyWorld->Get_Info(INFO_UP, &vDir);
		m_pBodyWorld->Move_Pos(&(vDir * -10.f * m_fTimeDelta));*/
		m_bJump = false;
	}
}

void CCubePlayer::TransAxis(void)
{
	_vec3	vBefore, vAfter;

	FAILED_CHECK_RETURN(Get_BodyTransform(), );

	m_pBodyWorld->Get_Info(INFO_POS, &vBefore);
	m_pBodyWorld->Get_BeforeInfo(INFO_POS, &vAfter);

	m_pLeftArmWorld->Rotation_Axis_Animation(-1.f, -1.5f, m_fAngle, -m_fLookAngle);
	m_pRightArmWorld->Rotation_Axis_Animation(-1.f, 1.5f, -m_fAngle, -m_fLookAngle);

	m_pLeftLegWorld->Rotation_Axis_Animation(-1.f, -0.5f, -m_fAngle, -m_fLookAngle);
	m_pRightLegWorld->Rotation_Axis_Animation(-1.f, 0.5f, m_fAngle, -m_fLookAngle);

	if(vBefore == vAfter)	//	이동상태가 
	{
		m_pLeftHandWorld->Rotation_Axis_Animation(-3.f, -1.5f, m_fAngle, -m_fLookAngle);
		m_pRightHandWorld->Rotation_Axis_Animation(-3.f, 1.5f, -m_fAngle, -m_fLookAngle);
		m_pLeftFootWorld->Rotation_Axis_Animation(-3.f, -0.5f, -m_fAngle, -m_fLookAngle);
		m_pRightFootWorld->Rotation_Axis_Animation(-3.f, 0.5f, m_fAngle, -m_fLookAngle);
	}
	else
	{
		m_pLeftHandWorld->Rotation_Axis_Animation(-3.f, -1.5f, m_fAngle, -m_fLookAngle, -1.f, -D3DX_PI / 2.f);
		m_pRightHandWorld->Rotation_Axis_Animation(-3.f, 1.5f, -m_fAngle, -m_fLookAngle, -1.f, -D3DX_PI / 2.f);
		m_pLeftFootWorld->Rotation_Axis_Animation(-3.f, -0.5f, -m_fAngle, -m_fLookAngle, -1.f, fabs(m_fAngle));
		m_pRightFootWorld->Rotation_Axis_Animation(-3.f, 0.5f, m_fAngle, -m_fLookAngle, -1.f, fabs(m_fAngle));
	}
}

void CCubePlayer::Look_Direction(void)
{
	FAILED_CHECK_RETURN(Get_BodyTransform(), );

	_vec3	vHead, vBody;
	m_pHeadWorld->Get_BeforeInfo(INFO_LOOK, &vHead);
	m_pBodyWorld->Get_BeforeInfo(INFO_LOOK, &vBody);

	m_pBodyWorld->Set_Info(INFO_LOOK, &vHead);

	/*vHead.y = 0.f;
	vBody.y = 0.f;

	D3DXVec3Normalize(&vHead, &vHead);
	D3DXVec3Normalize(&vBody, &vBody);

	float fDot = D3DXVec3Dot(&vHead, &vBody);
	float fDiagonal = acosf(fDot);

	cout << D3DXToDegree(fDiagonal) << endl;

	if (vHead.x > vBody.x)
	{
		m_pBodyWorld->Rotation(ROT_Y, fDiagonal);
		m_fLookAngle -= fDiagonal;
	}
	else if (vHead.x < vBody.x)
	{
		m_pBodyWorld->Rotation(ROT_Y, -fDiagonal);
		m_fLookAngle += fDiagonal;
	}*/
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
