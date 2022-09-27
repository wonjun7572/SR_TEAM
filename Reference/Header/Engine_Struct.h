#ifndef Engine_Struct_h__
#define Engine_Struct_h__

namespace Engine
{
	typedef	struct tagVertexColor
	{
		_vec3		vPos;
		_ulong		dwColor;

	}VTXCOL;

	const _ulong		FVF_COL = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;


	typedef struct tagVertexTex
	{
		_vec3		vPos;
		_vec3		vNormal;
		_vec2		vTexUV;

	}VTXTEX;

	const _ulong		FVF_TEX = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

	typedef struct tagVertexCubeTex
	{
		_vec3		vPos;
		_vec3		vTexUV;

	}VTXCUBE;

	const _ulong		FVF_CUBE = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);		// D3DFVF_TEXCOORDSIZE3 : 텍스처의 UV값이 FLOAT 형 3개의 크기만큼이며, 괄호산의 숫자 0의 의미는 본래 버텍스에 텍스처 UV 값이 여러개가 올 수 있는데 그중 0번째 것이 값을 지정하겠다는 의미이다.


	typedef	struct tagIndex16
	{
		_ushort			_0;
		_ushort			_1;
		_ushort			_2;

	}INDEX16;

	typedef	struct tagIndex32
	{
		_ulong		_0;
		_ulong		_1;
		_ulong		_2;

	}INDEX32;

	typedef struct tagMonsterState
	{
		_int iLevel;
		_float fCurrentHp;
		_float fMaxHp;
		_float fDamage;
	}MONSTERABILITY;

	typedef struct tagFrame
	{
		_uint		AnimationID;
		_float		fFrameCnt;		//프레임 카운트
		_float		fFrameMaxCnt;	//프레임 맥스 카운트
		_float		fTimeScale;		//타임범위
		_float		fWidth;			//넓이 
		_float		fHeight;		//높이

	}FRAME;

	//typedef struct tagParticle
	//{
	//	_vec3		Position;
	//	D3DCOLOR	Color;
	//	_float		Size;
	//	static const DWORD FVF_PARTICLE;
	//}PARTICLE;
	//const DWORD PARTICLE::FVF_PARTICLE = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_PSIZE;

	//typedef	struct tagAttribute
	//{
	//	_vec3 Position;
	//	_vec3 Velocity;
	//	_vec3 Acceleration;
	//	_float lifeTime;
	//	_float Age;
	//	D3DXCOLOR	Color;
	//	D3DXCOLOR	ColorFade;
	//	_bool		isAlive;
	//}ATTRIBUTE;


}


#endif // Engine_Struct_h__
