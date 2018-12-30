#include "..\..\includes\Conf\FileBookMarkConf.h"
#include <fstream>
#include "ScintillaHelper.h"
using namespace std;
// STATIC VARIABLES

vector<wstring> FileBookMarkConf::fileNames;

// END STATIC VARIABLES

FileBookMarkConf::~FileBookMarkConf(void)
{
}

void FileBookMarkConf::addFile(wstring file)
{
	fileNames.push_back(file);
}

void FileBookMarkConf::addCurrFile()
{
	wstring name = NppPlugin::ScintillaHelper::GetCurrFullFileName();
	
	if( name.size() > 0)
		addFile( name );
}

bool FileBookMarkConf::writeToFile()
{
	string outFileName = getenv("APPDATA");
	outFileName = outFileName + "Notepad++\\plugins\\Config";
	ofstream fout;
	fout.open(outFileName.c_str(), ios::trunc );
	if ( !fout )
	{
		return false;
	}
	else
	{
		for( vector<wstring>::iterator it = fileNames.begin();it!=fileNames.end();it++)
		{
			fout<<it->c_str()<<endl;
		}
	}
	fout.close();

	return true;
}