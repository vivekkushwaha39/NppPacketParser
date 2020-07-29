#pragma once
#include "DockingFeature\DockingDlgInterface.h"
#include "../res/resource.h"
#include <string>
#include <vector>

class PrefDialog: public DockingDlgInterface
{
public:
	PrefDialog() :DockingDlgInterface(IDD_PREF) {}
	virtual void initStaticElements();
protected:
	virtual INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);
};

