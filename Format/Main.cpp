#include "Format.h"
#include <iostream>
#include <memory>
#include <string>
int main()
{
	std::wcout<<Format(_T("{:10.6}"))(4321.)<<std::endl;
}