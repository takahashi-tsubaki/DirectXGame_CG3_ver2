#include "OBJShaderHeader.hlsli"
////Lambart反射
//VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
//{
//	//右、下、奥の方向を向いたライト
//	float3 lightdir = float3(1,-1,1);
//	lightdir = normalize(lightdir);
//	//ライトの色
//	float3 lightColor = float3(1, 1, 1);
//	// ピクセルシェーダーに渡す値
//	VSOutput output; 
//	output.svpos = mul(mat, pos);
//	//Lambart反射の計算
//	output.color.rgb = dot(-lightdir, normal) * m_diffuse * lightColor;
//	output.color.a = m_alpha;
//	output.uv = uv;
//	return output;
//}

//Phong反射
VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
{

	float3 lightdir = float3(1, -1, 1);
	lightdir = normalize(lightdir);

	float3 lightColor = float3(1, 1, 1);

	//環境反射光
	float3 ambient = m_ambient;
	//拡散反射光
	float3 diffuse = dot(-lightdir, normal)* m_diffuse;
	//視点座標
	const float3 eye = float3 (0, 0, -20);
	//光沢度
	float shininess = 4.0f;
	//頂点から視点への方向ベクトル
	float3 eyedir = normalize(eye-pos.xyz);
	//反射光ベクトル
	float3 reflect = normalize(lightdir + 2 * dot(-lightdir, normal) * normal);
	//鏡面反射光
	float3 specular = pow(saturate(dot(reflect,eyedir)),shininess)*m_specular;
	
	VSOutput output;
	output.svpos = mul(mat, pos);
	//Lambart反射の計算
	output.color.rgb = (ambient+diffuse+specular) * lightColor;
	output.color.a = m_alpha;
	output.uv = uv;
	return output;

}