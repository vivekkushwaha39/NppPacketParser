#pragma once
#include "DockingFeature\DockingDlgInterface.h"
#include "../res/resource.h"
#include <string>
#include <vector>
#include "Conf\FileBookMarkConf.h"
#include <string>
class TLVDialog: public DockingDlgInterface
{
public:
	TLVDialog() :DockingDlgInterface(IDD_TLVDIALOG)	{}
protected:
	virtual INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);

};