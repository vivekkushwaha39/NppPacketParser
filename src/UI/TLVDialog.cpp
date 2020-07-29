#include <codecvt>
#include <CustomTypeDefs.h>
#include "../includes/DockingFeature/TLVDialog.h"
#include "../includes/ScintillaHelper.h"
#include "../includes/Conf/Config.h"
#include "../includes/Utils.h"

using namespace std;
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

void TLVDialog::parseSelected()
{
	::ShowWindow(GetConsoleWindow(), SW_HIDE);
	string selText;
	NppPlugin::ScintillaHelper::GetSelectedText(selText);
	Utils::removeNonHex(selText);

	if (selText.size() > 0)
	{
		string command;
		string out;
		tstring wPyExec = Config::getInstance().getPythonExec();
		string pyExec = WS_TO_S(wPyExec);
		command = pyExec +
			string(" C:\\cygwin\\opt\\npp.7.8.6\\plugins\\NppPacketParser\\python\\tlv2json.py 1 ") +
			selText;
		try 
		{
			int processOut = Utils::GetProcessOutput(command, out);
			if ( processOut != 0)
			{
				stringstream ss;
				ss	<< command << endl
					<< "Process output is nonzero " 
					<< processOut;
				throw std::exception(ss.str().c_str());
			}
		}
		catch (std::exception e)
		{
			out = string(e.what());
		}
		catch (...)
		{
			out = "Some horrible exception in process call";
		}
		Utils::crTocrlf(out);
	
		CHAR_TO_UTF8(out);
		::SetDlgItemText(this->_hSelf, IDD_TXT_TREE, outPut);
		delete[]outPut;
	}
	else
	{
		::SetDlgItemText(this->_hSelf, IDD_TXT_TREE, TEXT("No text selected"));
	}
}