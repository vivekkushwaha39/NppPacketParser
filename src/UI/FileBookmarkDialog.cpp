#include "..\..\includes\DockingFeature\FileBookmarkDialog.h"
#include "PluginDefinition.h"
#include "ScintillaHelper.h"
#include <WindowsX.h>

using namespace std;
extern NppData nppData;

INT_PTR CALLBACK FileBookmarkDialog::run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
		case WM_COMMAND : 
		{
			switch (wParam)
			{
				case IDOK :
				{
					FileBookmarkDialog::openSelectedFile();
					delete this;
					return TRUE;
					break;

				}
				case IDCANCEL:
				{
					delete this;
					return TRUE;
					break;
				}

			}
				return FALSE;
		}

		default :
			return DockingDlgInterface::run_dlgProc(message, wParam, lParam);
	}
}

void FileBookmarkDialog::addItem(wstring item)
{
	::SendDlgItemMessage(this->_hSelf, IDC_LSTBKMK, LB_ADDSTRING, 0, (LPARAM) item.c_str());
}

void FileBookmarkDialog::refreshList()
{
	{
		std::vector<std::wstring> items = FileBookMarkConf::getFileNames();
		for ( vector<wstring>::iterator it = items.begin(); it != items.end(); it++ )
		{
			this->addItem( *it );
		}
	}
}


int FileBookmarkDialog::openSelectedFile()
{
	HWND listHandle = ::GetDlgItem(this->_hSelf , IDC_LSTBKMK);
	int indices[1];
	
	int ret = ListBox_GetSelItems(listHandle, 1, indices);
	if ( ret < 1)
	{
		MessageBox(0,L"Invalid index", L"Info", MB_OK);
	}
	else
	{

		wstring wfile = FileBookMarkConf::getItemAt(indices[0]);
		if ( wfile.size() > 0 )
		{
			NppPlugin::ScintillaHelper::OpenFile(wfile);
		}

	}


	return ret;
}