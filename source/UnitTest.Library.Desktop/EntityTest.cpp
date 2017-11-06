#include "pch.h"
#include "FooEntity.h"
#include "FooAction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{

	TEST_CLASS(EntityTest)
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

		TEST_METHOD(XMLParseTestHelperEntity)
		{
			Scope s;
			FooEntity::FooEntityFactory feFactory;
			ActionListFactory alFactory;
			ActionListIfFactory alifFactory;
			FooActionFactory faFactory;

			XMLParseHelperTable::SharedData eSharedData(s);
			XMLParseMaster parseMaster(eSharedData);
			XMLParseHelperEntity entityHelper;
			XMLParseHelperAction actionHelper;
			XMLParseHelperEntity* clone = entityHelper.Clone();

			parseMaster.AddHelper(entityHelper);
			parseMaster.AddHelper(actionHelper);
			parseMaster.ParseFromFile("Content/ParseEntity.xml");

			World* world = eSharedData.GetScopeData()->As<World>();
			Assert::IsTrue(world != nullptr);
			Assert::AreEqual(world->Name(), std::string("MyWorld"));

			WorldState* wState = world->GetWorldState();
			Assert::IsTrue(wState != nullptr);
			world->Update();
			wState->SetGameTime(wState->GetGameTime());

			Datum& sectors = world->Sectors();
			Sector* s1 = sectors.Get<Scope*>(0)->As<Sector>();
			Sector* s2 = sectors.Get<Scope*>(1)->As<Sector>();
			Assert::AreEqual(s1->Name(), std::string("Sector1"));
			Assert::AreEqual(s2->Name(), std::string("Sector2"));

			Datum& s1_Entities = s1->Entities();
			Datum& s2_Entities = s2->Entities();
			Entity* e1 = s1_Entities.Get<Scope*>(0)->As<Entity>();
			Entity* e2 = s2_Entities.Get<Scope*>(0)->As<Entity>();
			Entity* e3 = s2_Entities.Get<Scope*>(1)->As<Entity>();
			Assert::AreEqual(e1->Name(), std::string("first"));
			Assert::AreEqual(e2->Name(), std::string("second"));
			Assert::AreEqual(e3->Name(), std::string("third"));

			Assert::AreEqual(e1->Find("number")->Get<int>(), 1);
			Assert::AreEqual(e3->Find("Thing1")->Get<float>(), 1.0f);
			Assert::AreEqual(e3->Find("Thing2")->Get<int>(), 2);
			Assert::AreEqual(e3->Find("mFoo")->Get<std::string>(), std::string("FooBar"));
			Assert::AreEqual(e3->Find("myVector")->ToString(), std::string("vec4(1.000000, 2.000000, 3.000000, 4.000000)"));
			Assert::AreEqual(e3->Find("myMatrix")->ToString(), std::string("mat4x4((1.000000, 2.000000, 3.000000, 4.000000), (5.000000, 6.000000, 7.000000, 8.000000), (9.000000, 10.000000, 11.000000, 12.000000), (13.000000, 14.000000, 15.000000, 16.000000))"));

			parseMaster.RemoveHelper(entityHelper);
			delete clone;
			delete world;
		}

	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState EntityTest::sStartMemState;
#endif
}