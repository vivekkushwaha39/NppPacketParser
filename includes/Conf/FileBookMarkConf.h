#include <vector>
#include <string>


class FileBookMarkConf
{
	static std::vector<std::wstring> fileNames;
	
public:
	static void addFile(std::wstring );
	static void addCurrFile();
	static std::vector<std::wstring> getFileNames(){return fileNames;}
	static void loadListFromFile();
	static bool writeToFile();

	~FileBookMarkConf(void);
};
