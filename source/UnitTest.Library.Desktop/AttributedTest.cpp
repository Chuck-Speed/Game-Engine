#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{

	TEST_CLASS(AttributedTest)
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

		TEST_METHOD(AttributedTestCopy)
		{
			AttributedFoo f;

			f.AppendAuxiliaryAttribute("AuxInt") = 1;
			f.AppendAuxiliaryAttribute(std::string("AuxFloat")) = 1.0f;
			f.AppendAuxiliaryAttribute(std::string("AuxVector")) = glm::vec4(1.0f, 2.0f, 3.0f, 4.0f);
			f.AppendAuxiliaryAttribute(std::string("AuxMatrix")) = glm::mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
			f.AppendAuxiliaryAttribute(std::string("AuxString")) = std::string("Bacon");

			AttributedFoo f2(f);
			Assert::IsTrue(f2.IsAttribute(std::string("AuxInt")));
			Assert::IsTrue(f2.IsAttribute(std::string("AuxFloat")));
			Assert::IsTrue(f2.IsAttribute(std::string("AuxVector")));
			Assert::IsTrue(f2.IsAttribute(std::string("AuxMatrix")));
			Assert::IsTrue(f2.IsAttribute(std::string("AuxString")));
			Assert::IsTrue(f[std::string("AuxInt")] == f2[std::string("AuxInt")]);
			Assert::IsTrue(f[std::string("AuxFloat")] == f2[std::string("AuxFloat")]);
			Assert::IsTrue(f[std::string("AuxVector")] == f2[std::string("AuxVector")]);
			Assert::IsTrue(f[std::string("AuxMatrix")] == f2[std::string("AuxMatrix")]);
			Assert::IsTrue(f[std::string("AuxString")] == f2[std::string("AuxString")]);

			f2 = f;
			Assert::IsTrue(f2.IsAttribute(std::string("AuxInt")));
			Assert::IsTrue(f2.IsAttribute(std::string("AuxFloat")));
			Assert::IsTrue(f2.IsAttribute(std::string("AuxVector")));
			Assert::IsTrue(f2.IsAttribute(std::string("AuxMatrix")));
			Assert::IsTrue(f2.IsAttribute(std::string("AuxString")));
			Assert::IsTrue(f[std::string("AuxInt")] == f2[std::string("AuxInt")]);
			Assert::IsTrue(f[std::string("AuxFloat")] == f2[std::string("AuxFloat")]);
			Assert::IsTrue(f[std::string("AuxVector")] == f2[std::string("AuxVector")]);
			Assert::IsTrue(f[std::string("AuxMatrix")] == f2[std::string("AuxMatrix")]);
			Assert::IsTrue(f[std::string("AuxString")] == f2[std::string("AuxString")]);
		}

		TEST_METHOD(AttributedTestAddAttributes)
		{
			AttributedFoo f;
			Assert::IsTrue(f.IsPrescribedAttribute("Int"));
			Assert::IsFalse(f.IsPrescribedAttribute("Int2"));

			f.AppendAuxiliaryAttribute("AuxInt") = 8;
			Assert::IsTrue(f.IsAuxiliaryAttribute("AuxInt"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("AuxInt2"));
			Assert::AreEqual(f.AuxiliaryBegin(), 14U);
		}

	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState AttributedTest::sStartMemState;
#endif
}