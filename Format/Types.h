#ifndef __TYPES__
#define __TYPES__
/******************************************************************************
*                                 STL Headers                                 *
******************************************************************************/
#include <string>
/******************************************************************************
*                             Application Headers                             *
******************************************************************************/
namespace std
{
    #ifdef _UNICODE 
        typedef wstring tstring ;
        typedef wstringstream tstringstream ;
        typedef wchar_t tchar;
        template <typename Ty>
        tstring to_tstring(Ty _Val)
        {
            return std::to_wstring(_Val);
        }
        #define _T(x) L##x
    #else
        typedef string tstring;
        typedef stringstream tstringstream;
        typedef char tchar;
        string to_tstring(Ty _Val)
        {
            return std::to_string(_Val);
        }
        #define _T(x) x
    #endif
};
#ifdef _UNICODE 
typedef wchar_t tchar;
#else
typedef char tchar;
#endif
#endif