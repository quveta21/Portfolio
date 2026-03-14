#include <stdio.h>
#include "ui.h"
#include "tests.h"

int main()
{
	repo_tests();
	controller_tests();
	start_ui();
	return 0;
}
