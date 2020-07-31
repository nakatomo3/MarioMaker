#pragma once
#include "VisualComponent.h"
class Camera : public VisualComponent {
public:

	void Init();
	void Uninit();

	void Draw();

	static D3DXMATRIX GetViewMatrix();

	Camera();

private:
	static D3DXMATRIX viewMatrix;
};