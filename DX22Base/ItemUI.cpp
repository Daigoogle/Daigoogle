#include "ItemUI.h"
#include <DirectXMath.h>
#include "Sprite.h"


ItemUI::ItemUI():
	m_pTexture(nullptr)
{
	//テクスチャを設定	
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

	//ワールド行列はXYのみ考慮して作成
	DirectX::XMMATRIX Tm = DirectX::XMMatrixTranslation(1080.0f, 520.0f, 0.0f);
	DirectX::XMMATRIX Sm = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
	DirectX::XMMATRIX world = Sm * Tm;
	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);
	//DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	//ビュー行列は２Dだとあまりカメラの位置は関係ない、単位行列を設定
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列には２Dとして表示する為の行列を
	//この行列でスクリーンの大きさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f,1280.0f,720.0f,0.0f, 0.1f,10.0f); // 幅とか数値,後で実装する
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	//スプライトの設定
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(300.0f,-300.0f));
	Sprite::SetTexture(m_pTexture);
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::Draw();
}
