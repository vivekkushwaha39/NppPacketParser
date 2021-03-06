#include "ScintillaHelper.h"
#include "PluginDefinition.h"
using namespace std;
extern NppData nppData;
using namespace NppPlugin;

HANDLE ScintillaHelper::hModule = NULL;

ScintillaHelper::ScintillaHelper(void)
{
}


ScintillaHelper::~ScintillaHelper(void)
{
}

unsigned char ScintillaHelper::GetSelectedText(string &data)
{
	int which = -1;
	::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
    if (which == -1)
        return -1;

	HWND curScintilla = (which == 0)?nppData._scintillaMainHandle:nppData._scintillaSecondHandle;
	
	int end =  ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0 );
	int start = ::SendMessage(curScintilla, SCI_GETSELECTIONSTART, 0, 0 );
	
	if( end-start <= 0 )
	{
		return -2;
	}

	char *buff = new char[end - start + 2];

	TextRange tr;
	tr.chrg.cpMin = start ;
	tr.chrg.cpMax = end;
	tr.lpstrText = (char*) buff;
	::SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM) buff);
	data = string((char*)buff);
	delete []buff;
	return 0;
}

bool ScintillaHelper::OpenFile(const wstring &wfileName)
{

	::SendMessage(nppData._nppHandle, NPPM_DOOPEN, (WPARAM) 0, (LPARAM) wfileName.c_str());
	
	return  true;
}

tstring ScintillaHelper::GetCurrFullFileName()
{
	TCHAR buffer[1024];
	size_t buffSIZE = 1024;
	::SendMessage(nppData._nppHandle, NPPM_GETFULLCURRENTPATH, (WPARAM)buffSIZE,(LPARAM) buffer);
	return tstring(buffer);
}