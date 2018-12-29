
#include "DockingFeature\DockingDlgInterface.h"
#include "../res/resource.h"

class FileBookmarkDialog :
	public DockingDlgInterface
{
public:
	FileBookmarkDialog(void): DockingDlgInterface(IDD_DIALOG2){}
	virtual ~FileBookmarkDialog(void){};
protected:
	virtual INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);

};
