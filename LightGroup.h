#pragma once
#include <DirectXMath.h>
#include <d3d12.h>
#include <d3dx12.h>

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
class LightGroup
{
private:
	// Microsoft::WRL::���ȗ�
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	static const int DirLightNum = 3;

	//�_�����̐�
	static const int PointLightNum = 3;
	//�X�|�b�g���C�g�̐�
	static const int SpotLightNum = 3;

public://�T�u�N���X
	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		//�����̐F
		XMFLOAT3 ambientColor;
		float pad1;
		//���s�����p
		DirectionalLight::ConstBufferData dirLights[DirLightNum];
		//�_�����p
		PointLight::ConstBufferData pointLights[PointLightNum];
		//�X�|�b�g���C�g�p
		SpotLight::ConstBufferData spotLights[SpotLightNum];
	};

private://��I�����o�ϐ�
	//�f�o�C�X
	static ID3D12Device* device;

public://��I�����o�֐�
	/// <summary>
	/// ��I������
	/// </summary>
	static void StaticInitialize(ID3D12Device* device);

private://�����o�ϐ�
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;
	//�����̐F
	XMFLOAT3 ambientColor = { 1,1,1 };
	//���s�����̔z��
	DirectionalLight dirLights[DirLightNum];
	//�_�[�e�B�t���O
	bool dirty = false;
	//�_�����̔z��
	PointLight pointLights[PointLightNum];
	//�X�|�b�g���C�g�̔z��
	SpotLight spotLights[SpotLightNum];

public://�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="cmdList"></param>
	/// <param name="rootParameterIndex"></param>
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);

	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <returns></returns>
	static LightGroup* Create();

	/// <summary>
	/// �萔�o�b�t�@�]��
	/// </summary>
	void TransfarConstBuffer();

	/// <summary>
	/// �A���r�G���g�F���Z�b�g
	/// </summary>
	void SetAmbientColor(const XMFLOAT3 &color);

	/// <summary>
	/// ���s�����̗L���t���O���Z�b�g
	/// </summary>
	void SetDirLightActive(int index,bool active);

	/// <summary>
	/// ���s�����̃��C�g�������Z�b�g
	/// </summary>
	void SetDirLightDir(int index, const XMVECTOR &lightdir);

	/// <summary>
	/// ���s�����̃��C�g�F���Z�b�g
	/// </summary>
	void SetDirLightColor(int index,const XMFLOAT3 &lightcolor);

	/// <summary>
	/// �W���̃��C�g�ݒ�
	/// </summary>
	void DefaultLightSetting();

	void SetPointLightActive(int index, bool active);
	void SetPointLightPos(int index, const XMFLOAT3& lightpos);
	void SetPointLightColor(int index, const XMFLOAT3& lightcolor);
	void SetPointLightAtten(int index, const XMFLOAT3& lightatten);

	void SetSpotLightActive(int index, bool active);
	void SetSpotLightDir(int index, const XMVECTOR& lightdir);
	void SetSpotLightPos(int index, const XMFLOAT3& lightpos);
	void SetSpotLightColor(int index, const XMFLOAT3& lightcolor);
	void SetSpotLightAtten(int index, const XMFLOAT3& lightatten);
	void SetSpotLightFactorAngle(int index, const XMFLOAT2& lightFactorAngle);
};

