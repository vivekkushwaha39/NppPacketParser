#include "Conf/Config.h"
using namespace std;
Config& Config::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Config();
	}
	return *_instance;
}
void Config::fetchPreferences(tstring fileName)
{
	this->pythonExec = TEXT("C:\\cygwin\\bin\\python3.6m.exe");
}

tstring Config::getPythonExec()
{
	return this->pythonExec;
}

Config::Config()
{
	fetchPreferences();
}

Config* Config::_instance = nullptr;

