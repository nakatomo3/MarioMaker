#pragma once
#include "main.h"

// 頂点構造体
struct Vertex {
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR4 diffuse;
	D3DXVECTOR2 texUV;
};



// マテリアル構造体
struct Material {
	D3DXCOLOR	ambient;
	D3DXCOLOR	diffuse;
	D3DXCOLOR	specular;
	D3DXCOLOR	emission;
	float		shininess;
	float		dummy[3];//16byte境界用
};

struct Light {
	BOOL		enable;
	BOOL		dummy[3];//16byte境界用
	D3DXVECTOR4	direction;
	D3DXCOLOR	diffuse;
	D3DXCOLOR	ambient;
};


class CVertexBuffer;
class CIndexBuffer;
class CTexture;


class RendererManager {
private:

	static D3D_FEATURE_LEVEL       featureLevel;

	static ID3D11Device*           D3DDevice;
	static ID3D11DeviceContext*    immediateContext;
	static IDXGISwapChain*         swapChain;
	static ID3D11RenderTargetView* renderTargetView;
	static ID3D11DepthStencilView* depthStencilView;



	static ID3D11VertexShader*     vertexShader;
	static ID3D11PixelShader*      pixelShader;
	static ID3D11InputLayout*      vertexLayout;
	static ID3D11Buffer*			worldBuffer;
	static ID3D11Buffer*			viewBuffer;
	static ID3D11Buffer*			projectionBuffer;
	static ID3D11Buffer*			materialBuffer;
	static ID3D11Buffer*			lightBuffer;


	static ID3D11DepthStencilState* depthStateEnable;
	static ID3D11DepthStencilState* depthStateDisable;

	static ID3D11SamplerState* samplerState;

	static D3D11_RASTERIZER_DESC rd;


public:
	static void Init();
	static void Uninit();
	static void Begin();
	static void End();

	static void SetDepthEnable(bool Enable);
	//2D変換関数
	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(D3DXMATRIX * WorldMatrix);
	static void SetViewMatrix(D3DXMATRIX * ViewMatrix);
	static void SetProjectionMatrix(D3DXMATRIX * ProjectionMatrix);
	static void SetMaterial(Material Material);
	static void SetLight(Light Light);

	static ID3D11Device* GetDevice(void) {
		return D3DDevice; 
	}
	static ID3D11DeviceContext* GetDeviceContext(void) {
		return immediateContext; 
	}

	static ID3D11SamplerState** GetSampler() {
		return &samplerState;
	}

	static void SetFillMode(D3D11_FILL_MODE mode);
	static void SetCullMode(D3D11_CULL_MODE mode);

};
