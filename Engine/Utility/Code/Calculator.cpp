#include "..\..\Header\Calculator.h"
#include "Export_Function.h"

USING(Engine)

CCalculator::CCalculator(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev)
{

}

Engine::CCalculator::CCalculator(const CCalculator& rhs)
	: CComponent(rhs)
{

}

CCalculator::~CCalculator()
{
}

HRESULT CCalculator::Ready_Calculator(void)
{

	return S_OK;
}

Engine::_float CCalculator::HeightOnTerrain(_vec3* pPos, const _vec3* pTerrainVtxPos,
	const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv)
{
	_ulong	dwIndex = _ulong(pPos->z / dwVtxItv) * dwCntX + _ulong(pPos->x / dwVtxItv);
	_float	fWidth = (pPos->x - pTerrainVtxPos[dwIndex + dwCntX].x) / dwVtxItv;
	_float	fHeight = (pTerrainVtxPos[dwIndex + dwCntX].z - pPos->z) / dwVtxItv;

	D3DXPLANE		Plane;

	// ¿À¸¥ÂÊ À§ »ï°¢Çü
	if (fWidth > fHeight)
	{
		D3DXPlaneFromPoints(&Plane,
			&pTerrainVtxPos[dwIndex + dwCntX],
			&pTerrainVtxPos[dwIndex + dwCntX + 1],
			&pTerrainVtxPos[dwIndex + 1]);

	}
	// ¿ÞÂÊ ¾Æ·¡ »ï°¢Çü
	else
	{
		D3DXPlaneFromPoints(&Plane,
			&pTerrainVtxPos[dwIndex + dwCntX],
			&pTerrainVtxPos[dwIndex + 1],
			&pTerrainVtxPos[dwIndex]);
	}

	pPos->y = (-Plane.a * pPos->x - Plane.c * pPos->z - Plane.d) / Plane.b;

	return pPos->y;
}

_vec3 CCalculator::Peek_Target_Vector(HWND hWnd, _vec3 * SrcPos, const CTerrainTex * pTerrainTex, const CTransform * pTransform)
{
	POINT	WindowPt{};
	GetCursorPos(&WindowPt);
	ScreenToClient(hWnd, &WindowPt);

	_vec3	vPoint{};

	D3DVIEWPORT9	Viewport;
	ZeroMemory(&Viewport, sizeof(D3DVIEWPORT9));
	m_pGraphicDev->GetViewport(&Viewport);

	vPoint.x = WindowPt.x / (Viewport.Width * 0.5f) - 1.f;
	vPoint.y = WindowPt.y / -(Viewport.Height * 0.5f) + 1.f;
	vPoint.z = 0.f;

	_matrix			matProj;
	D3DXMatrixIdentity(&matProj);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixInverse(&matProj, nullptr, &matProj);
	D3DXVec3TransformCoord(&vPoint, &vPoint, &matProj);

	_vec3 vRayPos = *SrcPos;
	_vec3 vRayDir = vPoint - vRayPos;

	_matrix			matView;
	D3DXMatrixIdentity(&matView);
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, nullptr, &matView);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);

	_matrix			matWorld;
	D3DXMatrixIdentity(&matWorld);
	pTransform->Get_WorldMatrix(&matWorld);
	D3DXMatrixInverse(&matWorld, nullptr, &matWorld);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matWorld);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matWorld);

	const _vec3*	Vertex = pTerrainTex->Get_VtxPos();
	_ulong			dwVtxIndex[3]{};
	_float			fU, fV, fDist;

	for (_ulong dwIndex = 0; dwIndex < (VTXCNTX - 1) * (VTXCNTZ - 1) * 2; ++dwIndex)
	{
		//	¿ì»ó´Ü »ï°¢Çü
		dwVtxIndex[0] = dwIndex + VTXCNTX;
		dwVtxIndex[1] = dwIndex + VTXCNTX + 1;
		dwVtxIndex[2] = dwIndex + 1;

		if (D3DXIntersectTri
			(&Vertex[dwVtxIndex[1]],
				&Vertex[dwVtxIndex[0]],
				&Vertex[dwVtxIndex[2]],
				&vRayPos, &vRayDir,
				&fU, &fV, &fDist))
		{
			return _vec3(Vertex[dwVtxIndex[1]].x + (Vertex[dwVtxIndex[0]].x - Vertex[dwVtxIndex[1]].x) * fU,
				0.f,
				Vertex[dwVtxIndex[1]].z + (Vertex[dwVtxIndex[2]].z - Vertex[dwVtxIndex[1]].z) * fV);
		}

		// ÁÂÇÏ´Ü »ï°¢Çü
		dwVtxIndex[0] = dwIndex + VTXCNTX;
		dwVtxIndex[1] = dwIndex + 1;
		dwVtxIndex[2] = dwIndex;

		if (D3DXIntersectTri
			(&Vertex[dwVtxIndex[2]],
				&Vertex[dwVtxIndex[1]],
				&Vertex[dwVtxIndex[0]],
				&vRayPos, &vRayDir,
				&fU, &fV, &fDist))
		{
			return _vec3(Vertex[dwVtxIndex[2]].x + (Vertex[dwVtxIndex[1]].x - Vertex[dwVtxIndex[2]].x) * fU,
				0.f,
				Vertex[dwVtxIndex[2]].z + (Vertex[dwVtxIndex[0]].z - Vertex[dwVtxIndex[2]].z) * fV);
		}
	}

	return _vec3(0, 0, 0);
}



CComponent* CCalculator::Clone(void)
{
	return new CCalculator(*this);
}

CCalculator* CCalculator::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCalculator*	pInstance = new CCalculator(pGraphicDev);

	if (FAILED(pInstance->Ready_Calculator()))
	{
		MSG_BOX("Calculator Create Failed");
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CCalculator::Free(void)
{
	CComponent::Free();
}
