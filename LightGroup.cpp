#include "LightGroup.h"
#include <cassert>
using namespace DirectX;

ID3D12Device *LightGroup::device = nullptr;

void LightGroup::StaticInitialize(ID3D12Device* device)
{

	//再初期化チェック
	assert(!LightGroup::device);

	//nullptrチェック
	assert(device);


	LightGroup::device = device;

}

void LightGroup::Initialize()
{

	DefaultLightSetting();

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

void LightGroup::Update()
{
	if (dirty)
	{
		TransfarConstBuffer();
		dirty = false;
	}
}

void LightGroup::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex)
{
	//定数バッファビューをセット
	cmdList->SetGraphicsRootConstantBufferView(rootParameterIndex, constBuff->GetGPUVirtualAddress());
}

LightGroup* LightGroup::Create()
{

	//3Dオブジェクトのインスタンスの生成
	LightGroup* instance = new LightGroup();
	//初期化
	instance->Initialize();
	return instance;
}

void LightGroup::TransfarConstBuffer()
{
	HRESULT result;
	// 定数バッファにデータ転送
	ConstBufferData* constMap = nullptr;
	result = this->constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result)) {
		constMap->ambientColor = ambientColor;

		for (int i = 0; i < DirLightNum; i++)
		{
			//ライトが有効なら設定を転送
			if (dirLights[i].isActive())
			{
				constMap->dirLight[i].active = 1;
				constMap->dirLight[i].lightv = -dirLights[i].GetLightDir();
				constMap->dirLight[i].lightColor = dirLights[i].GetLightColor();
			}
			//ライトが有効なら転送しない
			else
			{
				constMap->dirLight[i].active = 0;
			}
		}

		constBuff->Unmap(0, nullptr);
	}
}

void LightGroup::SetAmbientColor(const XMFLOAT3& color)
{
	ambientColor = color;
	dirty = true;
}

void LightGroup::SetDirLightActive(int index, bool active)
{
	assert(0 <= index && index < DirLightNum);
	dirLights[index].SetActive(active);
}

void LightGroup::SetDirLightDir(int index, const XMVECTOR& lightdir)
{
	assert(0 <= index && index < DirLightNum);
	dirLights[index].SetLightDir(lightdir);
	dirty = true;
}

void LightGroup::SetDirLightColor(int index, const XMFLOAT3& lightcolor)
{
	assert(0 <= index && index < DirLightNum);
	dirLights[index].SetLightColor(lightcolor);
	dirty = true;
}

void LightGroup::DefaultLightSetting()
{
	dirLights[0].SetActive(true);
	dirLights[0].SetLightColor({1.0f,1.0f,1.0f});
	dirLights[0].SetLightDir({ 0.0f,-1.0f,0.0f,0 });

	dirLights[1].SetActive(true);
	dirLights[1].SetLightColor({ 1.0f,1.0f,1.0f });
	dirLights[1].SetLightDir({ +0.5f,+0.1f,+0.2f,0 });

	dirLights[2].SetActive(true);
	dirLights[2].SetLightColor({ 1.0f,1.0f,1.0f });
	dirLights[2].SetLightDir({ -0.5f,+0.1f,-0.2f,0 });

}
