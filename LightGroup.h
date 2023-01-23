#pragma once
#include <DirectXMath.h>
#include <d3d12.h>
#include <d3dx12.h>
#include "DirectionalLight.h"
class LightGroup
{
private:
	// Microsoft::WRL::を省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	static const int DirLightNum = 3;

public://サブクラス
	//定数バッファ用データ構造体
	struct ConstBufferData
	{
		//環境光の色
		XMFLOAT3 ambientColor;
		float pad1;
		//平行光源用
		DirectionalLight::ConstBufferData dirLight[DirLightNum];
	};

private://情的メンバ変数
	//デバイス
	static ID3D12Device* device;

public://情的メンバ関数
	/// <summary>
	/// 情的初期化
	/// </summary>
	static void StaticInitialize(ID3D12Device* device);

private://メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	//環境光の色
	XMFLOAT3 ambientColor = { 1,1,1 };
	//平行光源の配列
	DirectionalLight dirLights[DirLightNum];
	//ダーティフラグ
	bool dirty = false;
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="cmdList"></param>
	/// <param name="rootParameterIndex"></param>
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);

	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <returns></returns>
	static LightGroup* Create();

	/// <summary>
	/// 定数バッファ転送
	/// </summary>
	void TransfarConstBuffer();

	/// <summary>
	/// アンビエント色をセット
	/// </summary>
	void SetAmbientColor(const XMFLOAT3 &color);

	/// <summary>
	/// 平行光源の有効フラグをセット
	/// </summary>
	void SetDirLightActive(int index,bool active);

	/// <summary>
	/// 平行光源のライト方向をセット
	/// </summary>
	void SetDirLightDir(int index, const XMVECTOR &lightdir);

	/// <summary>
	/// 平行光源のライト色をセット
	/// </summary>
	void SetDirLightColor(int index,const XMFLOAT3 &lightcolor);

	/// <summary>
	/// 標準のライト設定
	/// </summary>
	void DefaultLightSetting();

};

