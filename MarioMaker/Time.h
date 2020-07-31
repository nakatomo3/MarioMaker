#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <time.h>

class Time {
public:
	
	static void Init();

	//現在のFPSを取得します
	static int GetFPS();
	//今現在アップデート出来るかを取得します(設定FPSを超えないようにしています)
	static bool IsUpdate();

	//1フレーム前との時間の差を取得します
	static double GetDeltaTime();

	//1フレーム前との時間の差(TimeScaleによらない)を取得します
	static double GetUnscaledDeltaTime();

	//スタートしてからのフレーム数を取得します
	static int GetFrameFromStart();

	//スタートしてからの時間を取得します
	static double GetTimeFromStart();

	//時間が流れる速さを変更します
	static void SetTimeSpeed(float speed);
	//時間が流れる速さを取得します
	static float GetTimeSpeed();

	//現在のDeltaTimeを取得します
	//もしこれが1/DEFAULT_FPSを大きく超えていた場合処理を中断することをお勧めします
	//一回の実行で使用する時間はほぼ0msです
	static double GetNowDeltaTime();

private :
	static float FPS;
	static float timeScale;
	
	static double deltaTime;

	static int frameCount;
	
	static LARGE_INTEGER m_Counter;
	static LONGLONG beforeFrameClock;
	static double clocksPerSecond;

	static double interval;

	static LONGLONG startFrameClock;

	~Time();

};