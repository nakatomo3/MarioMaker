#include "main.h"
#include "Field.h"
#include "renderer.h"

void Field::Init() {
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
	vertex[0].Normal = D3DXVECTOR3(0, 0, 0);
	vertex[0].Diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[0].TexCoord = D3DXVECTOR2(0, 0);

	vertex[1].Position = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
	vertex[1].Normal = D3DXVECTOR3(0, 0, 0);
	vertex[1].Diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[1].TexCoord = D3DXVECTOR2(1, 0);

	vertex[2].Position = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
	vertex[2].Normal = D3DXVECTOR3(0, 0, 0);
	vertex[2].Diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[2].TexCoord = D3DXVECTOR2(0, 1);

	vertex[3].Position = D3DXVECTOR3(10.0f, 0.0f, -10.0f);
	vertex[3].Normal = D3DXVECTOR3(0, 0, 0);
	vertex[3].Diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[3].TexCoord = D3DXVECTOR2(1, 1);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);

	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(), "assets/textures/number.png", NULL, NULL, &texture, NULL);

	position = D3DXVECTOR3(0, 0, 0);
	rotation = D3DXVECTOR3(0, 0, 0);
	scale = D3DXVECTOR3(1, 1, 1);

}

void Field::Uninit() {
	vertexBuffer->Release();
	texture->Release();
}

void Field::Update() {
}

void Field::Draw() {
	//マトリクス設定
	D3DXMATRIX world, mScale, mRot, mTrans;
	D3DXMatrixScaling(&mScale, scale.x, scale.y, scale.z);
	D3DXMatrixRotationYawPitchRoll(&mRot, rotation.y, rotation.x, rotation.z);
	D3DXMatrixTranslation(&mTrans, position.z, position.y, position.z);
	world = mScale * mRot * mTrans;
	CRenderer::SetWorldMatrix(&world);

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	//テクスチャ設定
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &texture);

	//プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);
}
