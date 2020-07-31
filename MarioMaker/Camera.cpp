#include "main.h"
#include "RendererManager.h"
#include "GameObject.h"
#include "Camera.h"
#include <cmath>

using namespace std;

D3DXMATRIX Camera::viewMatrix;

void Camera::Init() {
	layer = CAMERA;
}

void Camera::Uninit() {
}

void Camera::Draw() {
	auto position = gameObject->GetPosition().ConvertD3DVECTOR3();
	auto up = D3DXVECTOR3(0, 1, 0);
	
	D3DXVECTOR3 target = D3DXVECTOR3(0, 0, 1.f);

	Vector3 rot = gameObject->GetRotation();

	target = D3DXVECTOR3(0, target.z * sin(rot.GetX()), target.z * cos(rot.GetX()));
	target = D3DXVECTOR3(target.z * -sin(rot.GetY()), target.y, target.z * cos(rot.GetY()));
	target = D3DXVECTOR3(target.x * cos(rot.GetZ()) + target.y * sin(rot.GetZ()), target.x * -sin(rot.GetZ()) + target.y * cos(rot.GetZ()), target.z);


	up = D3DXVECTOR3(0, up.y * cos(rot.GetX()), up.y * -sin(rot.GetX()));
	up = D3DXVECTOR3(up.z * -sin(rot.GetY()), up.y, up.x * sin(rot.GetY()) + up.z * cos(rot.GetY()));
	up = D3DXVECTOR3(up.x * cos(rot.GetZ()) + up.y * sin(rot.GetZ()), up.x * -sin(rot.GetZ()) + up.y * cos(rot.GetZ()), up.z);

	D3DXMatrixLookAtLH(&viewMatrix, &position, &(position + target), &up);

	RendererManager::SetViewMatrix(&viewMatrix);

	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000);

	RendererManager::SetProjectionMatrix(&projectionMatrix);
}

D3DXMATRIX Camera::GetViewMatrix() {
	if (viewMatrix == nullptr) {
		LogWriter::Log("カメラがないのにviewMatrixを取得しようとしました。カメラの設定を確認してください");
		return D3DXMATRIX();
	}
	return viewMatrix;
}

Camera::Camera() {
	Init();
}
