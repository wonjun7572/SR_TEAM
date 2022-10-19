
/* ������̺� */
matrix		g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;
float		g_fData = 10.f;

/* VS : VERTEX SHADER */
/* ������ ���� ���̵��� �����ϳ�. */
/* �� : ������ ����, ��, ������ȯ. */
/* MAIN : �������Լ�. */

/* �׸������ϴ� ������ ������ �޾ƿ������� ����ü. */
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

/* ������ ��ȯ(����, ��, ����) */
/* ���������� ����, ���� */
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

/* ���������� ���̸�. */
/* w�����⿬��. */
/* ����Ʈ ��ȯ.(��������ǥ�� ��ȯ�Ѵ�. ) */
/* �����Ͷ����� (�ȼ��� �����. )*/

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
/* �ȼ��� ���� �����Ѵ�. */
/* ���� ������ �ѷ��׿��� ������ �ִ� �ȼ��� ������ŭ PS_MAIN�̶�� �Լ��� ȣ���ϰԵȴ�. */

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


