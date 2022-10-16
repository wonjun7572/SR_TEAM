#include "stdafx.h"
#include "..\Header\TransAxisBox.h"

#include "Export_Function.h"

USING(Engine)

CTransAxisBox::CTransAxisBox(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev), m_bIsRoot(false)
{
}

CTransAxisBox::~CTransAxisBox()
{
}

HRESULT CTransAxisBox::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransCom->Set_Pos(0.f, 0.f, 0.f);
	m_pTransCom->Set_Scale(1.f, 1.f, 1.f);
	m_pTransCom->Static_Update();

	m_fX = 0.f;
	m_fY = 0.f;
	m_fZ = 0.f;

	return S_OK;
}

_int CTransAxisBox::Update_Object(const _float & fTimeDelta)
{
	if (m_bDead)
	{
		return -1;
	}

	Engine::CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_ANIOBJ, this);

	_matrix matWorld, matParent;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matParent);

	m_pTransCom->Worldspace_By_Quarternion();

	m_pTransCom->Get_WorldMatrix(&matWorld);

	D3DXMatrixTranslation(&m_AxisMoveMatrix, m_fX, m_fY, m_fZ);

	matWorld = m_AxisMoveMatrix * matWorld;

	for (auto& iter : m_ParentList)
	{
		_matrix matTemp;
		iter->Get_Transform()->Get_WorldMatrix(&matTemp);

		_vec3 vScale, vPos;
		D3DXQUATERNION qRot;

		D3DXMatrixDecompose(&vScale, &qRot, &vPos, &matTemp);

		_matrix matRot, matTrans, matResult;
		D3DXMatrixRotationQuaternion(&matRot, &qRot);

		D3DXMatrixTranslation(&matTrans, vPos.x, vPos.y, vPos.z);

		matResult = matRot * matTrans;

		matParent *= matResult;
	}

	m_FinalWorldMatrix = matWorld * matParent;

	return 0;
}

void CTransAxisBox::LateUpdate_Object(void)
{
	Engine::CGameObject::LateUpdate_Object();
}

void CTransAxisBox::Render_Object(void)
{
	//m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	//빛표현 블랜딩
	//m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	//간단한 그림자
	//m_pGraphicDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	//m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	//곱셈합성 스킬뷰에 쓰면 좋을듯
	//m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
	//m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);

	//제곱합성 밝은색은 그대로, 어두운색은 더 어둡게 ( 보스전 방 꾸미는 데 쓰면 좋을듯)
	//m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR);
	//m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);

	//네거티브, 포지티브 합성 (검<->흰)
	//m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	//m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);

	//불투명
	//m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	//m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	//if(! (dynamic_cast<CBaseMapping*>(Engine::Get_GameObject(STAGE_MAPPING, L"BaseMapping"))->Get_Worldmap()))

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_FinalWorldMatrix);
	m_pTextureCom->Set_Texture(m_iTexIndex);
	m_pBufferCom->Render_Buffer();
	//m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	// 설치물이면 그 설치하기전까지는 알파먹고 설치되면 알파꺼져서 그 위치 생성되고
}

bool CTransAxisBox::Set_SelectGizmo(void)
{
	_matrix matCamera;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matCamera);
	D3DXMatrixInverse(&matCamera, nullptr, &matCamera);

	_vec3	vEye = { matCamera.m[3][0], matCamera.m[3][1], matCamera.m[3][2] };

	return false;
}

HRESULT CTransAxisBox::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CFlexibleAxisCube*>(Clone_Proto(L"Proto_FlexibleAxisCubeCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_FlexibleAxisCubeCom", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_CubePlayerTexture"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubePlayerTexture", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_TransformCom", pComponent });

	pComponent = m_pCalculatorCom = dynamic_cast<CCalculator*>(Clone_Proto(L"Proto_CalculatorCom"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CalculatorCom", pComponent });

	pComponent = m_pQuaternion = dynamic_cast<CQuarternion*>(Clone_Proto(L"Proto_QuaternionCom"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_QuaternionCom", pComponent });

	return S_OK;
}

void CTransAxisBox::AxisMatrixCreate(void)
{
	D3DXMatrixTranslation(&m_AxisMoveMatrix, m_fX, m_fY, m_fZ);

	m_pTransCom->m_matWorld *= m_AxisMoveMatrix;
}

CTransAxisBox * CTransAxisBox::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTransAxisBox* pInstance = new CTransAxisBox(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		MSG_BOX("TransAxisBox Create Fail");
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CTransAxisBox::Free(void)
{
	CGameObject::Free();
}
