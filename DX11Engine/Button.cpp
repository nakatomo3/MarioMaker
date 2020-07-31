#include "Button.h"

void Button::OnClick() {
	if (gameObject != nullptr) {
		gameObject->OnClick();
	} else {
		LogWriter::Log("GameObjectがアタッチされていないボタンのOnClickが呼ばれました");
	}
}

Button::Button() {
	Init();
}

Button::Button(Texture * tex) {
	textureP = tex;
	texture = textureP->GetTexture();

	Init();
}

void Button::Init() {
	layer = UI;

	scale = Vector2(100, 100);
	position = Vector3(SCREEN_CENTER_X, SCREEN_CENTER_Y);
	tw = 1;
	th = 1;

	//何かあっても分かるように、仮のデータを入れておく

	Vertex vertex[4];

	vertex[0].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].normal = D3DXVECTOR3(0, 0, 0);
	vertex[0].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[0].texUV = D3DXVECTOR2(0, 0);

	vertex[1].position = D3DXVECTOR3(200.0f, 0.0f, 0.0f);
	vertex[1].normal = D3DXVECTOR3(0, 0, 0);
	vertex[1].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[1].texUV = D3DXVECTOR2(1, 0);

	vertex[2].position = D3DXVECTOR3(0.0f, 200.0f, 0.0f);
	vertex[2].normal = D3DXVECTOR3(0, 0, 0);
	vertex[2].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[2].texUV = D3DXVECTOR2(0, 1);

	vertex[3].position = D3DXVECTOR3(200.0f, 200.0f, 0.0f);
	vertex[3].normal = D3DXVECTOR3(0, 0, 0);
	vertex[3].diffuse = D3DXVECTOR4(1, 1, 1, 1);
	vertex[3].texUV = D3DXVECTOR2(1, 1);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	RendererManager::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);
	if (textureP == NULL) {
		textureP = Texture::nullTexture;
		texture = textureP->GetTexture();
	}

}

void Button::Uninit() {
}

void Button::Draw() {
	if (wasChange == true) {
		Vector3 pos = Vector3(0, 0, 0);
		if (gameObject == nullptr) {
			LogWriter::Log("スプライトがGameObjectにアタッチされずに使用されました。GameObjectにアタッチしたうえで使用してください");
			return;
		} else {
			pos = gameObject->GetPosition();
		}

		float positionX = pos.GetX() + position.GetX();
		float positionY = pos.GetY() + position.GetY();
		float positionZ = pos.GetZ() + position.GetZ();

		float left = -scale.GetX() / 2;
		float right = scale.GetX() / 2;

		float up = -scale.GetY() / 2;
		float down = scale.GetY() / 2;

		if (criterion & 1) {
			left = 0;
			right = scale.GetX();
		} else if (criterion & 2) {
			left = -scale.GetX();
			right = 0;
		}

		if (criterion & 4) {
			up = 0;
			down = scale.GetY();
		} else if (criterion & 8) {
			up = -scale.GetY();
			down = 0;
		}

		Vertex vertex[4] = {
			{D3DXVECTOR3(positionX + left , positionY + up  , positionZ), D3DXVECTOR3(0,0,0), color, D3DXVECTOR2(tx     , ty)},
			{D3DXVECTOR3(positionX + right, positionY + up  , positionZ), D3DXVECTOR3(0,0,0), color, D3DXVECTOR2(tx + tw, ty)},
			{D3DXVECTOR3(positionX + left , positionY + down, positionZ), D3DXVECTOR3(0,0,0), color, D3DXVECTOR2(tx     , ty + th)},
			{D3DXVECTOR3(positionX + right, positionY + down, positionZ), D3DXVECTOR3(0,0,0), color, D3DXVECTOR2(tx + tw, ty + th)}
		};

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(Vertex) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = vertex;

		vertexBuffer->Release();
		RendererManager::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);

		//texture->Release();
		//マトリクス設定
		RendererManager::SetWorldViewProjection2D();

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

		wasChange = false;

	} else {

		//マトリクス設定
		RendererManager::SetWorldViewProjection2D();

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

		wasChange = false;

	}
}

void Button::Update() {
	auto cursor = Input::GetCursorPosition();
	auto x = cursor.GetX();
	auto y = cursor.GetY();

	auto pos = gameObject->GetPosition();

	float positionX = pos.GetX() + position.GetX();
	float positionY = pos.GetY() + position.GetY();

	float left = -scale.GetX() / 2;
	float right = scale.GetX() / 2;

	float up = -scale.GetY() / 2;
	float down = scale.GetY() / 2;

	if (criterion & 1) {
		left = 0;
		right = scale.GetX();
	} else if (criterion & 2) {
		left = -scale.GetX();
		right = 0;
	}

	if (criterion & 4) {
		up = 0;
		down = scale.GetY();
	} else if (criterion & 8) {
		up = -scale.GetY();
		down = 0;
	}

	if (x >= left + positionX && x <= positionX + right && y <= positionY + down && positionY + up <= y) {
		if (Input::GetMouse(0)) {
			SetColor(colors[CLICKKING]);
		} else {
			SetColor(colors[MOUSE_OVER]);
		}
		if (Input::GetMouseDown(0)) {
			OnClick();
		}
	} else {
		SetColor(colors[INACTIVE]);
	}

}

void Button::SetTexture(Texture * _texture) {
	if (textureP != _texture) {
		wasChange = true;
	}
	textureP = _texture;
	texture = textureP->GetTexture();
}

void Button::SetScale(Vector2 _scale) {
	if (scale != _scale) {
		wasChange = true;
	}
	scale = _scale;
}

void Button::SetCriterion(Criterion _criterion) {
	if (criterion != _criterion) {
		wasChange = true;
	}
	criterion = _criterion;
}

void Button::SetPosition(Vector3 _position) {
	if (position != _position) {
		wasChange = true;
	}
	position = _position;
}

void Button::SetColor(D3DXVECTOR4 _color) {
	if (color != _color) {
		wasChange = true;
	}
	color = _color;
}

Texture * Button::GetTexture() {
	return textureP;
}

Vector2 Button::GetScale() {
	return scale;
}

Criterion Button::GetCriterion() {
	return criterion;
}

Vector3 Button::GetPosition() {
	return position;
}

void Button::SetTexturePosition(float _tx, float _ty) {
	tx = _tx;
	ty = _ty;
}

void Button::SetTextureScale(float _tw, float _th) {
	tw = _tw;
	th = _th;
}
