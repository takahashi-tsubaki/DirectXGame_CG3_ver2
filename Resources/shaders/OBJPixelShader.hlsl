#include "OBJShaderHeader.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

//float4 main(VSOutput input) : SV_TARGET
//{
//	float3 light = normalize(float3(1,-1,1)); // 右下奥　向きのライト
//	float light_diffuse = saturate(dot(-light, input.normal));
//	float3 shade_color;
//	shade_color = m_ambient; // アンビエント項
//	shade_color += m_diffuse * light_diffuse;	// ディフューズ項
//	float4 texcolor = tex.Sample(smp, input.uv);
//	return float4(texcolor.rgb * shade_color, texcolor.a * m_alpha);
//}

float4 main(VSOutput input) : SV_TARGET
{
	//float4 texcolor = tex.Sample(smp, input.uv);

	////シェーディングのよる色
	//float4 shadecolor;
	////光沢度
	//const float shininess = 4.0f;
	////頂点から視点への方向ベクトル
	//float3 eyedir = normalize(cameraPos - input.worldpos.xyz);
	////ライトに向かうベクトルと法線の内積
	//float3 dotlightnormal = dot(lightv,input.normal);
	////反射光ベクトル
	//float3 reflect = normalize(-lightv + 2 * dotlightnormal * input.normal);
	////環境反射光
	//float3 ambient = m_ambient;
	////拡散反射光
	//float3 diffuse = dotlightnormal * m_diffuse;
	////鏡面反射光
	//float3 specular = pow(saturate(dot(reflect,eyedir)),shininess)*m_specular;
	////全て加算する
	//shadecolor.rgb = (ambient + diffuse + specular)*lightColor;
	//shadecolor.a = m_alpha;

	float4 texcolor = tex.Sample(smp, input.uv);
	//光沢度
	const float shininess = 4.0f;
	//頂点から視点への方向ベクトル
	float3 eyedir = normalize(cameraPos - input.worldpos.xyz);
	//環境反射光
	float3 ambient = m_ambient;

	//シェーディングのよる色
	float4 shadecolor = float4 (ambientColor * ambient, m_alpha);

	for (int i = 0; i < 3; i++)
	{
		if (dirLights[i].active)
		{
			//ライトに向かうベクトルと法線の内積
			float3 dotlightnormal = dot(dirLights[i].lightv, input.normal);
			//反射光ベクトル
			float3 reflect = normalize(-dirLights[i].lightv + 2 * dotlightnormal * input.normal);
			//拡散反射光
			float3 diffuse = dotlightnormal * m_diffuse;
			//鏡面反射光
			float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;
			//全て加算する
			shadecolor.rgb += (diffuse + specular) * dirLights[i].lightColor;
		}
	}

	for (int i = 0; i < POINTLIGHT_NUM; i++)
	{
		if (pointLights[i].active)
		{
			float3 lightv = pointLights[i].lightpos - input.worldpos.xyz;
			//ベクトルの長さ
			float d = length(lightv);
			//正規化し、単位ベクトルにする
			lightv = normalize(lightv);
			float atten = 1.0f / (pointLights[i].lightatten.x + pointLights[i].lightatten.y * d + pointLights[i].lightatten.z * d * d);
			//ライトに向かうベクトルと法線の内積
			float3 dotlightnormal = dot(lightv, input.normal);
			//反射光ベクトル
			float3 reflect = normalize(-lightv + 2 * dotlightnormal * input.normal);
			//拡散反射光
			float3 diffuse = dotlightnormal * m_diffuse;
			//鏡面反射光
			float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;
			//全て加算する
			shadecolor.rgb += atten * (diffuse + specular) * pointLights[i].lightcolor;
		}
	}

	//return shadecolor * texcolor;
	return shadecolor * texcolor;
}