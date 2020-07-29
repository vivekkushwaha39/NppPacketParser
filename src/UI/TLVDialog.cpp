#include "../includes/DockingFeature/TLVDialog.h"

INT_PTR CALLBACK TLVDialog::run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam)
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