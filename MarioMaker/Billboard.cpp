#include "Billboard.h"
#include "GameObject.h"
#include "Camera.h"

void Billboard::Draw() {
	Vector3 pos = Vector3(0, 0, 0);
	if (gameObject == nullptr) {
		LogWriter::Log("スプライトがGameObjectにアタッチされずに使用されました。GameObjectにアタッチしたうえで使用してください");
		return;
	} else {
		pos = gameObject->GetPosition();
	}

	D3DXMATRIX world, mScale, mRot, mTrans;

	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &Camera::GetViewMatrix());
	invView._41 = 0;
	invView._42 = 0;
	invView._43 = 0;

	//マトリクス設定
	D3DXMatrixScaling(&mScale, gameObject->GetScale().GetX() * scale.GetX(), gameObject->GetScale().GetY() * scale.GetY(), gameObject->GetScale().GetZ());
	D3DXMatrixRotationYawPitchRoll(&mRot, gameObject->GetRotation().GetY(), gameObject->GetRotation().GetX(), gameObject->GetRotation().GetZ());
	D3DXMatrixTranslation(&mTrans, gameObject->GetPosition().GetX(), gameObject->GetPosition().GetY(), gameObject->GetPosition().GetZ());
	world = mScale * invView * mTrans;
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
	RendererManager::GetDeviceContext()->Draw(4, 0);
}