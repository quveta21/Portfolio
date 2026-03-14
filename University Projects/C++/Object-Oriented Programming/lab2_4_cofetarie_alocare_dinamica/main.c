#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include "ui.h"
#include "tests.h"
#include <crtdbg.h>

int main()
{
	repo_tests();
	controller_tests();
	start_ui();
	_CrtDumpMemoryLeaks();
	return 0;
}
