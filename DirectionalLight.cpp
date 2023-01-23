#include "DirectionalLight.h"
using namespace DirectX;
ID3D12Device* DirectionalLight::device = nullptr;

void DirectionalLight::StaticInitalize(ID3D12Device* device)
{
	//再初期化チェック
	assert(!DirectionalLight::device);
	//nullptrチェック
	assert(device);
	//情的メンバ変数のセット
	DirectionalLight::device = device;
}

void DirectionalLight::Initalize()
{
	HRESULT result;
	// ヒーププロパティ
	CD3DX12_HEAP_PROPERTIES heapPropsConstantBuffer = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	// リソース設定
	CD3DX12_RESOURCE_DESC resourceDescConstantBuffer =
		CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff);

	// 定数バッファの生成
	result = device->CreateCommittedResource(
		&heapPropsConstantBuffer, D3D12_HEAP_FLAG_NONE, &resourceDescConstantBuffer, D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(&constBuff));
	assert(SUCCEEDED(result));

	//定数バッファへデータ転送
	TransfarConstBuffer();
}

void DirectionalLight::Update()
{
	//値の更新があったときだけ定数バッファに転送する
	if (dirty)
	{
		TransfarConstBuffer();
		dirty = false;
	}
}

void DirectionalLight::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex)
{
	//定数バッファビューをセット
	cmdList->SetGraphicsRootConstantBufferView(rootParameterIndex,constBuff->GetGPUVirtualAddress());
}

DirectionalLight* DirectionalLight::Create()
{
	//3Dオブジェクトのインスタンスの生成
	DirectionalLight* instance = new DirectionalLight();
	//初期化
	instance->Initalize();
	return instance;
}

void DirectionalLight::TransfarConstBuffer()
{

	HRESULT result;
	// 定数バッファにデータ転送
	ConstBufferData* constMap = nullptr;
	result = this->constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result)) {
		constMap->lightv = -lightdir;
		constMap->lightColor =lightcolor;	// 行列の合成	
		constBuff->Unmap(0, nullptr);
	}
}

void DirectionalLight::SetLightDir(const XMVECTOR& lightdir)
{
	//正規化してセット
	this->lightdir = XMVector3Normalize(lightdir);
	dirty = true;
}

void DirectionalLight::SetLightColor(const XMFLOAT3 lightcolor)
{
	this->lightcolor = lightcolor;
	dirty = true;
}
