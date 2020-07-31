#include "main.h"
#include "DXEngine.h"

#include "Player.h"

#include <string>
using namespace std;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wparam, LPARAM lparam);

void Init(HINSTANCE hInstance, int nCmdShow);
void Uninit();
void Update();

HWND window;
WNDCLASSEX wcex;
MSG msg;

GameObject* player;
GameObject* camera;
GameObject* ui;
NumText* fps;

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


	// 初期化処理(ウィンドウを作成してから行う)
	LogWriter::Init();
	RendererManager::Init();
	TagManager::Init();

	Time::Init();
	Texture::Init();
	Input::Init(_hWnd);


	//シーンの作成など
	Scene* scene = new Scene("hoge");
	//SceneManager::LoadScene("hoge");

	camera = new GameObject("カメラ");
	camera->AddComponent<Camera>();
	ObjectManager::Instantiate(camera);
	camera->SetPosition(Vector3(0, 2, 0));
	
	ui = new GameObject("window");
	Texture* tex = new Texture("assets/textures/number.png");
	auto windowComponent = ui->AddComponent<Window>();
	ObjectManager::Instantiate(ui);
	ui->SetPosition(Vector3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0));
	auto text = ui->AddComponent<Text>();
	text->SetText("デバッグ情報");
	text->SetFontSize(18);
	text->SetColor(D3DXVECTOR4(1, 1, 1, 1));
	text->SetPosition(Vector3(-90, -9));

	
	/*image->SetTexture(tex);
	image->SetPosition(Vector3(SCREEN_WIDTH - image->GetScale().GetX() / 2, image->GetScale().GetY() / 2, 0));
	*/
	auto imageObj = new GameObject("WindowContent");
	auto image = imageObj->AddComponent<Image>();
	image->SetPosition(Vector3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 60, 1));
	image->SetScale(Vector2(200,120));
	image->SetColor(D3DXVECTOR4(1, 1, 1, 0.501f));
	imageObj->SetParent(ui);
	auto fpsLabel = imageObj->AddComponent<Text>();
	fpsLabel->SetText("FPS:");
	fpsLabel->SetPosition(Vector3(SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 + 20, 0));
	fpsLabel->SetColor(D3DXVECTOR4(0, 0, 0, 1));
	fpsLabel->SetFontSize(20);
	fps = imageObj->AddComponent<NumText>();
	fps->SetFontSize(20);
	fps->SetPosition(Vector3(SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 + 20, 0));
	fps->SetColor(D3DXVECTOR4(0, 0, 0, 1));
	auto screenSize = imageObj->AddComponent<Text>();
	screenSize->SetText("ScreenSize:");
	screenSize->SetColor(D3DXVECTOR4(0, 0, 0, 1));
	screenSize->SetFontSize(20);
	screenSize->SetPosition(Vector3(SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 + 50, 0));
	auto screenSizeX = imageObj->AddComponent<NumText>();
	screenSizeX->SetText(SCREEN_WIDTH);
	screenSizeX->SetColor(D3DXVECTOR4(0, 0, 0, 1));
	screenSizeX->SetFontSize(20);
	screenSizeX->SetPosition(Vector3(SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 + 80, 0));
	auto screenSizeY = imageObj->AddComponent<NumText>();
	screenSizeY->SetText(SCREEN_HEIGHT);
	screenSizeY->SetColor(D3DXVECTOR4(0, 0, 0, 1));
	screenSizeY->SetFontSize(20);
	screenSizeY->SetPosition(Vector3(SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT / 2 + 80, 0));
	ObjectManager::Instantiate(imageObj);
	

	player = new GameObject("プレイヤー");
	//player->AddComponent<Player>();
	player->AddComponent<SphereCollider>();
	player->AddComponent<Quad>()->SetTexture(tex);
	player->SetTag(PLAYER);
	ObjectManager::Instantiate(player);

	player->Rotate(Vector3(1.57f,0,0));
	player->SetScale(Vector3(10, 10, 0));

	for (int i = 0; i < 5; i++) {
		auto target = new GameObject("ターゲット" + to_string(i));
		target->AddComponent<SphereCollider>();
		target->AddComponent<Billboard>();
		target->SetTag(ENEMY);
		target->SetPosition(Vector3(i * 2 - 4, 0, 5));
		ObjectManager::Instantiate(target);

	}

	// ウインドウの表示(初期化処理の後に行う)
	ShowWindow(window, cmdShow);
	UpdateWindow(window);
}

void Uninit() {
	RendererManager::End();

	Input::Uninit();
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

				camera->Move(Vector3(0, Input::GetMouseWheel() * 0.001f, 0));
				if (Input::GetKey('Q')) {
					camera->Rotate(0, 0.1f, 0);
				}
				if (Input::GetKey('E')) {
					camera->Rotate(0, -0.1f, 0);
				}
				if (Input::GetKey('W')) {
					camera->Move(0, 0, 0.1f);
				}
				if (Input::GetKey('A')) {
					camera->Move(-0.1f, 0, 0);
				}
				if (Input::GetKey('S')) {
					camera->Move(0, 0, -0.1f);
				}
				if (Input::GetKey('D')) {
					camera->Move(0.1f, 0, 0);
				}
				fps->SetText(1 / Time::GetDeltaTime());

				// 描画処理
				RendererManager::Begin();
				ObjectManager::Draw();
				RendererManager::End();
				Input::SetMouseWheel(0);
			}
		}
	}
}
