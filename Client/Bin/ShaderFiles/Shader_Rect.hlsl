
struct VS_IN
{
	float3 vertexPosition;
	float3 vertexNormal;
	float2 vertexUV;
}

struct VS_OUT
{
	float4 vertexPosition;
	float3 vertexNormal;
	float2 vertexUV;
}

VS_OUT VS_MAIN(VS_IN in)
{
	VS_OUT vOut;

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

vector PS_MAIN(PS_IN in)
{

}