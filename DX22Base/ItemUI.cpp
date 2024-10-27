#include "ItemUI.h"
#include <DirectXMath.h>
#include "Sprite.h"


ItemUI::ItemUI():
	m_pTexture(nullptr)
{
	//�e�N�X�`����ݒ�	
	m_pTexture = New(Texture)();
	if (FAILED(m_pTexture->Create("Assets/Texture/takodane.png")))
	{
		MessageBox(NULL, " Assets/Texture :ItemUI", "Error", MB_OK);
	}

}

ItemUI::~ItemUI()
{
	if (m_pTexture)
	{
		delete m_pTexture;
	}
}

void ItemUI::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	//���[���h�s���XY�̂ݍl�����č쐬
	DirectX::XMMATRIX Tm = DirectX::XMMatrixTranslation(1080.0f, 520.0f, 0.0f);
	DirectX::XMMATRIX Sm = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
	DirectX::XMMATRIX world = Sm * Tm;
	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);
	//DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	//�r���[�s��͂QD���Ƃ��܂�J�����̈ʒu�͊֌W�Ȃ��A�P�ʍs���ݒ�
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s��ɂ͂QD�Ƃ��ĕ\������ׂ̍s���
	//���̍s��ŃX�N���[���̑傫�������܂�
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f,1280.0f,720.0f,0.0f, 0.1f,10.0f); // ���Ƃ����l,��Ŏ�������
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(300.0f,-300.0f));
	Sprite::SetTexture(m_pTexture);
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::Draw();
}
