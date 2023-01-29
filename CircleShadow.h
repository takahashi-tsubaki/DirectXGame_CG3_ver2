#pragma once
#include <DirectXMath.h>
class CircleShadow
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
	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		XMVECTOR dir;
		XMFLOAT3 casterPos;
		float distanceCasterLight;
		XMFLOAT3 atten;
		float pad3;
		XMFLOAT2 factorAngleCos;
		unsigned int active;
		float pad4;
	};
public://�����o�֐�
	inline void SetDir(const XMVECTOR& dir) { this->dir = DirectX::XMVector3Normalize(dir); }
	inline const XMVECTOR& GetDir() { return dir; }

	inline void SetCasterPos(const XMFLOAT3& casterPos) { this->casterPos = casterPos; }
	inline const XMFLOAT3& GetCasterPos() { return casterPos; }
	inline void SetDistanceCasterLight(float distanceCasterLight) { this->distanceCasterLight = distanceCasterLight; }
	inline const float GetDistanceCasterLight() { return distanceCasterLight; }
	inline void SetAtten(const XMFLOAT3& atten) { this->atten = atten; }
	inline const XMFLOAT3& GetAtten() { return atten; }

	inline void SetFactorAngle(const XMFLOAT2& factorAngle) {
		this->factorAngleCos.x = cosf(DirectX::XMConvertToRadians(factorAngle.x));
		this->factorAngleCos.y = cosf(DirectX::XMConvertToRadians(factorAngle.y));
	}
	inline const XMFLOAT2& GetFactorAngleCos() { return factorAngleCos; }

	inline void SetActive(bool active) { this->active = active; }
	inline bool isActive() { return active; }

private://�����o�ϐ�
	//����(�P�ʃx�N�g��)
	XMVECTOR dir = { 1,0,0,0 };
	//�L���X�^�[�ƃ��C�g�̋���
	float distanceCasterLight = 100.0f;
	//�L���X�^�[���W
	XMFLOAT3 casterPos = { 0,0,0 };
	//���������W��
	XMFLOAT3 atten = { 0.5f,0.6f,0.0f };
	//�����p�x(�J�n�A�I��)
	XMFLOAT2 factorAngleCos = { 0.2f,0.5f };
	//�L���t���O
	bool active = false;
};