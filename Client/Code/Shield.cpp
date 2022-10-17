#include "stdafx.h"
#include "..\Header\Shield.h"
#include "DeffensiveMatrix.h"

CShield::CShield(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CShield::~CShield()
{
}

HRESULT CShield::Ready_Object(const _vec3 & Position, const _vec3& Direction)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_vPos = Position;
	m_vPos.y = 0.75f;
	m_vDir = Direction;
	m_vScale = { 0.2f,0.2f,0.2f };
	m_fSpeed = 0.25f;
	m_pTransCom->Set_Pos(m_vPos.x, m_vPos.y, m_vPos.z);
	m_pTransCom->Set_Scale(m_vScale.x, m_vScale.y, m_vScale.z);
	return S_OK;
}

_int CShield::Update_Object(const _float & fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_UI, this);

	Move();
	DefensiveMatrix();

	if (m_bDead)
	{
		if (m_pDeffensiveMatrix != nullptr)		
			m_pDeffensiveMatrix->Kill_Obj();	
		return-1;
	}
	return 0;
}

void CShield::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CShield::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pTexture->Set_Texture(0);
	m_pCube->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	
	
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

HRESULT CShield::Add_Component(void)
{
	CComponent* pInstance = nullptr;

	pInstance = m_pCube = dynamic_cast<CCubeTex*>(Engine::Clone_Proto(CUBETEX_COMP));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ CUBETEX_COMP, pInstance });

	pInstance = m_pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Red_Tex"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Red_Tex", pInstance });

	pInstance = m_pTransCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pInstance });

	
	return S_OK;
}

void CShield::Move(void)
{
	_vec3 vPos;
	m_pTransCom->Get_Info(INFO_POS, &vPos);

	if (m_bMove)
	{
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		m_vDir *= m_fSpeed;
		m_pTransCom->Move_Pos(&m_vDir);		
	}	

	if (!m_bMove)
	{		
		m_bShield = true;
	}
}

void CShield::DefensiveMatrix(void)
{
	_vec3 vPos;
	m_pTransCom->Get_Info(INFO_POS, &vPos);

	if (m_bShield)
	{
		if (m_pDeffensiveMatrix == nullptr)
		{
			CLayer* pLayer = Get_Layer(STAGE_SKILL);
			m_pDeffensiveMatrix = CDeffensiveMatrix::Create(m_pGraphicDev, vPos);
			NULL_CHECK_RETURN(m_pDeffensiveMatrix, );
			FAILED_CHECK_RETURN(pLayer->Add_GameList(m_pDeffensiveMatrix), );
		}
	}
}

CShield * CShield::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & Position, const _vec3 & Direction)
{
	CShield* pInstance = new CShield(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(Position,Direction)))
	{
		MSG_BOX("CShield Object Create Fail");
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CShield::Free(void)
{
	CGameObject::Free();
}