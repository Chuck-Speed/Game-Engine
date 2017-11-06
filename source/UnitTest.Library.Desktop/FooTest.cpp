#include "pch.h"
//#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{		
	TEST_CLASS(FooTest)
	{
	public:

		TEST_METHOD(FooTestConstructor)
		{
			int a = 10;
			Foo f(a);

			Assert::AreEqual(a, f.Data());
		}

		TEST_METHOD(FooTestData)
		{
			int a = 10;
			Foo f(a);
			int ref = f.Data();

			Assert::AreEqual(a, ref);
		}

	};
}