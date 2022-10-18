
matrix		g_matWorld, g_matView, g_matProj;

struct VS_IN
{
	float3 vertexPosition : POSITION;
	float3 vertexNormal : NORMAL;
	float2 vertexUV : TEXCOORD0;
}

struct VS_OUT
{
	float4 vertexPosition: POSITION;
	float3 vertexNormal;
	float2 vertexUV : TEXCOORD0;
}

VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT vOut = (VS_OUT)0;

	vOut.vertexPosition = mul(vector(In.vertexPosition, 1.f), g_matWorld);
	vOut.vertexPosition = mul(In.vertexPosition, g_matView);
	vOut.vertexPosition = mul(In.vertexPosition, g_matProj);

	vOut.vertexUV = In.vertexUV;

	return vOut;
}

/*
	W나누기, 뷰포트 변환, 레스터라이즈는 자체적으로 진행
	PS_IN은 VS_OUT과 동일해야 함
*/

struct PS_IN
{
	float4 vertexPosition;
	float3 vertexNormal;
	float2 vertexUV;
}

struct PS_OUT
{
	vector vColor : COLOR0;			//	반환값 방식1
};

PS_OUT PS_MAIN(PS_IN in) : COLOR0	//	반환값 방식2
{

}

//vector PS_MAIN(PS_IN in) : COLOR0
//{
//
//}

technique DefaultTechnique
{
	// 위에서부터 0, 1, 2 ... 순서

	pass DefaultPass
	{
		// 진입점 지정, 기능의 캡슐화
		VertexShader = compile vs_3_0 VS_MAIN;
		PixelShader = compile ps_3_0 PS_MAIN;
	};

	pass AnotherPass
	{
		// 용도에 따라 지정, 필요한 셰이딩 기법에 따라 변경
		VertexShader = compile vs_3_0 VS_MAIN_ANOTHER;
		PixelShader = compile ps_3_0 PS_MAIN_ANOTHER;
	};
};