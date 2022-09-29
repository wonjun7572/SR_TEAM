#include "stdafx.h"
#include "TestCube.h"

#include "Export_Function.h"

CTestCube::CTestCube(LPDIRECT3DDEVICE9 pGraphicDev) : CGameObject(pGraphicDev)
{
}

CTestCube::CTestCube(const CGameObject& rhs) : CGameObject(rhs)
{
}

CTestCube::~CTestCube()
{
}

HRESULT CTestCube::Ready_Object(int PosX, int PosY)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	if (PosX == 0 && PosY == 0) {}
	else
	{ Set_TransformPositon(); }
	
	_vec3 vScale = { 0.5f,0.5f,0.5f };
	m_pTransCom->Set_Scale(&vScale);

	return S_OK;
}

_int CTestCube::Update_Object(const _float& fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_NONALPHA, this);
	return 0;
}

void CTestCube::Render_Object()
{
	if (m_bWireFrame)
		m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pTextureCom->Set_Texture(m_iTexIndex);
	m_pBufferCom->Render_Buffer();

	if (m_bWireFrame)
		m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

// 큐브를 선택 후 터레인 자리위에 올려 놓는 함수
void CTestCube::Set_TransformPositon()
{
	CTerrainTex*	pTerrainBufferCom = dynamic_cast<CTerrainTex*>(Engine::Get_Component(L"Layer_Tool", L"TerrainByTool", L"Proto_TerrainTexCom", ID_STATIC));
	NULL_CHECK_RETURN(pTerrainBufferCom, );

	CTransform*		pTerrainTransformCom = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Tool", L"TerrainByTool", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(pTerrainTransformCom, );

	_vec3 Temp = m_pCalculatorCom->Peek_Target_Vector(g_hWnd, &(_vec3(0.f,0.f,0.f)), pTerrainBufferCom, pTerrainTransformCom);

	m_pTransCom->Set_Pos(Temp.x, Temp.y, Temp.z);
}

bool CTestCube::Set_SelectGizmo()
{
	if (m_pCalculatorCom->Peek_Cube_Target(g_hWnd, &(_vec3(0.f, 0.f, 0.f)), m_pBufferCom, m_pTransCom))
		return true;

	return false;
}

HRESULT CTestCube::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CCubeTex*>(Clone_Proto(L"Proto_CubeTexCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubeTexCom", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_CubePlayerTexture"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubePlayerTexture", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	pComponent = m_pCalculatorCom = dynamic_cast<CCalculator*>(Clone_Proto(L"Proto_CalculatorCom"));
	NULL_CHECK_RETURN(m_pCalculatorCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CalculatorCom", pComponent });

	return S_OK;
}

CTestCube* CTestCube::Create(LPDIRECT3DDEVICE9 pGraphicDev, int Posx, int Posy)
{
	CTestCube*	pInstance = new CTestCube(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(Posx, Posy)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CTestCube::Free()
{
	CGameObject::Free();
}

