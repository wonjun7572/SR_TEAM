
matrix		g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;

bool		g_isHit = false;

texture		g_DefaultTexture;

sampler		DefaultSampler = sampler_state
{
	texture = g_DefaultTexture;
	minfilter = linear;
	magfilter = linear;
};

struct VS_IN
{
	float3		vPosition : POSITION;
	float3		vNormal : NORMAL;
	float2		vTexUV : TEXCOORD0;
};

struct VS_OUT
{
	float4		vPosition : POSITION;
	float3		vNormal : NORMAL;
	float2		vTexUV : TEXCOORD0;
};

VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT		Out = (VS_OUT)0;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vNormal = In.vNormal;
	Out.vTexUV = In.vTexUV;

	return Out;
}

struct PS_IN
{
	float4		vPosition : POSITION;
	float2		vTexUV : TEXCOORD0;
};

struct PS_OUT
{
	vector		vColor : COLOR0;
};

PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	vector		vColor = (vector)1.f;

	Out.vColor = tex2D(DefaultSampler, In.vTexUV);

	//if (true == g_isHit)
	//	vColor.rgb = 1.f;
	//else
	//	vColor = tex2D(DefaultSampler, In.vTexUV);

	//vColor.a = In.vTexUV.y;

	//Out.vColor = vColor;

	return Out;
}

technique DefaultTechnique
{
	pass Default
	{
	/*	AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		BlendOp = Add;*/

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}
}