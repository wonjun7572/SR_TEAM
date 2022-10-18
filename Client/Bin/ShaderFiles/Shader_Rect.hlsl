
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
	W������, ����Ʈ ��ȯ, �����Ͷ������ ��ü������ ����
	PS_IN�� VS_OUT�� �����ؾ� ��
*/

struct PS_IN
{
	float4 vertexPosition;
	float3 vertexNormal;
	float2 vertexUV;
}

struct PS_OUT
{
	vector vColor : COLOR0;			//	��ȯ�� ���1
};

PS_OUT PS_MAIN(PS_IN in) : COLOR0	//	��ȯ�� ���2
{

}

//vector PS_MAIN(PS_IN in) : COLOR0
//{
//
//}

technique DefaultTechnique
{
	// ���������� 0, 1, 2 ... ����

	pass DefaultPass
	{
		// ������ ����, ����� ĸ��ȭ
		VertexShader = compile vs_3_0 VS_MAIN;
		PixelShader = compile ps_3_0 PS_MAIN;
	};

	pass AnotherPass
	{
		// �뵵�� ���� ����, �ʿ��� ���̵� ����� ���� ����
		VertexShader = compile vs_3_0 VS_MAIN_ANOTHER;
		PixelShader = compile ps_3_0 PS_MAIN_ANOTHER;
	};
};