#include "test_dll.h"

int main(int argc, char* argv[])
{
	TestDllAPI test_dll;

	test_dll.test_function(123);

	return 0;
}

