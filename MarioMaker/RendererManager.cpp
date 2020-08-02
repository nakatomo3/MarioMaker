
#include "main.h"
#include "RendererManager.h"
#include <io.h>


D3D_FEATURE_LEVEL       RendererManager::featureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device*           RendererManager::D3DDevice = NULL;
ID3D11DeviceContext*    RendererManager::immediateContext = NULL;
IDXGISwapChain*         RendererManager::swapChain = NULL;
ID3D11RenderTargetView* RendererManager::renderTargetView = NULL;
ID3D11DepthStencilView* RendererManager::depthStencilView = NULL;



ID3D11VertexShader*     RendererManager::vertexShader = NULL;
ID3D11PixelShader*      RendererManager::pixelShader = NULL;
ID3D11InputLayout*      RendererManager::vertexLayout = NULL;
ID3D11Buffer*			RendererManager::worldBuffer = NULL;
ID3D11Buffer*			RendererManager::viewBuffer = NULL;
ID3D11Buffer*			RendererManager::projectionBuffer = NULL;
ID3D11Buffer*			RendererManager::materialBuffer = NULL;
ID3D11Buffer*			RendererManager::lightBuffer = NULL;


ID3D11DepthStencilState* RendererManager::depthStateEnable = NULL;
ID3D11DepthStencilState* RendererManager::depthStateDisable = NULL;

ID3D11SamplerState* RendererManager::samplerState;

D3D11_RASTERIZER_DESC RendererManager::rd;


void RendererManager::Init() {
	HRESULT hr = S_OK;

	// デバイス、スワップチェーン、コンテキスト生成
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = SCREEN_WIDTH;
	sd.BufferDesc.Height = SCREEN_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = GetWindow();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&swapChain,
		&D3DDevice,
		&featureLevel,
		&immediateContext);


	// レンダーターゲットビュー生成、設定
	ID3D11Texture2D* pBackBuffer = NULL;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	D3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &renderTargetView);
	pBackBuffer->Release();



	//深度ステンシル用テクスチャー作成
	ID3D11Texture2D* depthTexture = NULL;
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(td));
	td.Width = sd.BufferDesc.Width;
	td.Height = sd.BufferDesc.Height;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc = sd.SampleDesc;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;
	D3DDevice->CreateTexture2D(&td, NULL, &depthTexture);

	//深度ステンシルターゲット作成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = td.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Flags = 0;
	D3DDevice->CreateDepthStencilView(depthTexture, &dsvd, &depthStencilView);


	immediateContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);


	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)SCREEN_WIDTH;		//画面の表示範囲(拡大率)
	vp.Height = (FLOAT)SCREEN_HEIGHT;	//縦幅
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;					//左上の座標X
	vp.TopLeftY = 0;					//右上の座標Y
	immediateContext->RSSetViewports(1, &vp);

	UINT count = 1;
	D3D11_RECT rect;	//画面の表示範囲(切り抜き)
	rect.left = static_cast<LONG>(0);
	rect.right = static_cast<LONG>(SCREEN_WIDTH);
	rect.top = static_cast<LONG>(0);
	rect.bottom = static_cast<LONG>(SCREEN_HEIGHT);
	immediateContext->RSSetScissorRects(count, &rect);

	// ラスタライザステート設定
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;	//ワイヤーフレームにしたいときはD3D11_FILL_WIREFRAMEにする
	rd.CullMode = D3D11_CULL_BACK;	//裏面を描画しない、CULL_NONEで両面、_FRONTで表面を描画しない
	rd.DepthClipEnable = TRUE;		//時計回りでポリゴンにする
	rd.MultisampleEnable = FALSE;
	rd.ScissorEnable = TRUE;

	ID3D11RasterizerState *rs;
	D3DDevice->CreateRasterizerState(&rd, &rs);

	immediateContext->RSSetState(rs);




	// ブレンドステート設定
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.AlphaToCoverageEnable = TRUE;		//描画の前後に関係なく透過処理してくれるやつ
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	ID3D11BlendState* blendState = NULL;
	D3DDevice->CreateBlendState(&blendDesc, &blendState);
	immediateContext->OMSetBlendState(blendState, blendFactor, 0xffffffff);



	// 深度ステンシルステート設定
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;

	D3DDevice->CreateDepthStencilState(&depthStencilDesc, &depthStateEnable);//深度有効ステート

	//depthStencilDesc.DepthEnable = FALSE;
	//depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	//D3DDevice->CreateDepthStencilState(&depthStencilDesc, &depthStateDisable);//深度無効ステート

	immediateContext->OMSetDepthStencilState(depthStateEnable, NULL);




	// サンプラーステート設定
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;//D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	samplerState = NULL;
	D3DDevice->CreateSamplerState(&samplerDesc, &samplerState);

	immediateContext->PSSetSamplers(0, 1, &samplerState);




	// 頂点シェーダ生成
	{
		FILE* file;
		long int fsize;

		file = fopen("vertexShader.cso", "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		D3DDevice->CreateVertexShader(buffer, fsize, NULL, &vertexShader);


		// 入力レイアウト生成
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		UINT numElements = ARRAYSIZE(layout);

		D3DDevice->CreateInputLayout(layout,
			numElements,
			buffer,
			fsize,
			&vertexLayout);

		delete[] buffer;
	}



	// ピクセルシェーダ生成
	{
		FILE* file;
		long int fsize;

		file = fopen("pixelShader.cso", "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		D3DDevice->CreatePixelShader(buffer, fsize, NULL, &pixelShader);

		delete[] buffer;
	}




	// 定数バッファ生成
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	D3DDevice->CreateBuffer(&hBufferDesc, NULL, &worldBuffer);
	immediateContext->VSSetConstantBuffers(0, 1, &worldBuffer);

	D3DDevice->CreateBuffer(&hBufferDesc, NULL, &viewBuffer);
	immediateContext->VSSetConstantBuffers(1, 1, &viewBuffer);

	D3DDevice->CreateBuffer(&hBufferDesc, NULL, &projectionBuffer);
	immediateContext->VSSetConstantBuffers(2, 1, &projectionBuffer);


	hBufferDesc.ByteWidth = sizeof(Material);

	D3DDevice->CreateBuffer(&hBufferDesc, NULL, &materialBuffer);
	immediateContext->VSSetConstantBuffers(3, 1, &materialBuffer);


	hBufferDesc.ByteWidth = sizeof(Light);

	D3DDevice->CreateBuffer(&hBufferDesc, NULL, &lightBuffer);
	immediateContext->VSSetConstantBuffers(4, 1, &lightBuffer);





	// 入力レイアウト設定
	immediateContext->IASetInputLayout(vertexLayout);

	// シェーダ設定
	immediateContext->VSSetShader(vertexShader, NULL, 0);
	immediateContext->PSSetShader(pixelShader, NULL, 0);



	// ライト無効化
	Light light;
	light.enable = false;
	SetLight(light);



	// マテリアル初期化
	Material material;
	ZeroMemory(&material, sizeof(material));
	material.diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);




}



void RendererManager::Uninit() {
	// オブジェクト解放
	worldBuffer->Release();
	viewBuffer->Release();
	projectionBuffer->Release();
	lightBuffer->Release();
	materialBuffer->Release();

	vertexLayout->Release();
	vertexShader->Release();
	pixelShader->Release();

	immediateContext->ClearState();
	renderTargetView->Release();
	swapChain->Release();
	immediateContext->Release();
	D3DDevice->Release();

}



void RendererManager::Begin() {
	// バックバッファクリア
	float ClearColor[4] = { 0.5f, 0.9f, 0.5f, 1.0f };
	immediateContext->ClearRenderTargetView(renderTargetView, ClearColor);
	immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

}



void RendererManager::End() {
	swapChain->Present(1, 0);
}




void RendererManager::SetDepthEnable(bool Enable) {
	if (Enable) {
		immediateContext->OMSetDepthStencilState(depthStateEnable, NULL);
	} else {
		immediateContext->OMSetDepthStencilState(depthStateDisable, NULL);
	}
}

void RendererManager::SetWorldViewProjection2D() {
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	D3DXMatrixTranspose(&world, &world);

	immediateContext->UpdateSubresource(worldBuffer, 0, NULL, &world, 0, 0);

	D3DXMATRIX view;
	D3DXMatrixIdentity(&view);
	D3DXMatrixTranspose(&view, &view);
	immediateContext->UpdateSubresource(viewBuffer, 0, NULL, &view, 0, 0);

	D3DXMATRIX projection;
	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 10.0f);
	D3DXMatrixTranspose(&projection, &projection);
	immediateContext->UpdateSubresource(projectionBuffer, 0, NULL, &projection, 0, 0);

}


void RendererManager::SetWorldMatrix(D3DXMATRIX *WorldMatrix) {
	D3DXMATRIX world;
	D3DXMatrixTranspose(&world, WorldMatrix);
	immediateContext->UpdateSubresource(worldBuffer, 0, NULL, &world, 0, 0);
}

void RendererManager::SetViewMatrix(D3DXMATRIX *ViewMatrix) {
	D3DXMATRIX view;
	D3DXMatrixTranspose(&view, ViewMatrix);
	immediateContext->UpdateSubresource(viewBuffer, 0, NULL, &view, 0, 0);
}

void RendererManager::SetProjectionMatrix(D3DXMATRIX *ProjectionMatrix) {
	D3DXMATRIX projection;
	D3DXMatrixTranspose(&projection, ProjectionMatrix);
	immediateContext->UpdateSubresource(projectionBuffer, 0, NULL, &projection, 0, 0);
}



void RendererManager::SetMaterial(Material Material) {

	immediateContext->UpdateSubresource(materialBuffer, 0, NULL, &Material, 0, 0);

}

void RendererManager::SetLight(Light Light) {

	immediateContext->UpdateSubresource(lightBuffer, 0, NULL, &Light, 0, 0);

}

void RendererManager::SetFillMode(D3D11_FILL_MODE mode) {
	rd.FillMode = mode;	//ワイヤーフレームにしたいときはD3D11_FILL_WIREFRAMEにする

	ID3D11RasterizerState *rs;
	D3DDevice->CreateRasterizerState(&rd, &rs);

	immediateContext->RSSetState(rs);
}

void RendererManager::SetCullMode(D3D11_CULL_MODE mode) {
	rd.CullMode = mode;	//裏面を描画しない、CULL_NONEで両面、_FRONTで表面を描画しない

	ID3D11RasterizerState *rs;
	D3DDevice->CreateRasterizerState(&rd, &rs);

	immediateContext->RSSetState(rs);
}
