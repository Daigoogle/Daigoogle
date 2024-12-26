#include "DirectX11SetUp.h"
#include "Window.h"

DirectX11SetUp::DirectX11SetUp()
	:Singleton(UPDATE_ORDER::NO_UPDATE)
	, m_pDevice(nullptr)
	, m_pContext(nullptr)
	, m_pSwapChain(nullptr)
	, m_pRTV(nullptr)
	, m_pDSV(nullptr)
	, m_bCheckIn(false)
	, m_BufferSize({ 0,0 })
	, m_hWnd(nullptr)
	, m_thisFullScreen(false)
{

}

DirectX11SetUp::~DirectX11SetUp()
{
	SAFE_DELETE(m_pDSV);
	SAFE_DELETE(m_pRTV);

	for (int i = 0; i < SAMPLER_MAX; ++i)
		SAFE_RELEASE(m_pSamplerState[i]);
	for (int i = 0; i < BLEND_MAX; ++i)
		SAFE_RELEASE(m_pBlendState[i]);
	for (int i = 0; i < 3; ++i)
		SAFE_RELEASE(m_pRasterizerState[i]);
	if (m_pContext)
		m_pContext->ClearState();
	SAFE_RELEASE(m_pContext);
	if (m_pSwapChain)
		m_pSwapChain->SetFullscreenState(false, NULL);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pDevice);
}

bool DirectX11SetUp::Init()
{
	Window& wind = Window::GetInstance();

	SettingData(wind.GetHWnd(), {(int)wind.GetScreenWidth(),(int)wind.GetScreenHeight()},wind.IsFullScreen());
	return true;
}

void DirectX11SetUp::BeginDraw()
{
	float color[4] = { 0.85f, 0.84f, 0.84f, 1.0f };
	m_pRTV->Clear(color);
	m_pDSV->Clear();
}
void DirectX11SetUp::EndDraw()
{
	m_pSwapChain->Present(0, 0);
}

HRESULT DirectX11SetUp::SettingData(const HWND hWnd, const nVec2& Size, const bool fullScreen)
{
	m_hWnd = hWnd;
	m_BufferSize = Size;
	m_thisFullScreen = fullScreen;
	return CheckAllSeting();
}

void DirectX11SetUp::SetHWND(const HWND hWnd)
{
	m_hWnd = hWnd;
	if (m_bCheckIn)
		;
	else
		CheckAllSeting();
}

void DirectX11SetUp::SetBufferSize(const nVec2& Size)
{
	m_BufferSize = Size;
	if (m_bCheckIn)
		;
	else
		CheckAllSeting();
}

void DirectX11SetUp::SetFullScreen(const bool fullScreen)
{
	m_thisFullScreen = fullScreen; if (m_bCheckIn)
		;
	else
		CheckAllSeting();
}

void DirectX11SetUp::SetRenderTargets(UINT num, RenderTarget** ppViews, DepthStencil* pView)
{
	static ID3D11RenderTargetView* rtvs[4];

	if (num > 4) num = 4;
	for (UINT i = 0; i < num; ++i)
		rtvs[i] = ppViews[i]->GetView();
	m_pContext->OMSetRenderTargets(num, rtvs, pView ? pView->GetView() : nullptr);

	// ビューポートの設定
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = (float)ppViews[0]->GetWidth();
	vp.Height = (float)ppViews[0]->GetHeight();
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_pContext->RSSetViewports(1, &vp);
}

void DirectX11SetUp::SetCullingMode(D3D11_CULL_MODE cull)
{
	switch (cull)
	{
	case D3D11_CULL_NONE: m_pContext->RSSetState(m_pRasterizerState[0]); break;
	case D3D11_CULL_FRONT: m_pContext->RSSetState(m_pRasterizerState[1]); break;
	case D3D11_CULL_BACK: m_pContext->RSSetState(m_pRasterizerState[2]); break;
	}
}
void DirectX11SetUp::SetBlendMode(BlendMode blend)
{
	if (blend < 0 || blend >= BLEND_MAX) return;
	FLOAT blendFactor[4] = { D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO };
	m_pContext->OMSetBlendState(m_pBlendState[blend], blendFactor, 0xffffffff);
}
void DirectX11SetUp::SetSamplerState(SamplerState state)
{
	if (state < 0 || state >= SAMPLER_MAX) return;
	m_pContext->PSSetSamplers(0, 1, &m_pSamplerState[state]);
}

ID3D11Device* DirectX11SetUp::GetDevice()
{
	return m_pDevice;
	if (m_bCheckIn)
		;
	else
		CheckAllSeting();
}

ID3D11DeviceContext* DirectX11SetUp::GetContext()
{
	return m_pContext;
}

IDXGISwapChain* DirectX11SetUp::GetSwapChain()
{
	return m_pSwapChain;
}

RenderTarget* DirectX11SetUp::GetDefaultRTV()
{
	return m_pRTV;
}

DepthStencil* DirectX11SetUp::GetDefaultDSV()
{
	return m_pDSV;
}

HRESULT DirectX11SetUp::CheckAllSeting()
{
	if (m_bCheckIn)	//	もうセッティングしてたら処理しない
		return E_ABORT;

	if (!(*(__int64*)m_BufferSize.v) || !m_hWnd)
		return E_INVALIDARG;

	HRESULT	hr = E_FAIL;
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));						// ゼロクリア
	sd.BufferDesc.Width = m_BufferSize.x;						// バックバッファの幅
	sd.BufferDesc.Height = m_BufferSize.y;						// バックバッファの高さ
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// バックバッファフォーマット(R,G,B,A)
	sd.SampleDesc.Count = 1;							// マルチサンプルの数
	sd.BufferDesc.RefreshRate.Numerator = 1000;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// バックバッファの使用方法
	sd.BufferCount = 1;									// バックバッファの数
	sd.OutputWindow = m_hWnd;								// 関連付けるウインドウ
	sd.Windowed = m_thisFullScreen ? FALSE : TRUE;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// ドライバの種類
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,	// GPUで描画
		D3D_DRIVER_TYPE_WARP,		// 高精度(低速
		D3D_DRIVER_TYPE_REFERENCE,	// CPUで描画
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	UINT createDeviceFlags = 0;
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

	// 機能レベル
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,		// DirectX11.1対応GPUレベル
		D3D_FEATURE_LEVEL_11_0,		// DirectX11対応GPUレベル
		D3D_FEATURE_LEVEL_10_1,		// DirectX10.1対応GPUレベル
		D3D_FEATURE_LEVEL_10_0,		// DirectX10対応GPUレベル
		D3D_FEATURE_LEVEL_9_3,		// DirectX9.3対応GPUレベル
		D3D_FEATURE_LEVEL_9_2,		// DirectX9.2対応GPUレベル
		D3D_FEATURE_LEVEL_9_1		// Direct9.1対応GPUレベル
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex)
	{
		driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,					// ディスプレイデバイスのアダプタ（NULLの場合最初に見つかったアダプタ）
			driverType,				// デバイスドライバのタイプ
			NULL,					// ソフトウェアラスタライザを使用する場合に指定する
			createDeviceFlags,		// デバイスフラグ
			featureLevels,			// 機能レベル
			numFeatureLevels,		// 機能レベル数
			D3D11_SDK_VERSION,		// 
			&sd,					// スワップチェインの設定
			&m_pSwapChain,			// IDXGIDwapChainインタフェース	
			&m_pDevice,				// ID3D11Deviceインタフェース
			&featureLevel,		// サポートされている機能レベル
			&m_pContext);		// デバイスコンテキスト
		if (SUCCEEDED(hr)) {
			break;
		}
	}
	if (FAILED(hr)) {
		return hr;
	}

	//--- レンダーターゲット設定
	m_pRTV = New(RenderTarget)();
	if (FAILED(hr = m_pRTV->CreateFromScreen()))
		return hr;
	m_pDSV = New(DepthStencil)();
	if (FAILED(hr = m_pDSV->Create(m_pRTV->GetWidth(), m_pRTV->GetHeight(), false)))
		return hr;
	SetRenderTargets(1, &m_pRTV, nullptr);


	//--- カリング設定
	D3D11_RASTERIZER_DESC rasterizer = {};
	D3D11_CULL_MODE cull[] = {
		D3D11_CULL_NONE,
		D3D11_CULL_FRONT,
		D3D11_CULL_BACK
	};
	rasterizer.FillMode = D3D11_FILL_SOLID;
	rasterizer.FrontCounterClockwise = false;
	for (int i = 0; i < 3; ++i)
	{
		rasterizer.CullMode = cull[i];
		hr = m_pDevice->CreateRasterizerState(&rasterizer, &m_pRasterizerState[i]);
		if (FAILED(hr)) { return hr; }
	}
	SetCullingMode(D3D11_CULL_BACK);

	//--- 深度テスト


	//--- アルファブレンディング
	// https://pgming-ctrl.com/directx11/blend/
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.AlphaToCoverageEnable = TRUE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	D3D11_BLEND blend[BLEND_MAX][2] = {
		{D3D11_BLEND_ONE, D3D11_BLEND_ZERO},
		{D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA},
		{D3D11_BLEND_ONE, D3D11_BLEND_ONE},
		{D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_ONE},
		{D3D11_BLEND_ZERO, D3D11_BLEND_INV_SRC_COLOR},
		{D3D11_BLEND_INV_DEST_COLOR, D3D11_BLEND_ONE},
	};

	for (int i = 0; i < BLEND_MAX; ++i)
	{
		blendDesc.RenderTarget[0].SrcBlend = blend[i][0];
		blendDesc.RenderTarget[0].DestBlend = blend[i][1];
		hr = m_pDevice->CreateBlendState(&blendDesc, &m_pBlendState[i]);
		if (FAILED(hr)) { return hr; }
	}

	SetBlendMode(BLEND_ALPHA);

	// サンプラー
	D3D11_SAMPLER_DESC samplerDesc = {};
	D3D11_FILTER filter[] = {
		D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		D3D11_FILTER_MIN_MAG_MIP_POINT,
	};

	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	for (int i = 0; i < SAMPLER_MAX; ++i)
	{
		samplerDesc.Filter = filter[i];
		hr = m_pDevice->CreateSamplerState(&samplerDesc, &m_pSamplerState[i]);
		if (FAILED(hr)) { return hr; }
	}

	SetSamplerState(SAMPLER_LINEAR);

	m_bCheckIn = true;

	return S_OK;
}

nVec2 DirectX11SetUp::GetBufferSize()
{
	return m_BufferSize;
}