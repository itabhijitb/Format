#include "Format.h"
#include <iostream>
int main()
{
	std::wcout<<Format(_T("{0}{1}"))(std::tstring(_T("Abhijit")),1106).str()<<std::endl;
}