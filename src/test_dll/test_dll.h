#pragma once

#ifdef LIB_TEST_DLL_EXPORTS
	#define LIB_TEST_DLL_API __declspec(dllexport)
#else
	#define LIB_TEST_DLL_API __declspec(dllimport)
	#ifdef _DEBUG
		#pragma comment(lib, "test_dllD.lib")
	#else
		#pragma comment(lib, "test_dll.lib")
	#endif
#endif

class LIB_TEST_DLL_API TestDllAPI
{
public:
	TestDllAPI();
	virtual ~TestDllAPI();

	void test_function(const int &val);
};

