
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
	W나누기, 뷰포트 변환, 레스터라이즈는 자체적으로 진행
	PS_IN은 VS_OUT과 동일해야 함
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