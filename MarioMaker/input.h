#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include "Singleton.h"
#include <dinput.h>
#include <Windows.h>
#include <XInput.h>
#include <vector>
#include "Vector2.h"
using namespace std;

#define	NUM_KEY_MAX	(256)	// �L�[�̍ő吔

#pragma comment (lib, "xinput.lib")

enum MouseButton {
	MOUSE_LEFT		= 0,
	MOUSE_RIGHT		= 1,
	MOUSE_CENTER	= 2
};

enum LOG_FILE_STATE {
	NONE = 0,
	READ = 1,
	WRITE = 2
};

class Input {
public:
	static void Init(HWND hWnd);
	static void Uninit();

	static void Update();

	static bool GetKey(BYTE key);
	static bool GetKeyDown(BYTE key);
	static bool GetKeyUp(BYTE key);

	static bool GetMouse(MouseButton button);
	static bool GetMouse(int button);
	static bool GetMouseDown(MouseButton button);
	static bool GetMouseDown(int button);
	static bool GetMouseUp(MouseButton button);
	static bool GetMouseUp(int button);

	static XINPUT_STATE GetController(int index);

	static Vector2 GetCursorPosition();

	//�}�E�X�z�C�[���̉�]��
	static int GetMouseWheel();
	//windows�̃R�[���o�b�N�֐�����擾���邽�߂Ɏg�p�A�g�p�֎~
	static void SetMouseWheel(int value);

	//path�̃t�@�C����ǂݍ��ݎn�߂܂�
	static bool StartLogRead(string path);
	//folder/path�̃t�@�C����ǂݍ��ݎn�߂܂�
	static bool StartLogRead(string folder, string path);
	//���̓��O�t�@�C�����������ݎn�߂܂�
	static bool StartLogWrite();
	//path�̃��O�t�@�C�����������ݎn�߂܂�
	static bool StartLogWrite(string path);
	//folder/path�̃��O�t�@�C�����������ݎn�߂܂�
	//folder�͖��������玩���ō��܂����A������ԂŊK�w�\���Ŏw�肷��Ǝ��s���܂�
	static bool StartLogWrite(string folder, string path);

	static void EndLogReadWrite();

private:
	static BYTE oldKeyState[256];
	static BYTE keyState[256];

	static bool mouseOldState[3];
	static bool mouseState[3];

	static bool InitInput();
	static void UninitInput();

	static bool InitKeyboard(HINSTANCE hInstance, HWND hWnd);
	static void UninitKeyboard();

	static vector<XINPUT_STATE> controllers;

	static HWND hWnd;

	static int mouseWheelDelta;

	static double timer;

	static BYTE noInputFrameCount;

	static unsigned int readPos;
	static bool isReadingNoInput;
	static bool isEndReadFile;

	static LOG_FILE_STATE logFileState;

	static string logFilePath;

	Input();
	~Input();
};

