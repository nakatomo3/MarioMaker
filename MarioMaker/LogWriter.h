#pragma once
using namespace std;
#include <string>
#include "Singleton.h"
class LogWriter {
public:
	static void Log(const char*, ...);
	static void LogWorning(const char* format, ...);
	static void LogError(const char * format, ...);

	static void Init();
	static void Uninit();
private:
};