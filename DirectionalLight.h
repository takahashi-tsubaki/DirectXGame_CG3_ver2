#pragma once
#include <DirectXMath.h>
#include <d3d12.h>
#include <d3dx12.h>

class DirectionalLight
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
	// 定数バッファ用データ構造体
	struct ConstBufferData
	{
		XMVECTOR lightv;//ライトへの方向を表すベクトル
		XMFLOAT3 lightColor;//ライトの色
		//有効フラグ
		unsigned int active;
	};

private://情的メンバ変数
	//デバイス
	static ID3D12Device* device;

public://情的メンバ関数
	/// <summary>
	/// 情的初期化
	/// </summary>
	static void StaticInitalize(ID3D12Device* device);

private://メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource>constBuff;
	//ライト光線方向(単位ベクトル)
	XMVECTOR lightdir = { 1,0,0,0 };
	//ライト色
	XMFLOAT3 lightcolor = { 1,1,1 };
	//ダーティフラグ
	bool dirty = false;
	//有効フラグ
	bool active = false;

public:
	/// <summary>
	/// 定数バッファ転送
	/// </summary>
	void TransfarConstBuffer();

	/// <summary>
	/// ライト方向をセット
	/// </summary>
	/// <param name="lightdir"></param>
	void SetLightDir(const XMVECTOR& lightdir);

	/// <summary>
	/// ライト方向の取得
	/// </summary>
	XMVECTOR GetLightDir() { return lightdir; }

	/// <summary>
	/// ライト色をセット
	/// </summary>
	void SetLightColor(const XMFLOAT3 lightcolor);

	/// <summary>
	/// ライト色の取得
	/// </summary>
	XMFLOAT3 GetLightColor() { return lightcolor; }

	/// <summary>
	/// 有効フラグをセット
	/// </summary>
	/// <param name="active"></param>
	inline void SetActive(bool active){this->active = active;}

	/// <summary>
	/// 有効チェック
	/// </summary>
	/// <returns></returns>
	inline bool isActive() { return active; }

	/// <summary>
	/// 初期化
	/// </summary>
	void Initalize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList*cmdList,UINT rootParameterIndex);


	static DirectionalLight* Create();
};

