#include <string>
#include "Error.h"
#include <iomanip>
#include <sstream>
#include <wchar.h>
#include <map>
#include "Types.h"
class ErrorToken
{
private:
	std::tstring Lookup(int iErrorCode)
	{
		//Lookup Error Code
		return std::tstring();
	}
public:
	ErrorToken(wchar_t sev, int iErrorCode):
		m_iErrorCode(iErrorCode), m_wSev(sev), m_szErrMsg(Lookup(iErrorCode))
	{
		 
	};
	operator std::tstring()
	{
		std::tstringstream szErrMsg;
		switch(m_wSev)
		{
		case L'F':
			szErrMsg<<_T("Fatal   :");
			break;
		case L'E':
			szErrMsg<<_T("Error   :");
			break;
		case L'W':
			szErrMsg<<_T("Warning :");
			break;
		case L'I':
			szErrMsg<<_T("Info    :");
			break;
		default:
			szErrMsg<<_T("Unknown :");
			break;
		};
		szErrMsg<<std::setw(20);
		szErrMsg<<

	};
private:
	int          m_iErrorCode;
	wchar_t      m_wSev;
	std::tstring m_szErrMsg;
	std::tstring m_caller;
	std::tstring m_lineno;
};
class ErrorHandler
{

};