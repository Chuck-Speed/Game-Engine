#include "pch.h"
#include "FooEntity.h"
#include "FooAction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{

	TEST_CLASS(XMLParseTest)
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

		TEST_METHOD(XMLParseTestMaster)
		{
			XMLParseMaster::SharedData sharedData;
			XMLParseMaster p(sharedData);
			XMLParseHelperFoo helper;

			p.AddHelper(helper);
			p.ParseFromFile("Content/ParseTest.xml");
			Assert::AreEqual(0U, sharedData.Depth());
			Assert::AreEqual(std::string("Content/ParseTest.xml"), p.GetFileName());

			XMLParseMaster* clone = p.Clone();
			auto expression = [&] { clone->AddHelper(helper); };
			Assert::ExpectException<std::exception>(expression);

			auto expression2 = [&] { clone->RemoveHelper(helper); };
			Assert::ExpectException<std::exception>(expression2);

			auto expression3 = [&] { sharedData.DecrementDepth(); };
			Assert::ExpectException<std::exception>(expression3);
			
			delete clone;

			XMLParseMaster::SharedData sharedData2;
			sharedData2.IncrementDepth();

			p.RemoveHelper(helper);
			p.SetSharedData(sharedData2);
			Assert::IsTrue(&sharedData2 == &p.GetSharedData());
		}

		TEST_METHOD(XMLParseTestHelperFoo)
		{
			XMLParseHelperFoo::SharedData sharedDataFoo;
			XMLParseMaster pFoo(sharedDataFoo);
			XMLParseHelperFoo helper;
			pFoo.AddHelper(helper);
			pFoo.ParseFromFile("Content/ParseTest.xml");

			auto pair = sharedDataFoo.GetData();
			Assert::AreEqual(std::string("stat"), pair.first);
			Assert::AreEqual(std::string("power"), pair.second);
			Assert::AreEqual(10, sharedDataFoo.GetPower());

			XMLParseMaster* clone = pFoo.Clone();
			delete clone;

			pFoo.RemoveHelper(helper);
		}

		TEST_METHOD(XMLParseTestRTTI)
		{
			XMLParseHelperFoo::SharedData sharedData;
			RTTI* pRTTI = &sharedData;
			std::uint64_t ID = XMLParseHelperFoo::SharedData::TypeIdClass();
			RTTI* dummyPtr = nullptr;

			Assert::IsTrue(pRTTI->TypeIdInstance() == ID);
			Assert::IsTrue(XMLParseHelperFoo::SharedData::TypeName() == "SharedData");
			Assert::IsTrue(sharedData.Is(ID));
			Assert::IsTrue(sharedData.Is("SharedData"));

			RTTI* Query = sharedData.QueryInterface(ID);
			Assert::IsTrue(Query->Is("SharedData"));
			Assert::IsTrue(Query->As<XMLParseHelperFoo::SharedData>() != nullptr);
			Assert::IsFalse(Query->Equals(dummyPtr));
			std::string dataString = sharedData.ToString();
			Query = sharedData.QueryInterface(0);
			Assert::IsTrue(Query == nullptr);

			Scope* s = new Scope();
			XMLParseHelperTable::SharedData sharedTableData(*s);
			RTTI* p2_RTTI = &sharedTableData;
			std::uint64_t ID2 = XMLParseHelperTable::SharedData::TypeIdClass();

			Assert::IsTrue(p2_RTTI->TypeIdInstance() == ID2);
			Assert::IsTrue(XMLParseHelperTable::SharedData::TypeName() == "SharedData");
			Assert::IsTrue(sharedTableData.Is(ID2));
			Assert::IsTrue(sharedTableData.Is("SharedData"));

			Query = sharedTableData.QueryInterface(ID2);
			Assert::IsTrue(Query->Is("SharedData"));
			Assert::IsTrue(Query->As<XMLParseHelperTable::SharedData>() != nullptr);
			Assert::IsFalse(Query->Equals(dummyPtr));
			dataString = sharedTableData.ToString();
			Query = sharedTableData.QueryInterface(0);
			Assert::IsTrue(Query == nullptr);

			ActionList* a = new ActionList();
			std::uint64_t ID3 = ActionList::TypeIdClass();

			Assert::IsTrue(a->TypeIdInstance() == ID3);
			Assert::IsTrue(ActionList::TypeName() == "ActionList");
			Assert::IsTrue(a->Is(ID3));
			Assert::IsTrue(a->Is("ActionList"));

			Query = a->QueryInterface(ID3);
			Assert::IsTrue(Query->Is("ActionList"));
			Assert::IsTrue(Query->As<ActionList>() != nullptr);
			Assert::IsFalse(Query->Equals(dummyPtr));
			dataString = a->ToString();
			Query = a->QueryInterface(0);
			Assert::IsTrue(Query == nullptr);

			delete a;
			delete s;
		}

		TEST_METHOD(XMLParseTestHelperTable)
		{
			Scope* testScope = new Scope();
			XMLParseHelperTable::SharedData sharedData(*testScope);
			XMLParseMaster pTable(sharedData);
			XMLParseHelperTable helper;
			pTable.AddHelper(helper);

			XMLParseMaster* clone = pTable.Clone();
			XMLParseHelperTable::SharedData* dataClone = sharedData.Clone();

			std::string input = std::string("<Scope name = \"root\"><Integer name = \"myInt\" index = \"0\" value = \"8\"/></Scope>");
			pTable.Parse(input.c_str(), static_cast<uint32_t>(input.length()), true);

			Scope* s = sharedData.GetScopeData();
			Assert::IsTrue (s != nullptr);

			Assert::AreEqual(8, (*s)["myInt"].Get<int>());
			pTable.Reset();
			helper.Initialize();

			input = std::string("<Scope name = \"root\"><Float name = \"myFloatArray\" index = \"2\" value = \"7.8\"/><Float name = \"myFloatArray\" index = \"1\" value = \"8.8\"/><Float name = \"myFloatArray\" index = \"2\" value = \"9.8\"/></Scope>");
			pTable.Parse(input.c_str(), static_cast<uint32_t>(input.length()), true);

			Datum* datum = sharedData.GetScopeData()->Find("myFloatArray");
			Assert::IsTrue(datum != nullptr);

			s = sharedData.GetScopeData();
			Assert::IsTrue(s != nullptr);

			Assert::AreEqual(7.8f, (*s)["myFloatArray"].Get<float>(0));
			Assert::AreEqual(8.8f, (*s)["myFloatArray"].Get<float>(1));
			Assert::AreEqual(9.8f, (*s)["myFloatArray"].Get<float>(2));

			pTable.Reset();
			helper.Initialize();

			pTable.ParseFromFile("Content/ParseTable.xml");
			s = sharedData.GetScopeData();
			Assert::IsTrue(s != nullptr);
			Assert::AreEqual(8, (*s)["myInt"].Get<int>());

			Scope* child = (*s)["Scope Jr."].Get<Scope*>();
			Assert::AreEqual((*child)["myString"].Get<std::string>(), std::string("Oppah!"));
			Assert::AreEqual((*child)["myVector"].ToString(), std::string("vec4(1.000000, 2.000000, 3.000000, 4.000000)"));
			Assert::AreEqual((*child)["myMatrix"].ToString(), std::string("mat4x4((1.000000, 2.000000, 3.000000, 4.000000), (5.000000, 6.000000, 7.000000, 8.000000), (9.000000, 10.000000, 11.000000, 12.000000), (13.000000, 14.000000, 15.000000, 16.000000))"));

			delete clone;
			delete dataClone;
			delete testScope;
		}
	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState XMLParseTest::sStartMemState;
#endif
}