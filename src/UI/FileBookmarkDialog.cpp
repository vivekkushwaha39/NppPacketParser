#include "..\..\includes\DockingFeature\FileBookmarkDialog.h"
#include "PluginDefinition.h"
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
					delete this;
					return TRUE;
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
		for (std::vector<std::wstring>::iterator it = items.begin() ; it != items.end() ; it++ )
		{
			addItem(*it);
		}
	}
}