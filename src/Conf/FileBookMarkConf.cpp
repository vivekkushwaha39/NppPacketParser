#include "..\..\includes\Conf\FileBookMarkConf.h"
#include <fstream>
#include <sstream>
#include "ScintillaHelper.h"
using namespace std;
// STATIC VARIABLES

vector<wstring> FileBookMarkConf::fileNames;
bool FileBookMarkConf::needToWrite = false;
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
	{
		addFile( name );
		FileBookMarkConf::needToWrite = true;
	}
}

bool FileBookMarkConf::loadListFromFile()
{
	string inFileName(getenv("APPDATA"));
	inFileName = inFileName + "\\Notepad++\\plugins\\Config\\fileBookmark.txt";
	
	ifstream fin;
	
	fin.open(inFileName.c_str());

	if ( !fin )
	{
		return false;
	}
	
	string line;
	int count=0;
	
	while( getline(fin, line)  )
	{
		wstring wfile( line.begin(), line.end());
		addFile( wfile );
	}

	return true;
}

bool FileBookMarkConf::writeToFile()
{
	string outFileName(getenv("APPDATA"));
	outFileName = outFileName + "\\Notepad++\\plugins\\Config\\fileBookmark.txt";
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
			string towrite( it->begin(), it->end() );
			fout<<towrite<<endl;
		}
	}
	fout.close();

	return true;
}

bool FileBookMarkConf::exitAction()
{
	if( FileBookMarkConf::needToWrite )
	{
		return FileBookMarkConf::writeToFile();
	}
	return true;
}


wstring FileBookMarkConf::getItemAt(int index)
{
	wstring ret = L"";

	if ( fileNames.size() >= index )
	{
		ret = fileNames[index];
	}

	return ret;
}