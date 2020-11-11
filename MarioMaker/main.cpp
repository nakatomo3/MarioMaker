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
// ウインドウプロシージャ
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

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
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

	// 初期化処理(ウィンドウを作成してから行う)
	LogWriter::Init();
	RendererManager::Init();
	TagManager::Init();

	Time::Init();
	Texture::Init();
	Input::Init(_hWnd);


	//シーンの作成など
	Scene* title = new Title("タイトル");
	SceneManager::LoadScene(title);

	Scene* editScene = new EditScene("編集シーン");
	Scene* selectScene = new SelectStageScene("選択シーン");
	Scene* playScene = new PlayScene("プレイシーン");

	// ウインドウの表示(初期化処理の後に行う)
	ShowWindow(window, cmdShow);
	UpdateWindow(window);
}

void Uninit() {

	RendererManager::End();

	Input::Uninit();
	LogWriter::Log("ログライターが終了しました");
	LogWriter::Uninit();

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
}

void Update() {

	// メッセージループ
	while (1) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {// PostQuitMessage()が呼ばれたらループ終了
				break;
			} else {
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} else {
			if (Time::IsUpdate()) {

				// 更新処理
				Input::Update();
				CollisionManager::Update();
				SceneManager::Update();

				ObjectManager::FirstUpdate();
				ObjectManager::Update();
				ObjectManager::LateUpdate();

				// 描画処理
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
