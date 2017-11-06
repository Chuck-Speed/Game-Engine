#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{

	TEST_CLASS(ScopeTest)
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
		class RTTIClass : public Scope{};

		TEST_METHOD(ScopeTestConstructor)
		{
			Scope s;
			s.Append("Hello!");
			s.AppendScope("Hello!");
			s.AppendScope("Hello!");
		}

		TEST_METHOD(ScopeTestCopy)
		{
			Scope s;
			s.Append("Hello!");
			s.Append("Test!");
			s.AppendScope("Scope!");
			Scope sCopy(s);
			Assert::IsTrue(s == sCopy);
		}

		TEST_METHOD(ScopeTestFind)
		{
			Scope s;
			Scope s2;
			Datum* datum = s.Find("Test!");
			Assert::IsTrue(datum == nullptr);

			s2.Append("Test!");
			Datum* datum2 = s2.Find("Test!");
			Assert::IsTrue(datum2 != nullptr);
			Assert::IsTrue(datum2->Type() == Datum::DatumType::UNKNOWN);
		}

		TEST_METHOD(ScopeTestSearch)
		{
			Scope s;
			s.Append("0");
			Scope& s2 = s.AppendScope("1");
			Scope& s3 = s2.AppendScope("2");
			Scope& s4 = s3.AppendScope("3");
			Scope& s5 = s4.AppendScope("4");

			const Scope* results = nullptr;
			Datum* datum = s5.Search("0", &results);
			
			Assert::IsTrue(datum != nullptr);
			Assert::IsTrue(*results == s);
		}

		TEST_METHOD(ScopeTestFindName)
		{
			Scope s;
			Scope s2;
			Scope& s3 = s2.AppendScope("Test");
			std::string result = s.FindName(s2);
			Assert::IsTrue(result.empty());

			result = s2.FindName(s3);
			Assert::IsTrue(result == "Test");
		}

		TEST_METHOD(ScopeTestAppend)
		{
			Scope s;
			Datum& datum = s.Append("Test");
			Datum& datum2 = s.Append("Test");
			Assert::IsTrue(datum == datum2);
		}

		TEST_METHOD(ScopeTestAppendScope)
		{
			Scope s;
			Scope s2;
			Datum datum(Datum::DatumType::INTEGER);
			s.AppendScope("Test");
			s.AppendScope("Test");
			Datum& datum2 = s2.Append("Invalid");
			datum2.SetType(Datum::DatumType::INTEGER);

			s.Adopt(s2, "Invalid");
			auto expression = [&] {s2.AppendScope("Invalid"); };
			Assert::ExpectException<std::exception>(expression);
		}

		TEST_METHOD(ScopeTestOrphan)
		{
			Scope s;
			Scope s2 = s.AppendScope("Test");
			
			s.Orphan();
			s2.Orphan();
			Assert::IsTrue(s2.GetParent() == nullptr);

			s.Adopt(s2, "Test");
			s2.Orphan();
			Assert::IsTrue(s2.GetParent() == nullptr);
		}

		TEST_METHOD(ScopeTestAdopt)
		{
			Scope s;
			Scope s2;
			s2.Append("Test");
			s.Adopt(s2, "Test");
		}

		TEST_METHOD(ScopeTestRTTI)
		{
			Scope s;
			s.Append("Test");
			s.AppendScope("Test2");
			s.AppendScope("Test2");
			Scope s2 = s;
			RTTI* pRTTI = &s;
			std::uint64_t ID = Scope::TypeIdClass();

			Assert::IsTrue(pRTTI->TypeIdInstance() == ID);
			Assert::IsTrue(Scope::TypeName() == "Scope");
			Assert::IsTrue(s.Is(ID));
			Assert::IsTrue(s.Is("Scope"));

			RTTIClass test;
			Assert::IsTrue(test.Is("Scope"));
			Assert::IsTrue(test.Is(ID));

			RTTI* Query = s.QueryInterface(ID);
			Assert::IsTrue(Query->Is("Scope"));
			std::string scopeString = s.ToString();
			Query = s.QueryInterface(0);
			Assert::IsTrue(Query == nullptr);

		}

		TEST_METHOD(ScopeTestBracket)
		{
			Scope s;
			auto expression = [&] { s[20]; };
			Assert::ExpectException<std::out_of_range>(expression);

			Datum& datum = s.Append("Test");
			Assert::IsTrue(s[0] == datum);
		}

		TEST_METHOD(ScopeTestClear)
		{
			Scope s;
			s.AppendScope("Test");
			s.Append("Test2");
			s.AppendScope("Test3");
			s.Clear();
		}

	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState ScopeTest::sStartMemState;
#endif
}