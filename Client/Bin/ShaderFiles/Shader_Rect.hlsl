
/* 상수테이블 */
matrix		g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;
float		g_fData = 10.f;

/* VS : VERTEX SHADER */
/* 정점에 대한 셰이딩을 수행하낟. */
/* 예 : 정점의 월드, 뷰, 투영변환. */
/* MAIN : 진입점함수. */

/* 그리고자하는 정점의 정보를 받아오기위한 구조체. */
struct VS_IN
{
	// float float2, float3, float4 == vector
	// float4x4 == matrix
	float3		vPosition : POSITION;
	float2		vTexUV : TEXCOORD0;
};

struct VS_OUT
{
	float4		vPosition : POSITION;
	float2		vTexUV : TEXCOORD0;
};

//VS_OUT VS_MAIN(float4 vPosition : POSITION, float2 vTexUV : TEXCOORD0)
//{
//	VS_OUT		Out;
//
//	//Out.vPosition = ;
//
//	return Out;
//}

/* 정점의 변환(월드, 뷰, 투영) */
/* 정정정보의 수정, 변경 */
VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT		Out = (VS_OUT)0;

	vector		vPosition = mul(vector(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vTexUV = In.vTexUV;

	return Out;
}

/* 정점세개가 모이면. */
/* w나누기연산. */
/* 뷰포트 변환.(윈도우좌표로 변환한다. ) */
/* 래스터라이즈 (픽셀을 만든다. )*/

struct PS_IN
{
	float4		vPosition : POSITION;
	float2		vTexUV : TEXCOORD0;
};

struct PS_OUT
{
	vector		vColor : COLOR0;
};




/* PS : PIXEL SHADER */
/* 픽셀의 색을 결정한다. */
/* 정점 세개에 둘러쌓여진 영역에 있는 픽셀의 갯수만큼 PS_MAIN이라는 함수를 호출하게된다. */

PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	Out.vColor.ra = 1.f;

	return Out;
}

//vector PS_MAIN(PS_IN In) : COLOR0
//{
//
//
//}


technique DefaultTechnique
{
	pass Default
	{
		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}

	//pass Hide
	//{
	//	VertexShader = compile vs_3_0 VS_MAIN_HIDE();
	//	PixelShader = compile ps_3_0 PS_MAIN_HIDE();
	//}
}


