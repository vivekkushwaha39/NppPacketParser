#ifndef SCINTILLA_HELPER_H
#define SCINTILLA_HELPER_H
#include "CustomTypeDefs.h"
namespace NppPlugin
{
	class ScintillaHelper
	{
		static HANDLE hModule;

	public:
		ScintillaHelper(void);
		~ScintillaHelper(void);
		static unsigned char GetSelectedText(std::string & );
		static bool OpenFile(const std::wstring &);
		static HANDLE GethModule(){ return ScintillaHelper::hModule; }
		static void SethModule(HANDLE _hModule){ ScintillaHelper::hModule = _hModule; }
		static tstring GetCurrFullFileName();
	};
}
#endif /* SCINTILLA_HELPER_H */