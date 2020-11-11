#include "main.h"
#include "DXEngine.h"

#include "Title.h"
#include "EditScene.h"
#include "SelectStageScene.h"
#include "PlayScene.h"

#include <crtdbg.h>

#include <string>
using namespace std;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wparam, LPARAM lparam);

void Init(HINSTANCE hInstance, int nCmdShow);
void Uninit();
void Update();

HWND window;
WNDCLASSEX wcex;
MSG msg;

HWND _hWnd;

HWND GetWindow() {
	return window;
}


int APIENTRY WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR lpCmdLine, int cmdShow) {
	
	Init(instance, cmdShow);

	Update();
	
	Uninit();

	return (int)msg.wParam;
}


//=============================================================================
// �E�C���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam) {

	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wparam) {
		case VK_ESCAPE:
			if (MessageBox(hWnd, END_MESSAGE, END_WINDOW_CAPTION, MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	case WM_MOUSEWHEEL:
		Input::SetMouseWheel(GET_WHEEL_DELTA_WPARAM(wparam));
	default:
		break;
	}

	_hWnd = hWnd;

	return DefWindowProc(hWnd, message, wparam, lparam);
}

void Init(HINSTANCE instance, int cmdShow) {
	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		instance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	window = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
		(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
		NULL,
		NULL,
		instance,
		NULL);

	_ASSERT(_CrtCheckMemory());

	// ����������(�E�B���h�E���쐬���Ă���s��)
	LogWriter::Init();
	RendererManager::Init();
	TagManager::Init();

	Time::Init();
	Texture::Init();
	Input::Init(_hWnd);


	//�V�[���̍쐬�Ȃ�
	Scene* title = new Title("�^�C�g��");
	SceneManager::LoadScene(title);

	Scene* editScene = new EditScene("�ҏW�V�[��");
	Scene* selectScene = new SelectStageScene("�I���V�[��");
	Scene* playScene = new PlayScene("�v���C�V�[��");

	// �E�C���h�E�̕\��(�����������̌�ɍs��)
	ShowWindow(window, cmdShow);
	UpdateWindow(window);
}

void Uninit() {

	RendererManager::End();

	Input::Uninit();
	LogWriter::Log("���O���C�^�[���I�����܂���");
	LogWriter::Uninit();

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
}

void Update() {

	// ���b�Z�[�W���[�v
	while (1) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			} else {
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} else {
			if (Time::IsUpdate()) {

				// �X�V����
				Input::Update();
				CollisionManager::Update();
				SceneManager::Update();

				ObjectManager::FirstUpdate();
				ObjectManager::Update();
				ObjectManager::LateUpdate();

				// �`�揈��
				RendererManager::Begin();
				ObjectManager::Draw();
				RendererManager::End();
				Input::SetMouseWheel(0);

				ObjectManager::Destroy();
				ObjectManager::Load();

				_ASSERT(_CrtCheckMemory());
			}
		}
	}
}
