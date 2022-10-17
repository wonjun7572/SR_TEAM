#pragma once
#include "Component.h"
class CShader : public CComponent
{
private:
	explicit CShader(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CShader(const CShader& rhs);
	virtual ~CShader() = default;

public:
	HRESULT	Ready_Shader(const _tchar* ShaderFileName);
public:
	void	Begin_Shader(void);
	void	End_Shader(void);

private:
	LPD3DXEFFECT	m_pEffect = nullptr;

public:
	static CShader*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* ShaderFileName);
	virtual CComponent* Clone(void);
	virtual void		Free(void);
};

