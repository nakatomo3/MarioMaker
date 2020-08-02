#include "Cube.h"
#include "GameObject.h"

void Cube::Init() {
	th = 1;
	tw = 1;

	Vertex vertex[18];
	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA sd;

	vertex[0].position = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
	vertex[0].normal = D3DXVECTOR3(0, 0, 0);
	vertex[0].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[0].texUV = D3DXVECTOR2(0, 1);

	vertex[1].position = D3DXVECTOR3(-0.5f, 0.5f, -0.5f);
	vertex[1].normal = D3DXVECTOR3(0, 0, 0);
	vertex[1].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[1].texUV = D3DXVECTOR2(0, 0);

	vertex[2].position = D3DXVECTOR3(0.5f, -0.5f, -0.5f);
	vertex[2].normal = D3DXVECTOR3(0, 0, 0);
	vertex[2].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[2].texUV = D3DXVECTOR2(1, 1);

	vertex[3].position = D3DXVECTOR3(0.5f, 0.5f, -0.5f);
	vertex[3].normal = D3DXVECTOR3(0, 0, 0);
	vertex[3].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[3].texUV = D3DXVECTOR2(1, 0);

	vertex[4].position = D3DXVECTOR3(0.5f, -0.5f, 0.5f);
	vertex[4].normal = D3DXVECTOR3(0, 0, 0);
	vertex[4].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[4].texUV = D3DXVECTOR2(0, 1);

	vertex[5].position = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
	vertex[5].normal = D3DXVECTOR3(0, 0, 0);
	vertex[5].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[5].texUV = D3DXVECTOR2(0, 0);

	vertex[6].position = D3DXVECTOR3(-0.5f, -0.5f, 0.5f);
	vertex[6].normal = D3DXVECTOR3(0, 0, 0);
	vertex[6].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[6].texUV = D3DXVECTOR2(1, 1);

	vertex[7].position = D3DXVECTOR3(-0.5f, 0.5f, 0.5f);
	vertex[7].normal = D3DXVECTOR3(0, 0, 0);
	vertex[7].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[7].texUV = D3DXVECTOR2(1, 0);

	vertex[8].position = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
	vertex[8].normal = D3DXVECTOR3(0, 0, 0);
	vertex[8].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[8].texUV = D3DXVECTOR2(0, 1);

	vertex[9].position = D3DXVECTOR3(-0.5f, 0.5f, -0.5f);
	vertex[9].normal = D3DXVECTOR3(0, 0, 0);
	vertex[9].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[9].texUV = D3DXVECTOR2(0, 0);

	vertex[10].position = D3DXVECTOR3(-0.5f, 0.5f, 0.5f);
	vertex[10].normal = D3DXVECTOR3(0, 0, 0);
	vertex[10].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[10].texUV = D3DXVECTOR2(1, 0);

	vertex[11].position = D3DXVECTOR3(0.5f, 0.5f, -0.5f);
	vertex[11].normal = D3DXVECTOR3(0, 0, 0);
	vertex[11].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[11].texUV = D3DXVECTOR2(0, 1);

	vertex[12].position = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
	vertex[12].normal = D3DXVECTOR3(0, 0, 0);
	vertex[12].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[12].texUV = D3DXVECTOR2(1, 1);

	//縮退
	vertex[13].position = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
	vertex[13].normal = D3DXVECTOR3(0, 0, 0);
	vertex[13].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[13].texUV = D3DXVECTOR2(1, 1);
	vertex[14].position = D3DXVECTOR3(0.5f, -0.5f, -0.5f);
	vertex[14].normal = D3DXVECTOR3(0, 0, 0);
	vertex[14].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[14].texUV = D3DXVECTOR2(1, 1);

	vertex[15].position = D3DXVECTOR3(0.5f, -0.5f, -0.5f);
	vertex[15].normal = D3DXVECTOR3(0, 0, 0);
	vertex[15].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[15].texUV = D3DXVECTOR2(0, 0);

	vertex[16].position = D3DXVECTOR3(0.5f, -0.5f, 0.5f);
	vertex[16].normal = D3DXVECTOR3(0, 0, 0);
	vertex[16].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[16].texUV = D3DXVECTOR2(1, 0);

	vertex[17].position = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
	vertex[17].normal = D3DXVECTOR3(0, 0, 0);
	vertex[17].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[17].texUV = D3DXVECTOR2(0, 1);

	vertex[18].position = D3DXVECTOR3(-0.5f, -0.5f, 0.5f);
	vertex[18].normal = D3DXVECTOR3(0, 0, 0);
	vertex[18].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[18].texUV = D3DXVECTOR2(1, 1);

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * 18;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	RendererManager::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);
	if (texture == nullptr) {
		textureP = Texture::nullTexture;
		texture = textureP->GetTexture();
	}
}

void Cube::OnDestroy() {
	vertexBuffer->Release();
}

void Cube::Draw() {

	RendererManager::SetCullMode(D3D11_CULL_NONE);
	Vector3 pos = Vector3(0, 0, 0);
	if (gameObject == nullptr) {
		LogWriter::Log("スプライトがGameObjectにアタッチされずに使用されました。GameObjectにアタッチしたうえで使用してください");
		return;
	} else {
		pos = gameObject->GetPosition() - gameObject->GetLocalPosition();
	}

	D3DXMATRIX world, mScale, mRot, mTrans, localPos;

	//マトリクス設定
	D3DXMatrixScaling(&mScale, gameObject->GetScale().GetX() * scale.GetX(), gameObject->GetScale().GetY() * scale.GetY(), gameObject->GetScale().GetZ());
	D3DXMatrixRotationYawPitchRoll(&mRot, gameObject->GetRotation().GetY(), gameObject->GetRotation().GetX(), gameObject->GetRotation().GetZ());
	D3DXMatrixTranslation(&mTrans, pos.GetX(), pos.GetY(), pos.GetZ());
	D3DXMatrixTranslation(&localPos, gameObject->GetLocalPosition().GetX(), gameObject->GetLocalPosition().GetY(), gameObject->GetLocalPosition().GetZ());
	world = localPos * mScale * mRot * mTrans;
	RendererManager::SetWorldMatrix(&world);

	//頂点バッファ設定
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	RendererManager::GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	//テクスチャ設定
	RendererManager::GetDeviceContext()->PSSetShaderResources(0, 1, &texture);

	//プリミティブトポロジ設定
	RendererManager::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	RendererManager::GetDeviceContext()->Draw(18, 0);
	RendererManager::SetCullMode(D3D11_CULL_BACK);
}

void Cube::SetTexture(Texture * _texture) {
	textureP = _texture;
	texture = textureP->GetTexture();
}

void Cube::SetScale(Vector2 _scale) {
}

void Cube::SetCriterion(Criterion _criterion) {
}

void Cube::SetPosition(Vector3 _position) {
}

void Cube::SetColor(D3DXVECTOR4 _color) {
}

Texture * Cube::GetTexture() {
	return nullptr;
}

Vector2 Cube::GetScale() {
	return Vector2();
}

Criterion Cube::GetCriterion() {
	return Criterion();
}

Vector3 Cube::GetPosition() {
	return Vector3();
}

void Cube::SetTexturePosition(float _tx, float _ty) {
}

void Cube::SetTextureScale(float _tw, float _th) {
}

Cube::Cube() {
	Init();
}
