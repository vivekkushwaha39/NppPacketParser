#pragma once
#include <vector>
#include <string>


class FileBookMarkConf
{
	static std::vector<std::wstring> fileNames;
	static bool needToWrite;	
public:
	static void addFile(std::wstring );
	static void addCurrFile();
	static std::vector<std::wstring> getFileNames(){return fileNames;}
	static bool loadListFromFile();
	static bool writeToFile();
	static bool exitAction();
	static std::wstring getItemAt(int );
	~FileBookMarkConf(void);
};
