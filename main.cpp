#include <iostream>
#include "Program.h"
using namespace std;

int main(int argc, char** argv)
{
	Program p;

	p.fileRead();
	p.printMenu();
	p.fileWrite();

	return 0;
}