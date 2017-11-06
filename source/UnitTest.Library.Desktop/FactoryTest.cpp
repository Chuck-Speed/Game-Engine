#include "pch.h"
#include "Factory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{

	TEST_CLASS(FactoryTest)
	{
	public:
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif

#if defined(DEBUG) | defined(_DEBUG)
		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
		}
#endif

		ConcreteFactory(RTTI, AttributedFoo)

		TEST_METHOD(FactoryTestMaster)
		{
			Assert::IsTrue(Factory<RTTI>::Create("AttributedFoo") == nullptr);
			Assert::IsTrue(Factory<RTTI>::Find("AttributedFoo") == nullptr);

			AttributedFooFactory aFoo;
			RTTI* foo = aFoo.Create();
			RTTI* foo2 = Factory<RTTI>::Create("AttributedFoo");
			Assert::IsTrue(Factory<RTTI>::begin() != Factory<RTTI>::end());
			Assert::IsTrue(Factory<RTTI>::Find("AttributedFoo") != nullptr);

			AttributedFoo* rFoo = foo->As<AttributedFoo>();
			Assert::IsTrue(rFoo != nullptr);
			delete foo;
			delete foo2;
			
		}
	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState FactoryTest::sStartMemState;
#endif
}