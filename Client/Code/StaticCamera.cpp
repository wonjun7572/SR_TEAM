#include "stdafx.h"
#include "..\Header\StaticCamera.h"



CStaticCamera::CStaticCamera(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCamera(pGraphicDev)
{
}


CStaticCamera::~CStaticCamera()
{
}

HRESULT CStaticCamera::Ready_Object(const _vec3* pEye,
	const _vec3* pAt,
	const _vec3* pUp,
	const _float& fFov,
	const _float& fAspect,
	const _float& fNear,
	const _float& fFar)
{
	m_vEye = *pEye;
	m_vAt = *pAt;
	m_vUp = *pUp;

	m_fFov = fFov;
	m_fAspect = fAspect;
	m_fNear = fNear;
	m_fFar = fFar;

	FAILED_CHECK_RETURN(CCamera::Ready_Object(), E_FAIL);

	return S_OK;
}

Engine::_int CStaticCamera::Update_Object(const _float& fTimeDelta)
{
	Key_Input(fTimeDelta);

	//Target_Renewal();

	Look_Taget();

	Mouse_Fix();

	_int iExit = CCamera::Update_Object(fTimeDelta);

	return iExit;
}

void CStaticCamera::LateUpdate_Object(void)
{
	CCamera::LateUpdate_Object();
}

void CStaticCamera::Free(void)
{
	CCamera::Free();
}

CStaticCamera* CStaticCamera::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3* pEye, const _vec3* pAt, const _vec3* pUp, const _float& fFov /*= D3DXToRadian(60.f)*/, const _float& fAspect /*= (float)WINCX / WINCY*/, const _float& fNear /*= 0.1f*/, const _float& fFar /*= 1000.f*/)
{
	CStaticCamera*		pInstance = new CStaticCamera(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(pEye, pAt, pUp, fFov, fAspect, fNear, fFar)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CStaticCamera::Key_Input(const _float& fTimeDelta)
{
	// 마우스 휠을 통한 줌인 줌 아웃
	if (m_fDistance >= 1)
	{
		if (Get_DIMouseMove(DIMS_Z) > 0)
			m_fDistance -= fTimeDelta * m_fSpeed * 5.f;
	}

	if (m_fDistance <= 20)
	{
		if (Get_DIMouseMove(DIMS_Z) < 0)
			m_fDistance += fTimeDelta * m_fSpeed * 5.f;
	}

	// 카메라 축 회전 방향 제한해야함
	//if (m_pPlayerTransform)
	//{
	//	_vec3 vPlayerPos;
	//	m_pPlayerTransform->Get_Info(INFO_POS, &vPlayerPos);
	//	//if (Get_DIMouseMove(DIMS_Y) > 0)
	//		m_fAngle += D3DXToRadian(180.f) * fTimeDelta;
	//	/*if (Get_DIMouseMove(DIMS_Y) < 0)
	//		m_fAngle += D3DXToRadian(180.f) * fTimeDelta;*/
	//}
}

void CStaticCamera::Target_Renewal(void)
{
	if (!m_pPlayerTransform)
	{
		m_pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"BODY", L"Proto_TransformCom", ID_DYNAMIC));
		NULL_CHECK(m_pPlayerTransform);
	}

	_vec3	vLook;
	m_pPlayerTransform->Get_Info(INFO_LOOK, &vLook);

	m_vEye = vLook * -1.f;	// 방향 벡터
	D3DXVec3Normalize(&m_vEye, &m_vEye);

	m_vEye.y = 1.f;
	m_vEye *= m_fDistance;	// 방향 벡터

	_vec3		vRight;
	memcpy(&vRight, &m_pPlayerTransform->m_matWorld.m[0][0], sizeof(_vec3));

	_matrix		matRot;
	D3DXMatrixRotationAxis(&matRot, &vRight, m_fAngle);
	D3DXVec3TransformNormal(&m_vEye, &m_vEye, &matRot);

	m_vEye += m_pPlayerTransform->m_vInfo[INFO_POS];
	m_vAt = m_pPlayerTransform->m_vInfo[INFO_POS];
}

void CStaticCamera::Mouse_Fix(void)
{
	POINT	pt{ WINCX >> 1 , WINCY >> 1 };

	ClientToScreen(g_hWnd, &pt);
	SetCursorPos(pt.x, pt.y);
}

void CStaticCamera::Look_Taget(void)
{
	if (nullptr == m_pTransform_Target)
	{
		m_pTransform_Target = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"HEAD", L"Proto_TransformCom", ID_DYNAMIC));
		NULL_CHECK(m_pTransform_Target);
	}

	_vec3 vLook;
	m_pTransform_Target->Get_Info(INFO_LOOK, &vLook);

	_vec3 vRight;
	m_pTransform_Target->Get_Info(INFO_RIGHT, &vRight);

	_vec3 vUp;
	m_pTransform_Target->Get_Info(INFO_UP, &vUp);

	m_vEye = (vLook * -2.f) + (vUp * 1.f);
	D3DXVec3Normalize(&m_vEye, &m_vEye);

	//m_vEye.y = 1.f;
	m_vEye *= m_fDistance;

	_vec3 vPos;
	m_pTransform_Target->Get_Info(INFO_POS, &vPos);

	m_vEye += vPos;
	m_vAt = vPos;// - (vRight * 3.f);

	//m_vEye.x += 2.f;
	//m_vAt.x += 2.f;
}
