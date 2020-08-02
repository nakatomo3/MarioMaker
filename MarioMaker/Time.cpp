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
	LogWriter::Log("Timeが初期化されました");
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
	LONGLONG LongDef = m_Counter.QuadPart - startFrameClock;    // 差分カウント数を算出する。
	double dDef = (double)LongDef;
	return dDef / clocksPerSecond;
}

bool Time::IsUpdate() {
	QueryPerformanceCounter(&m_Counter);                     // 現在の時刻を取得し、
	LONGLONG LongDef = m_Counter.QuadPart - beforeFrameClock;    // 差分カウント数を算出する。
	double dDef = (double)LongDef;                             // 倍精度浮動小数点に変換
	beforeFrameClock = m_Counter.QuadPart;                       // 現在の時刻を保持

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
		LogWriter::LogError("ChangeTimeSpeedで%fを設定しました。マイナスの数字は入力しないでください",speed);
		return;
	}
	timeScale = speed;
}

float Time::GetTimeSpeed() {
	return timeScale;
}

double Time::GetNowDeltaTime() {                    // 現在の時刻を取得し、
	QueryPerformanceCounter(&m_Counter);                     // 現在の時刻を取得し、
	LONGLONG LongDef = m_Counter.QuadPart - beforeFrameClock;    // 差分カウント数を算出する。
	double dDef = (double)LongDef;                             // 倍精度浮動小数点に変換
	beforeFrameClock = m_Counter.QuadPart;                       // 現在の時刻を保持

	interval += dDef / clocksPerSecond;
															   
	return interval;
}
