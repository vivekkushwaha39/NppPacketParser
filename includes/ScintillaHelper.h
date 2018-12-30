#ifndef SCINTILLA_HELPER_H
#define SCINTILLA_HELPER_H

#include <string>
#include <Windows.h>
namespace NppPlugin
{
	class ScintillaHelper
	{
		static HANDLE hModule;

	public:
		ScintillaHelper(void);
		~ScintillaHelper(void);
		unsigned char GetSelectedText(std::string & );
		bool OpenFile(const std::string &);
		static HANDLE GethModule(){ return ScintillaHelper::hModule; }
		static void SethModule(HANDLE _hModule){ ScintillaHelper::hModule = _hModule; }
		static std::wstring GetCurrFullFileName();
	};
}
#endif /* SCINTILLA_HELPER_H */