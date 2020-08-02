#include "Time.h"
#include <timeapi.h>
#include "LogWriter.h"
#pragma comment(lib, "winmm.lib")
#include "Setting.h"
double clockPerSecond;

float Time::FPS = DEFAULT_FPS;
float Time::timeScale = 1;

double Time::deltaTime = 0;

int Time::frameCount = 0;

LARGE_INTEGER Time::m_Counter;
LONGLONG Time::beforeFrameClock = 0;
double Time::clocksPerSecond = 0;
LONGLONG Time::startFrameClock;

double Time::interval = 0;

void Time::Init() {
	FPS = DEFAULT_FPS;
	frameCount = 0;
	LARGE_INTEGER Freq;
	clockPerSecond = QueryPerformanceFrequency(&Freq);
	clocksPerSecond = (double)Freq.QuadPart;
	QueryPerformanceCounter(&m_Counter);
	beforeFrameClock = m_Counter.QuadPart;
	startFrameClock = m_Counter.QuadPart;
	LogWriter::Log("Time������������܂���");
}


Time::~Time() {

}

int Time::GetFPS() {
	return (int)FPS;
}

double Time::GetDeltaTime() {
	return deltaTime * timeScale;
}

double Time::GetUnscaledDeltaTime() {
	return deltaTime;
}

int Time::GetFrameFromStart() {
	return frameCount;
}

double Time::GetTimeFromStart() {
	LONGLONG LongDef = m_Counter.QuadPart - startFrameClock;    // �����J�E���g�����Z�o����B
	double dDef = (double)LongDef;
	return dDef / clocksPerSecond;
}

bool Time::IsUpdate() {
	QueryPerformanceCounter(&m_Counter);                     // ���݂̎������擾���A
	LONGLONG LongDef = m_Counter.QuadPart - beforeFrameClock;    // �����J�E���g�����Z�o����B
	double dDef = (double)LongDef;                             // �{���x���������_�ɕϊ�
	beforeFrameClock = m_Counter.QuadPart;                       // ���݂̎�����ێ�

	interval += dDef / clocksPerSecond;

	if (interval < 1.0 / FPS) {
		return false;
	}
	deltaTime = interval;
	interval = 0;

	frameCount++;

	return true;
}

void Time::SetTimeSpeed(float speed) {
	if (speed < 0) {
		LogWriter::LogError("ChangeTimeSpeed��%f��ݒ肵�܂����B�}�C�i�X�̐����͓��͂��Ȃ��ł�������",speed);
		return;
	}
	timeScale = speed;
}

float Time::GetTimeSpeed() {
	return timeScale;
}

double Time::GetNowDeltaTime() {                    // ���݂̎������擾���A
	QueryPerformanceCounter(&m_Counter);                     // ���݂̎������擾���A
	LONGLONG LongDef = m_Counter.QuadPart - beforeFrameClock;    // �����J�E���g�����Z�o����B
	double dDef = (double)LongDef;                             // �{���x���������_�ɕϊ�
	beforeFrameClock = m_Counter.QuadPart;                       // ���݂̎�����ێ�

	interval += dDef / clocksPerSecond;
															   
	return interval;
}
