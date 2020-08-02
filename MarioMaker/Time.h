#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <time.h>

class Time {
public:
	
	static void Init();

	//���݂�FPS���擾���܂�
	static int GetFPS();
	//�����݃A�b�v�f�[�g�o���邩���擾���܂�(�ݒ�FPS�𒴂��Ȃ��悤�ɂ��Ă��܂�)
	static bool IsUpdate();

	//1�t���[���O�Ƃ̎��Ԃ̍����擾���܂�
	static double GetDeltaTime();

	//1�t���[���O�Ƃ̎��Ԃ̍�(TimeScale�ɂ��Ȃ�)���擾���܂�
	static double GetUnscaledDeltaTime();

	//�X�^�[�g���Ă���̃t���[�������擾���܂�
	static int GetFrameFromStart();

	//�X�^�[�g���Ă���̎��Ԃ��擾���܂�
	static double GetTimeFromStart();

	//���Ԃ�����鑬����ύX���܂�
	static void SetTimeSpeed(float speed);
	//���Ԃ�����鑬�����擾���܂�
	static float GetTimeSpeed();

	//���݂�DeltaTime���擾���܂�
	//�������ꂪ1/DEFAULT_FPS��傫�������Ă����ꍇ�����𒆒f���邱�Ƃ������߂��܂�
	//���̎��s�Ŏg�p���鎞�Ԃ͂ق�0ms�ł�
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