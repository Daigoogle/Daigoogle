#ifndef _____DIRECT_X_11_SET_UP_H_____
#define _____DIRECT_X_11_SET_UP_H_____

//	----------インクルード部----------
#include <d3d11.h>
#include "SingletonsMng.hxx"
#include "Vectors.hxx"
#include "Texture.h"

#pragma comment(lib, "d3d11.lib")

#define SAFE_DELETE(p) do{if(p){delete p; p = nullptr;}}while(0)
#define SAFE_DELETE_ARRAY(p) do{if(p){delete[] p; p = nullptr;}}while(0)
#define SAFE_RELEASE(p) do{if(p){p->Release(); p = nullptr;}}while(0)

enum BlendMode
{
	BLEND_NONE,
	BLEND_ALPHA,
	BLEND_ADD,
	BLEND_ADDALPHA,
	BLEND_SUB,
	BLEND_SCREEN,
	BLEND_MAX
};
enum SamplerState
{
	SAMPLER_LINEAR,
	SAMPLER_POINT,
	SAMPLER_MAX
};
class RenderTarget;
class DepthStencil;

class DirectX11SetUp final: public Singleton<DirectX11SetUp>
{
	friend class Singleton<DirectX11SetUp>;
public:
	//	=-= 規定処理 =-=
	bool Init();
	void BeginDraw();
	void EndDraw();

	//  =-= Set =-=
	HRESULT SettingData(const HWND hWnd,const nVec2& Size,const bool fullScreen);
	void SetHWND(const HWND hWnd);
	void SetBufferSize(const nVec2& Size);
	void SetFullScreen(const bool fullScreen);
	void SetRenderTargets(UINT num, RenderTarget** ppViews, DepthStencil* pView);
	void SetCullingMode(D3D11_CULL_MODE cull);
	void SetBlendMode(BlendMode blend);
	void SetSamplerState(SamplerState state);

	//	=-= Get =-= 
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();
	IDXGISwapChain* GetSwapChain();
	RenderTarget* GetDefaultRTV();
	DepthStencil* GetDefaultDSV();
	nVec2 GetBufferSize();

private:
	DirectX11SetUp();
	~DirectX11SetUp();

	HRESULT CheckAllSeting();
	bool m_bCheckIn;

	//	=-= Setting Status =-=
	nVec2 m_BufferSize;
	HWND m_hWnd;
	bool m_thisFullScreen;

	//	=-= DirectX Status =-=
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pContext;
	IDXGISwapChain* m_pSwapChain;
	RenderTarget* m_pRTV;
	DepthStencil* m_pDSV;
	ID3D11RasterizerState* m_pRasterizerState[3];
	ID3D11BlendState* m_pBlendState[BLEND_MAX];
	ID3D11SamplerState* m_pSamplerState[SAMPLER_MAX];
};

#endif // !_____DIRECT_X_11_SET_UP_H_____