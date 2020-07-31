#include "../includes/DockingFeature/PrefDialog.h"
#include "../includes/Conf/Config.h"
#include <string.h>
#include <winnt.h>
INT_PTR CALLBACK PrefDialog::run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		switch (wParam)
		{
		case IDCANCEL:
		{
			delete this;
			return TRUE;
		}
		}
		return FALSE;
	}

	default:
		return DockingDlgInterface::run_dlgProc(message, wParam, lParam);
	}
}

void PrefDialog::initStaticElements()
{
	Config& con = Config::getInstance();
	::SetDlgItemText(this->_hSelf, IDC_LBL_PYEXEC, L"Python bin");
	::SetDlgItemText(this->_hSelf, IDC_TXT_PYEX, (TCHAR *)con.getPythonExec().c_str() );
}
