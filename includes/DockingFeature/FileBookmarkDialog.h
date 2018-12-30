
#include "DockingFeature\DockingDlgInterface.h"
#include "../res/resource.h"
#include <string>
#include <vector>
#include "Conf\FileBookMarkConf.h"
class FileBookmarkDialog :
	public DockingDlgInterface
{
public:
	FileBookmarkDialog(void): DockingDlgInterface(IDD_DIALOG2){}
	virtual ~FileBookmarkDialog(void){};
	void addItem(std::wstring );
	void refreshList();
protected:
	virtual INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);

};
