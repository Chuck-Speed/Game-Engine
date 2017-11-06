#include "pch.h"
#include "FooEntity.h"
#include "FooAction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{

	TEST_CLASS(ActionTest)
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

		TEST_METHOD(XMLParseTestHelperAction)
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
			XMLParseHelperAction* clone = actionHelper.Clone();

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
			Sector* s2 = sectors.Get<Scope*>(1)->As<Sector>();
			Datum& s2_Entities = s2->Entities();
			Entity* e3 = s2_Entities.Get<Scope*>(1)->As<Entity>();

			Datum& actions = e3->Actions();
			ActionListIf* actionIf = actions.Get<Scope*>()->As<ActionListIf>();
			Assert::AreEqual(actionIf->Name(), std::string("LightsCameraAction"));

			Datum* actionList = actionIf->Find("ActionEntries");
			Datum& actions2 = actionList->Get<Scope*>()->As<ActionList>()->Actions();
			Assert::IsTrue(actions2.Size() != 0);

			actionIf->SetCondition(0);
			world->Update();

			delete clone;
			delete world;
		}

	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState ActionTest::sStartMemState;
#endif
}