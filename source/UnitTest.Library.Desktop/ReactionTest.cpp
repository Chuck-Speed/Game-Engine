#include "pch.h"
#include "FooEntity.h"
#include "FooAction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{

	TEST_CLASS(ReactionTest)
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

		TEST_METHOD(ReactionParseTest)
		{
			Scope s;
			FooEntity::FooEntityFactory feFactory;
			ActionListFactory alFactory;
			ActionListIfFactory alifFactory;
			ActionEventFactory aeFactory;
			FooActionFactory faFactory;
			ReactionAttributedFactory raFactory;

			XMLParseHelperTable::SharedData eSharedData(s);
			XMLParseMaster parseMaster(eSharedData);
			XMLParseHelperEntity entityHelper;
			XMLParseHelperAction actionHelper;
			XMLParseHelperReaction reactionHelper;
			XMLParseHelperReaction* clone = reactionHelper.Clone();

			parseMaster.AddHelper(entityHelper);
			parseMaster.AddHelper(actionHelper);
			parseMaster.AddHelper(reactionHelper);
			parseMaster.ParseFromFile("Content/ParseReaction.xml");

			World* world = eSharedData.GetScopeData()->As<World>();
			Assert::IsTrue(world != nullptr);
			Assert::AreEqual(world->Name(), std::string("MyWorld"));

			WorldState* wState = world->GetWorldState();
			Assert::IsTrue(wState != nullptr);
			world->Update();

			Datum& sectors = world->Sectors();
			Sector* s1 = sectors.Get<Scope*>()->As<Sector>();
			Datum& s1_Entities = s1->Entities();
			Entity* e = s1_Entities.Get<Scope*>()->As<Entity>();

			Datum& actions = e->Actions();
			ActionEvent* actionEvent = actions.Get<Scope*>()->As<ActionEvent>();
			Assert::AreEqual(actionEvent->Name(), std::string("DoTheThing"));
			Assert::IsTrue(actionEvent->Find("Subtype") != nullptr);
			Assert::IsTrue(actionEvent->Find("RandomInt") != nullptr);
			Assert::IsTrue(actionEvent->Find("Delay") != nullptr);

			Datum* reaction = e->Find("TheThing");
			Assert::IsTrue(reaction != nullptr);

			Event<EventMessageAttributed>::UnsubscribeAll();
			delete clone;
			delete world;
		}

		TEST_METHOD(ReactionDeliveryTest)
		{
			World* world = new World();
			WorldState* wState = world->GetWorldState();
			world->Update();
			ActionEvent aEvent;
			ReactionAttributedFactory raf;
			Reaction* reaction = Factory<Reaction>::Create("ReactionAttributed");
			Assert::IsTrue(reaction != nullptr);
			ReactionAttributed* reactionAtt = reaction->As<ReactionAttributed>();
			Assert::IsTrue(reaction != nullptr);

			EventMessageAttributed ema("subtype", world);
			ema.SetSubtype("newtype");
			ema.SetWorld(nullptr);
			Assert::IsTrue(ema.GetSubtype() != "subtype");
			Assert::IsTrue(ema.GetWorld() != world);

			aEvent.Find("Subtype")->Set("TheThing");
			aEvent.Find("Delay")->Set(0);
			Datum& AuxDatum1 = aEvent.AppendAuxiliaryAttribute("Aux1");
			Datum& AuxDatum2 = aEvent.AppendAuxiliaryAttribute("Aux2");
			aEvent.Find("Aux1")->Set(1.0f);
			aEvent.Find("Aux2")->Set("two");

			Datum subType;
			subType = "TheThing";
			reactionAtt->SetSubtype(subType);
			Assert::IsTrue(reactionAtt->GetSubtype() == subType);

			aEvent.Update(*wState);
			world->Update();
			world->GetEventQueue().Update(wState->GetGameTime());
			
			Assert::IsTrue(reactionAtt->Find("Aux1") != nullptr);
			Assert::IsTrue(reactionAtt->Find("Aux2") != nullptr);
			Assert::IsTrue(*reactionAtt->Find("Aux1") == AuxDatum1);
			Assert::IsTrue(*reactionAtt->Find("Aux2") == AuxDatum2);

			Event<EventMessageAttributed>::UnsubscribeAll();
			delete reaction;
			delete world;
		}

		TEST_METHOD(ReactionRTTITest)
		{
			ReactionAttributed* reaction = new ReactionAttributed();
			std::uint64_t ID = ReactionAttributed::TypeIdClass();
			RTTI* dummyPtr = nullptr;

			Assert::IsTrue(reaction->TypeIdInstance() == ID);
			Assert::IsTrue(ReactionAttributed::TypeName() == "Reaction");
			Assert::IsTrue(reaction->Is(ID));
			Assert::IsTrue(reaction->Is("Reaction"));

			RTTI* Query = reaction->QueryInterface(ID);
			Assert::IsTrue(Query->Is("Reaction"));
			Assert::IsTrue(Query->As<ReactionAttributed>() != nullptr);
			Assert::IsFalse(Query->Equals(dummyPtr));
			std::string dataString = reaction->ToString();
			Query = reaction->QueryInterface(0);
			Assert::IsTrue(reaction->Equals(reaction));
			Assert::IsTrue(Query == nullptr);

			ActionEvent* action = new ActionEvent();
			ID = ActionEvent::TypeIdClass();

			Assert::IsTrue(action->TypeIdInstance() == ID);
			Assert::IsTrue(ActionEvent::TypeName() == "ActionEvent");
			Assert::IsTrue(action->Is(ID));
			Assert::IsTrue(action->Is("ActionEvent"));

			Query = action->QueryInterface(ID);
			Assert::IsTrue(Query->Is("ActionEvent"));
			Assert::IsTrue(Query->As<ActionEvent>() != nullptr);
			Assert::IsFalse(Query->Equals(dummyPtr));
			dataString = action->ToString();
			Query = action->QueryInterface(0);
			Assert::IsTrue(action->Equals(action));
			Assert::IsTrue(Query == nullptr);

			EventMessageAttributed* ema = new EventMessageAttributed("testType");
			ID = EventMessageAttributed::TypeIdClass();

			Assert::IsTrue(ema->TypeIdInstance() == ID);
			Assert::IsTrue(EventMessageAttributed::TypeName() == "EventMessageAttributed");
			Assert::IsTrue(ema->Is(ID));
			Assert::IsTrue(ema->Is("EventMessageAttributed"));

			Query = ema->QueryInterface(ID);
			Assert::IsTrue(Query->Is("EventMessageAttributed"));
			Assert::IsTrue(Query->As<EventMessageAttributed>() != nullptr);
			Assert::IsFalse(Query->Equals(dummyPtr));
			dataString = ema->ToString();
			Query = ema->QueryInterface(0);
			Assert::IsTrue(ema->Equals(ema));
			Assert::IsTrue(Query == nullptr);

			Event<EventMessageAttributed>::UnsubscribeAll();
			delete action;
			delete ema;
			delete reaction;
		}
	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState ReactionTest::sStartMemState;
#endif
}