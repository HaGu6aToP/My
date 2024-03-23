#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include "Translator.h"
#include "Stack.h"
#include <string>
#include "List.h"


int _tmain(int argc, _TCHAR* argv[]) 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char* filename = "test.txt";

	try{
		auto l = MyClasses::�ompiler::SyntaxBlock().work(filename);
		int a = 1;
	}
	catch(const MyClasses::Error &e){
		char* s = e.getStr();
		std::cout << s;
		delete[] s;
	}

	std::cout << "True\n";

	system("pause");
}
