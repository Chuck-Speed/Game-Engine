#include "pch.h"
#include "FooSubscriber.h"
#include "EMASubscriber.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{

	TEST_CLASS(EventTest)
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

		TEST_METHOD(EventConstructorsTest)
		{
			World* world = new World();

			int message = 1;
			int message2 = 2;
			Event<int> e = Event<int>(message);
			e.SetTime(world->GetWorldState()->GetGameTime().CurrentTime(), std::chrono::milliseconds(60000));

			Event<int> e2(e);
			Assert::IsTrue(e2.Message() == e.Message());

			Event<int> e3(std::move(e));
			Assert::IsTrue(e3.Message() == e.Message());

			Event<int> e4(message2);
			e4 = std::move(e3);
			Assert::IsTrue(e3.Message() == e4.Message());

			Vector<EventSubscriber*> eSubs;
			std::mutex eMutex;
			std::mutex eMutex2;
			EventPublisher ePub(eSubs, &eMutex);
			EventPublisher ePub2(ePub);
			EventPublisher ePub3(std::move(ePub));
			EventPublisher ePub4(eSubs, &eMutex2);
			ePub4 = std::move(ePub2);
			Assert::IsTrue(ePub4.Delay() == ePub2.Delay());
			Assert::IsTrue(ePub4.Delay() == ePub3.Delay());

			delete world;
		}

		TEST_METHOD(EventPublisherTest)
		{
			World* world = new World();
			world->Update();

			FooSubscriber fooSub;
			FooSubscriber fooSub2;
			Event<int>::Subscribe(&fooSub);
			Event<int>::Subscribe(&fooSub2);
			EventQueue& eQ = world->GetEventQueue();

			int message = 1;
			std::shared_ptr<Event<int>> e = std::make_shared<Event<int>>(message);
			std::chrono::high_resolution_clock::time_point enqueueTime = world->GetWorldState()->GetGameTime().CurrentTime();
			eQ.Enqueue(e, world->GetWorldState()->GetGameTime(), std::chrono::milliseconds(100));
			Assert::IsTrue(enqueueTime == e->TimeEnqueued());
			Assert::IsTrue(std::chrono::milliseconds(100) == e->Delay());

			Event<int>::Unsubscribe(&fooSub);
			Event<int>::UnsubscribeAll();
			delete world;
		}

		TEST_METHOD(EventSendTest)
		{
			EventQueue eQ;
			Vector<EventSubscriber*> eSubs;
			FooSubscriber fooSub;
			eSubs.PushBack(&fooSub);
			std::mutex eMutex;
			std::mutex* pMutex = &eMutex;
			std::shared_ptr<EventPublisher> e = std::make_shared<EventPublisher>(eSubs, pMutex);
			Assert::ExpectException<std::exception>([&]
			{
				eQ.Send(e);
			});
		}

		TEST_METHOD(EventQueueTest)
		{
			World* world = new World();
			world->Update();

			FooSubscriber fooSub;
			EventQueue& eQ = world->GetEventQueue();
			int message = 1;
			int message2 = 2;
			int message3 = 3;
			std::shared_ptr<Event<int>> e = std::make_shared<Event<int>>(message);
			std::shared_ptr<Event<int>> e2 = std::make_shared<Event<int>>(message2);
			std::shared_ptr<Event<int>> e3 = std::make_shared<Event<int>>(message3);

			Event<int>::Subscribe(&fooSub);
			eQ.Enqueue(e, world->GetWorldState()->GetGameTime());
			eQ.Enqueue(e2, world->GetWorldState()->GetGameTime(), std::chrono::milliseconds(1000));
			eQ.Enqueue(e3, world->GetWorldState()->GetGameTime(), std::chrono::milliseconds(3000));
			Assert::AreEqual(3U, eQ.Size());

			world->Update();
			Assert::AreEqual(message, fooSub.mData);
			Assert::AreEqual(2U, eQ.Size());

			eQ.Clear();
			Assert::IsTrue(eQ.IsEmpty());

			Event<int>::UnsubscribeAll();
			delete world;
		}

		TEST_METHOD(EventRTTITest)
		{
			int message = 1;
			Event<int>* e = new Event<int>(message);
			RTTI* pRTTI = e;
			std::uint64_t ID = Event<int>::TypeIdClass();
			RTTI* dummyPtr = nullptr;

			Assert::IsTrue(pRTTI->TypeIdInstance() == ID);
			Assert::IsTrue(Event<int>::TypeName() == "Event<T>");
			Assert::IsTrue(e->Is(ID));
			Assert::IsTrue(e->Is("Event<T>"));

			RTTI* Query = e->QueryInterface(ID);
			Assert::IsTrue(Query->Is("Event<T>"));
			Assert::IsTrue(Query->As<Event<int>>() != nullptr);
			Assert::IsFalse(Query->Equals(dummyPtr));
			std::string dataString = e->ToString();
			Query = e->QueryInterface(0);
			Assert::IsTrue(Query == nullptr);

			e->As<EventPublisher>();
			RTTI* pRTTI2 = e;
			std::uint64_t ID2 = EventPublisher::TypeIdClass();

			Assert::IsTrue(pRTTI2->TypeIdInstance() == ID);
			Assert::IsTrue(EventPublisher::TypeName() == "EventPublisher");
			Assert::IsTrue(e->Is(ID2));
			Assert::IsTrue(e->Is("EventPublisher"));

			Query = e->QueryInterface(ID2);
			Assert::IsTrue(Query->Is("EventPublisher"));
			Assert::IsTrue(Query->As<EventPublisher>() != nullptr);
			Assert::IsFalse(Query->Equals(dummyPtr));
			dataString = e->ToString();
			Query = e->QueryInterface(0);
			Assert::IsTrue(Query == nullptr);
			delete e;
		}

		TEST_METHOD(EventAsyncTest)
		{
			World* world = new World();
			world->Update();

			EMASubscriber emaSubs[250];
			FooSubscriber fooSubs[250];
			for (uint32_t i = 0; i < 250; ++i)
			{
				Event<EventMessageAttributed>::Subscribe(&emaSubs[i]);
				Event<float>::Subscribe(&fooSubs[i]);
			}

			EventQueue& eQ = world->GetEventQueue();

			float message = 0.0f;
			EventMessageAttributed newEMA("DefaultSubType", world);
			std::shared_ptr<Event<float>> e = std::make_shared<Event<float>>(message);
			std::shared_ptr<Event<EventMessageAttributed>> ema = std::make_shared<Event<EventMessageAttributed>>(newEMA);

			eQ.Enqueue(e, world->GetWorldState()->GetGameTime(), std::chrono::milliseconds());
			eQ.Enqueue(ema, world->GetWorldState()->GetGameTime(), std::chrono::milliseconds());
			
			Assert::ExpectException<std::exception>([&]
			{
				eQ.Update(world->GetWorldState()->GetGameTime());
			});

			Assert::ExpectException<std::exception>([&]
			{
				world->Update();
			});

			Assert::ExpectException<std::exception>([&]
			{
				world->Update();
			});

			Event<float>::UnsubscribeAll();
			world->Update();

			Event<EventMessageAttributed>::UnsubscribeAll();
			delete world;
		}
	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState EventTest::sStartMemState;
#endif
}