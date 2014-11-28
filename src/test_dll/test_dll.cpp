#include "stdafx.h"

#define LIB_TEST_DLL_EXPORTS
#include "test_dll.h"

LIB_TEST_DLL_API TestDllAPI::TestDllAPI()
{
}

LIB_TEST_DLL_API TestDllAPI::~TestDllAPI()
{
}

LIB_TEST_DLL_API void TestDllAPI::test_function(const int &val)
{
	printf("TestDllAPI::test_function() : val=%d\n", val);
}