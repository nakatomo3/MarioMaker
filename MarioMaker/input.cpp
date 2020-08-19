#define _CRT_SECURE_NO_WARNINGS
#include "Setting.h"
#include "Input.h"
#include "LogWriter.h"
#include <stdio.h>
#include <time.h>
#include <direct.h>
#include <Windows.h>
#include "LogWriter.h"
#include "Time.h"

BYTE Input::oldKeyState[256];
BYTE Input::keyState[256];
vector<XINPUT_STATE> Input::controllers;
HWND Input::hWnd;
bool Input::mouseOldState[3];
bool Input::mouseState[3];
int Input::mouseWheelDelta;
double Input::timer = 0;
BYTE Input::noInputFrameCount = 0;
unsigned int Input::readPos = 0;
bool Input::isReadingNoInput = false;
LOG_FILE_STATE Input::logFileState;
string Input::logFilePath;

#define FOLDER_NAME_LENGTH (20)
#define FILE_NAME_LENGTH (13)
#define PATH_LENGTH (FOLDER_NAME_LENGTH + FILE_NAME_LENGTH)

FILE* inputFile;
char inputPath[PATH_LENGTH];
bool Input::InitInput() {
	memset(oldKeyState, 0, 256);
	memset(keyState, 0, 256);
	XINPUT_VIBRATION vib{ 10000 ,10000 };
	return true;
}

void Input::UninitInput() {
	
}

bool Input::InitKeyboard(HINSTANCE hInstance, HWND hWnd) {
	

	return true;
}

void Input::UninitKeyboard() {
	
}

void Input::Init(HWND _hwnd) {

	hWnd = _hwnd;

	InitInput();

	//�Q�[���p�b�h�Ȃǂ̏��������ǉ��\��
	for (int i = 0; i < 4; i++) {
		XINPUT_STATE state;
		controllers.emplace_back(state);
		ZeroMemory(&controllers[i], sizeof(XINPUT_STATE));
	}
}

void Input::Uninit() {
	if (inputFile != nullptr) {
		fclose(inputFile);
	}
	LogWriter::Log("Input������ɏI�����܂���");
}

void Input::Update() {

	memcpy(oldKeyState, keyState, 256);
	GetKeyboardState(keyState);

	mouseOldState[0] = mouseState[0];
	mouseOldState[1] = mouseState[1];
	mouseOldState[2] = mouseState[2];

	mouseState[0] = GetAsyncKeyState(VK_LBUTTON);
	mouseState[1] = GetAsyncKeyState(VK_RBUTTON);
	mouseState[2] = GetAsyncKeyState(VK_MBUTTON);

	for (int i = 0; i < 4; i++) {
		XInputGetState(i, &controllers[i]);
	}

	timer += Time::GetDeltaTime();

	if (logFileState == WRITE) {
		bool isSaveFile = false;
		if (timer >= 1) {
			isSaveFile = true;
		}
		if (inputFile != NULL) {
			//fprintf(inputFile, "[ ] input\n");
			bool input = false;
			vector<BYTE> inputs;
			for (int i = 0; i < 0xE0; i++) {
				if (keyState[i] & 0x80) {
					inputs.emplace_back((BYTE)i);
					input = true;
				}
			}
			if (input == false) {
				if (noInputFrameCount == 0) {
					BYTE num0 = 0;
					noInputFrameCount++;
					fwrite(&num0, sizeof(BYTE), 1, inputFile);
				} else if(noInputFrameCount == 0xFF){
					fwrite(&noInputFrameCount, sizeof(BYTE), 1, inputFile);
					noInputFrameCount = 0;
				} else {
					noInputFrameCount++;
				}
			} else {
				if (noInputFrameCount > 0) {
					fwrite(&noInputFrameCount, sizeof(BYTE), 1, inputFile);
				}
				if (inputs.size() > 0) {
					for (unsigned int i = 0; i < inputs.size(); i++) {
						fwrite(&inputs[i], sizeof(BYTE), 1, inputFile);
					}
					BYTE num256 = 0xFF;
					fwrite(&num256, sizeof(BYTE), 1, inputFile);
					noInputFrameCount = 0;
				}
			}
		
			if (isSaveFile == true) {
				fclose(inputFile);
				inputFile = fopen(inputPath, "ab");
				timer = 0;
			}
		} else {
			LogWriter::Log("inputFile��null�ł�");
		}
	} else if (logFileState == READ && (strlen(logFilePath.c_str()) > 0)) {

		if (isReadingNoInput == true) {
			noInputFrameCount++;
			fseek(inputFile, readPos, SEEK_SET);
			BYTE readChar;
			//LogWriter::Log("noinput");
			fread(&readChar, sizeof(BYTE), 1, inputFile);
			if (noInputFrameCount >= readChar) {
				readPos++;
				isReadingNoInput = false;
				noInputFrameCount = 0;
				//LogWriter::Log("endNoInput");
			}
		} else {
			fseek(inputFile, readPos, SEEK_SET);
			BYTE readChar;
			int num = fread(&readChar, sizeof(BYTE), 1, inputFile);
			if (readChar == 0x00) {
				isReadingNoInput = true;
				readPos++;
				return;
			}
			while (true) {
				if (num > 0) {
					//���͔��f
					//LogWriter::Log("%x", readChar);
					keyState[readChar] = 0x80;
					readPos++;
				} else {
					return;
				}
				num = fread(&readChar, sizeof(BYTE), 1, inputFile);
				if (readChar == 0xFF) {
					readPos++;
					break;
				}
			}
		}

	}
}

//���͒l�FVK_HOGE or 'A' or '0'�Ȃ�
bool Input::GetKey(BYTE key) {
	return (keyState[key] & 0x80);
}

//���͒l�FVK_HOGE or 'A' or '0'�Ȃ�
bool Input::GetKeyDown(BYTE key) {
	return (keyState[key] & 0x80 && !(oldKeyState[key] & 0x80));
}

//���͒l�FVK_HOGE or 'A' or '0'�Ȃ�
bool Input::GetKeyUp(BYTE key) {
	return (!(keyState[key] & 0x80) && oldKeyState[key] & 0x80);
}

bool Input::GetMouse(MouseButton button) {
	return mouseState[button];
}

bool Input::GetMouse(int button) {
	if (button < 0) {
		LogWriter::Log("GetMouse��0�ȏ�ɂ��Ă�������");
	}
	if (button > 2) {
		LogWriter::Log("GetMouse��2�ȉ��ɂ��Ă�������");
	}
	return mouseState[button];
}

bool Input::GetMouseDown(MouseButton button) {
	return mouseState[button] == true && mouseOldState[button] == false;
}

bool Input::GetMouseDown(int button) {
	if (button < 0) {
		LogWriter::Log("GetMouse��0�ȏ�ɂ��Ă�������");
	}
	if (button > 2) {
		LogWriter::Log("GetMouse��2�ȉ��ɂ��Ă�������");
	}
	return mouseState[button] == true && mouseOldState[button] == false;;
}

bool Input::GetMouseUp(MouseButton button) {
	return mouseState[button] == false && mouseOldState[button] == true;
}

bool Input::GetMouseUp(int button) {
	if (button < 0) {
		LogWriter::Log("GetMouse��0�ȏ�ɂ��Ă�������");
	}
	if (button > 2) {
		LogWriter::Log("GetMouse��2�ȉ��ɂ��Ă�������");
	}
	return mouseState[button] == false && mouseOldState[button] == true;
}

XINPUT_STATE Input::GetController(int index) {
	return controllers[index];
}

Vector2 Input::GetCursorPosition() {
	POINT point;
	GetCursorPos(&point);
	SetCursorPos(point.x, point.y);

	RECT lprc;
	GetWindowRect(hWnd, &lprc);
	return Vector2((float)(point.x - lprc.left), (float)(point.y - lprc.top - 30));
}

int Input::GetMouseWheel() {
	return mouseWheelDelta;
}

void Input::SetMouseWheel(int value) {
	mouseWheelDelta = value;
}

bool Input::StartLogRead(string path) {
	logFilePath = path;
	if (strlen(logFilePath.c_str()) > 0) {
		inputFile = fopen(logFilePath.c_str(), "rb");
		logFileState = READ;
	} else {
		LogWriter::Log("StartLogRead��path��1�����ȏ�ɂ��Ă�������");
		logFileState = NONE;
	}
	return true;
}

bool Input::StartLogRead(string folder, string path) {
	return true;
}

bool Input::StartLogWrite() {
	logFileState = WRITE;
	time_t timer = time(NULL); //�������擾����
	struct tm *local = localtime(&timer); //���ݒn�����ɕϊ�����

	_mkdir("InputLogs"); //Log�t�H���_���쐬����
	char folder[FOLDER_NAME_LENGTH];
	sprintf(folder, "InputLogs/%04d%02d%02d", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday); //�쐬����t�H���_�̖��O��N�����Ō��肷��
	_mkdir(folder); //�N�����t�H���_���쐬����
	sprintf(inputPath, "InputLogs/%04d%02d%02d/%02d_%02d_%02d.log", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec); //�p�X���݂̃t�@�C������ݒ肷��
	inputFile = fopen(inputPath, "ab");
	if (inputFile == NULL) {
		return false;
	}
	LogWriter::Log("���̓��O�t�@�C�����쐬���܂���");
	return true;
}

bool Input::StartLogWrite(string path) {
	return false;
}

bool Input::StartLogWrite(string folder, string path) {
	return false;
}

void Input::EndLogReadWrite() {
	switch (logFileState) {
	case NONE:
		break;
	case READ:
		fclose(inputFile);
		logFileState = NONE;
		break;
	case WRITE:
		fclose(inputFile);
		logFileState = NONE;
		break;
	default:
		LogWriter::Log("Input�̃t�@�C���ǂݏ����X�e�[�^�X���s���ł����B�K�����ǂ����m���߂Ă�������");
		logFileState = NONE;
		break;
	}
}

Input::Input() {

}


Input::~Input() {
}
