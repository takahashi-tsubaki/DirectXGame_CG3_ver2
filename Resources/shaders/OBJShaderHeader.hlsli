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

//
static const int DIRLIGHT_NUM = 3;
//点光源の数
static const int POINTLIGHT_NUM = 3;
//スポットライトの数
static const int SPOTLIGHT_NUM = 3;
//丸影の数
static const int CIRCLESHADOW_NUM = 1;

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

struct SpotLight
{
	float3 lightv;//ライトの光線方向の逆ベクトル
	float3 lightpos;//ライト座標
	float3 lightcolor;//ライト色
	float3 lightatten;//ライト距離減衰係数
	float2 lightfactoranglecos;//ライト減衰角度のコサイン
	uint active;
};

struct CircleShadow
{
	float3 dir;
	float3 casterPos;
	float distanceCasterLight;
	float3 atten;
	float2 factorAngleCos;//
	uint active;
};

cbuffer cbuff2 : register(b2)
{
	float3 ambientColor;
	DirLight dirLights[DIRLIGHT_NUM];
	PointLight pointLights[POINTLIGHT_NUM];
	SpotLight spotLights[SPOTLIGHT_NUM];
	CircleShadow circleShadows[CIRCLESHADOW_NUM];

}


// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
	float4 svpos : SV_POSITION; // システム用頂点座標
	float4 worldpos : POSITION;
	float3 normal :NORMAL; // 法線ベクトル
	float2 uv  :TEXCOORD; // uv値
};
