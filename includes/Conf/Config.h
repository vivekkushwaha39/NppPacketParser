#pragma once
#include "CustomTypeDefs.h"
#define DEF_PREF_FILE_NAME TEXT("tlv-tool.ini")
class Config
{
private:
	tstring pythonExec;
	static Config* _instance;
	Config();
public:
	void fetchPreferences(tstring = DEF_PREF_FILE_NAME );
	static Config& getInstance();
	tstring getPythonExec();
};

