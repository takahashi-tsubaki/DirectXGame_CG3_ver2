cbuffer cbuff0 : register(b0)
{
	matrix viewproj; //ビュープロジェクション行列
	matrix world;//ワールド行列
	float3 cameraPos;//カメラ座標
};

cbuffer cbuff1 : register(b1)
{
	float3 m_ambient  : packoffset(c0); // アンビエント係数
	float3 m_diffuse  : packoffset(c1); // ディフューズ係数
	float3 m_specular : packoffset(c2); // スペキュラー係数
	float m_alpha : packoffset(c2.w);	// アルファ
}
//cbuffer cbuff2 : register(b2)
//{
//	float3 lightv;
//	float3 lightColor;
//}

//点光源の数
static const int POINTLIGHT_NUM = 3;

struct DirLight
{
	float3 lightv;//方向の単位ベクトル
	float3 lightColor;//ライト色
	uint active;
};

struct PointLight
{
	float3 lightpos;//ライト座標
	float3 lightcolor;//ライト色
	float3 lightatten;//ライト距離減衰係数
	uint active;
};

cbuffer cbuff2 : register(b2)
{
	float3 ambientColor;
	DirLight dirLights[3];
	PointLight pointLights[POINTLIGHT_NUM];
}


// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
	float4 svpos : SV_POSITION; // システム用頂点座標
	float4 worldpos : POSITION;
	float3 normal :NORMAL; // 法線ベクトル
	float2 uv  :TEXCOORD; // uv値
};
