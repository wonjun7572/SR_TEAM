#include "stdafx.h"
#include "..\Header\StaticCamera.h"
#include "CubePlayer.h"
#include "Weapon.h"
#include "Inventory.h"
#include "Shop.h"

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

	m_fDistance = 10.f;

	FAILED_CHECK_RETURN(CCamera::Ready_Object(), E_FAIL);

	return S_OK;
}

Engine::_int CStaticCamera::Update_Object(const _float& fTimeDelta)
{
	if (!(dynamic_cast<CInventory*>(Engine::Get_GameObject(STAGE_UI, L"InventoryUI"))->Get_Switch()) || !(dynamic_cast<CShop*>(Engine::Get_GameObject(STAGE_UI, L"Shop"))->Get_Switch()))
	{	
		Key_Input(fTimeDelta);

		Look_Taget(fTimeDelta);
		
		Mouse_Fix();
	}

	_int	iExit = CCamera::Update_Object(fTimeDelta);

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
	if (Key_Down(DIK_V))
		m_bChangePOV = !m_bChangePOV;
}

void CStaticCamera::Mouse_Fix(void)
{
	if (!(dynamic_cast<CInventory*>(Engine::Get_GameObject(STAGE_UI, L"InventoryUI"))->Get_Switch()) && !(dynamic_cast<CShop*>(Engine::Get_GameObject(STAGE_UI, L"Shop"))->Get_Switch()))
	{
		ShowCursor(false); 
		POINT	pt{ WINCX >> 1 , WINCY >> 1 };

		ClientToScreen(g_hWnd, &pt);
		SetCursorPos(pt.x, pt.y);		
	}
}

void CStaticCamera::Look_Taget(const _float& _fTimeDelta)
{
	if (nullptr == m_pTransform_Target)
	{
		//m_pTransform_Target = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_CHARACTER, L"AnimationPlayer", L"m_pRotationTrans", ID_DYNAMIC));
		m_pTransform_Target = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_CHARACTER, L"HEAD", TRANSFORM_COMP, ID_DYNAMIC));
		NULL_CHECK(m_pTransform_Target);
	}

	CGameObject* pPlayer = nullptr;
	pPlayer = Engine::Get_GameObject(STAGE_CHARACTER, L"PLAYER");

	if (!m_bChangePOV && (dynamic_cast<CCubePlayer*>(pPlayer)->Get_Weapon() == dynamic_cast<CWeapon*>(Engine::Get_GameObject(STAGE_GUN, L"UZI1"))||
		dynamic_cast<CCubePlayer*>(pPlayer)->Get_Weapon() == dynamic_cast<CWeapon*>(Engine::Get_GameObject(STAGE_GUN, L"SHOTGUN"))))
	{
		ChangeFOV(60.f, 0.1f, 0.f, 0.f);
	}
	else if(m_bChangePOV && (dynamic_cast<CCubePlayer*>(pPlayer)->Get_Weapon() == dynamic_cast<CWeapon*>(Engine::Get_GameObject(STAGE_GUN, L"UZI1")) ||
		dynamic_cast<CCubePlayer*>(pPlayer)->Get_Weapon() == dynamic_cast<CWeapon*>(Engine::Get_GameObject(STAGE_GUN, L"SHOTGUN"))))
	{
		ChangeFOV(60.f, 1.5f, 0.f, 3.f);
	}
	else if (dynamic_cast<CCubePlayer*>(pPlayer)->Get_SniperZoom() == true)
	{
		ChangeFOV(15.f, 1.f, 10.f, 0.f);
	}
	else
	{
		_vec3 vLook;
		m_pTransform_Target->Get_Info(INFO_LOOK, &vLook);

		_vec3 vRight;
		m_pTransform_Target->Get_Info(INFO_RIGHT, &vRight);

		_vec3 vUp;
		m_pTransform_Target->Get_Info(INFO_UP, &vUp);
		m_vEye = (vLook * -1.f);

		D3DXVec3Normalize(&m_vEye, &m_vEye);
		m_vEye *= 0.1f;

		_vec3 vPos;
		m_pTransform_Target->Get_Info(INFO_POS, &vPos);

		m_fFov = D3DXToRadian(60.f);
		m_vEye.x += vPos.x;
		m_vEye.y += vPos.y;
		m_vEye.z += vPos.z;
		m_vAt = vPos;
	}
}

void CStaticCamera::Shaking_Camera(const _float& _fPower, const _float& _fLimitTime, const _float& _fTimeDelta)
{
	_vec3 vOldEye = m_vEye;

	m_fFrame += _fTimeDelta;
	m_iReverse *= -1;
	m_vEye.y = m_vEye.y + (_float(m_iReverse) * _fPower * _fTimeDelta);

	if (m_fFrame >= _fLimitTime)
	{
		m_fFrame = 0.f;
		m_vEye = vOldEye;
		m_bPlayerHit = false;
	}
}

void CStaticCamera::ChangeFOV(const _float & _fFOV, const _float & _fDistance, const _float& _fLook, const _float& _fRight)
{
	_vec3 vLook;
	m_pTransform_Target->Get_Info(INFO_LOOK, &vLook);

	_vec3 vRight;
	m_pTransform_Target->Get_Info(INFO_RIGHT, &vRight);

	_vec3 vUp;
	m_pTransform_Target->Get_Info(INFO_UP, &vUp);

	m_vEye = (vLook * -1.f);
	D3DXVec3Normalize(&m_vEye, &m_vEye);
	m_vEye *= _fDistance;

	_vec3 vPos;
	m_pTransform_Target->Get_Info(INFO_POS, &vPos);

	m_fFov = D3DXToRadian(_fFOV);
	m_vEye.x += vPos.x;
	m_vEye.y += vPos.y;
	m_vEye.z += vPos.z;
	m_vAt = vPos + (vLook * _fLook) + (vRight * _fRight);
}
