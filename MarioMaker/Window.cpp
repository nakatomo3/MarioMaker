#include "Window.h"
#include "input.h"
#include "Setting.h"
#include "Time.h"

Window::Window() {
	Init();
}

void Window::Init() {
	layer = UI;

	//gameObject->SetPosition(Vector3(SCREEN_CENTER_X, SCREEN_CENTER_Y));

	texture = textureP->GetTexture();

	Vertex vertex[4];
	ZeroMemory(vertex, sizeof(Vertex) * 4);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	RendererManager::GetDevice()->CreateBuffer(&bd, &sd, &barVertexBuffer);
}

void Window::Draw() {
	if (wasChange == true) {
		Vector3 pos = Vector3(0, 0, 0);
		if (gameObject == nullptr) {
			LogWriter::Log("スプライトがGameObjectにアタッチされずに使用されました。GameObjectにアタッチしたうえで使用してください");
			return;
		} else {
			pos = gameObject->GetPosition();
		}

		float positionX = pos.GetX();
		float positionY = pos.GetY();
		float positionZ = pos.GetZ();

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
			{D3DXVECTOR3(positionX + left , positionY + up  , positionZ), D3DXVECTOR3(0,0,0), color, D3DXVECTOR2(0, 0)},
			{D3DXVECTOR3(positionX + right, positionY + up  , positionZ), D3DXVECTOR3(0,0,0), color, D3DXVECTOR2(1, 0)},
			{D3DXVECTOR3(positionX + left , positionY + down, positionZ), D3DXVECTOR3(0,0,0), color, D3DXVECTOR2(0, 1)},
			{D3DXVECTOR3(positionX + right, positionY + down, positionZ), D3DXVECTOR3(0,0,0), color, D3DXVECTOR2(1, 1)}
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

		barVertexBuffer->Release();
		RendererManager::GetDevice()->CreateBuffer(&bd, &sd, &barVertexBuffer);

		//texture->Release();
		//マトリクス設定
		RendererManager::SetWorldViewProjection2D();

		//頂点バッファ設定
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		RendererManager::GetDeviceContext()->IASetVertexBuffers(0, 1, &barVertexBuffer, &stride, &offset);

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
		RendererManager::GetDeviceContext()->IASetVertexBuffers(0, 1, &barVertexBuffer, &stride, &offset);

		//テクスチャ設定
		RendererManager::GetDeviceContext()->PSSetShaderResources(0, 1, &texture);

		//プリミティブトポロジ設定
		RendererManager::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		//ポリゴン描画
		RendererManager::GetDeviceContext()->Draw(4, 0);

		wasChange = false;

	}
}

void Window::Update() {
	auto cursor = Input::GetCursorPosition();
	auto x = cursor.GetX();
	auto y = cursor.GetY();

	auto pos = gameObject->GetPosition();

	float positionX = pos.GetX();
	float positionY = pos.GetY();

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
		if (Input::GetMouseDown(0)) {
			cursorPositionAtClick = Vector2(Input::GetCursorPosition().GetX(), Input::GetCursorPosition().GetY());
			windowPositionAtClick = gameObject->GetPosition();
			isDragging = true;
		}
		if (Input::GetMouseDown(0)) {
			if (clickTimer <= doubleClickInterval) {
				for (unsigned int i = 0; i < gameObject->GetChildCount(); i++) {
					gameObject->GetChild(i)->SetActive(!gameObject->GetChild(i)->GetActive());
				}
			}
			clickTimer = 0;
		}
	}
	clickTimer += (float)Time::GetDeltaTime();
	if (isDragging == true && Input::GetMouse(0)) {
		gameObject->SetPosition(windowPositionAtClick - Vector3(cursorPositionAtClick.GetX() - Input::GetCursorPosition().GetX(), cursorPositionAtClick.GetY() - Input::GetCursorPosition().GetY(), 0));
		wasChange = true;
		if (gameObject->GetPosition().GetX() >= SCREEN_WIDTH) {
			gameObject->SetPosition(Vector3(SCREEN_WIDTH, gameObject->GetPosition().GetY()));
		}
		if (gameObject->GetPosition().GetX() <= 0) {
			gameObject->SetPosition(Vector3(0, gameObject->GetPosition().GetY()));
		}
		if (gameObject->GetPosition().GetY() >= SCREEN_HEIGHT) {
			gameObject->SetPosition(Vector3(gameObject->GetPosition().GetX(), SCREEN_HEIGHT));
		}
		if (gameObject->GetPosition().GetY() <= 0) {
			gameObject->SetPosition(Vector3(gameObject->GetPosition().GetX(), 0));
		}
	}
	if (isDragging == true && Input::GetMouseUp(0)) {
		isDragging = false;
	}
}
