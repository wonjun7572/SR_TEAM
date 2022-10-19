#pragma once
#include "Component.h"
#include "Engine_Include.h"

BEGIN(Engine)

/* �ܺο��� �ۼ��� ���̴��ڵ�(����)�� �����Ͽ� ��ü(ID3DXEffect)ȭ ��Ų��. */
class ENGINE_DLL CShader : public CComponent
{
public:
	explicit CShader(LPDIRECT3DDEVICE9 pDevice);
	explicit CShader(const CShader& rhs);
	virtual ~CShader() = default;

public:
	HRESULT Ready_Shader(const _tchar* pShaderFilePath);

	/* �������� ���̴��� �������Ѵ�. */
	HRESULT Begin_Shader(_uint iPassIndex);

	/* ���������� �����Լ��� ȣ���Ѵٸ� Transform�� ���� ����� ���������. */

	HRESULT End_Shader();

public:
	HRESULT Set_RawValue(D3DXHANDLE hHandle, const void* pData, _uint iLength);
	HRESULT Set_Texture(D3DXHANDLE hHandle, IDirect3DBaseTexture9* pTexture);

private:
	LPD3DXEFFECT				m_pEffect = nullptr;

public:
	static CShader*		Create(LPDIRECT3DDEVICE9 pDevice, const _tchar* pShaderFilePath);
	virtual CComponent*	Clone(void);

private:
	virtual void Free(void);
};

END