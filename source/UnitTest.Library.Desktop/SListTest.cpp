#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(SListTest)
	{
	public:

		TEST_METHOD(SListTestConstructor)
		{
			SList<int> intList;
			SList<int*> pIntList;
			SList<Foo> FooList;
			uint32_t size = 0;

			Assert::AreEqual(intList.Size(), size);
			Assert::AreEqual(pIntList.Size(), size);
			Assert::AreEqual(FooList.Size(), size);
			Assert::ExpectException<std::exception>([&] {return intList.Front(); });
			Assert::ExpectException<std::exception>([&] {return pIntList.Front(); });
			Assert::ExpectException<std::exception>([&] {return FooList.Front(); });
			Assert::ExpectException<std::exception>([&] {return intList.Back(); });
			Assert::ExpectException<std::exception>([&] {return pIntList.Back(); });
			Assert::ExpectException<std::exception>([&] {return FooList.Back(); });
		}


		TEST_METHOD(SListTestPushFront)
		{
			SList<int> intList;
			SList<int*> pIntList;
			SList<Foo> FooList;

			int testInts[2] = { 1337, 100 };
			Foo testFoos[2] = { Foo(testInts[0]), Foo(testInts[1]) };

			//Tests pushing to empty list branch
			intList.PushFront(testInts[0]);
			pIntList.PushFront(&testInts[0]);
			FooList.PushFront(testFoos[0]);

			Assert::AreEqual(intList.Front(), testInts[0]);
			Assert::AreEqual(pIntList.Front(), &testInts[0]);
			Assert::AreEqual(FooList.Front().Data(), testFoos[0].Data());
			Assert::AreEqual(intList.Front(), intList.Back());
			Assert::AreEqual(pIntList.Front(), pIntList.Back());
			Assert::AreEqual(FooList.Front().Data(), FooList.Back().Data());

			//Tests pushing to non-empty list branch
			intList.PushFront(testInts[1]);
			pIntList.PushFront(&testInts[1]);
			FooList.PushFront(testFoos[1]);
			Assert::AreNotEqual(intList.Front(), testInts[0]);
			Assert::AreNotEqual(pIntList.Front(), &testInts[0]);
			Assert::AreNotEqual(FooList.Front().Data(), testFoos[0].Data());
		}

		TEST_METHOD(SListTestPushBack)
		{
			SList<int> intList;
			SList<int*> pIntList;
			SList<Foo> FooList;

			int testInts[2] = { 1337, 100 };
			Foo testFoos[2] = { Foo(testInts[0]), Foo(testInts[1]) };

			//Tests pushing to empty list branch
			intList.PushBack(testInts[0]);
			pIntList.PushBack(&testInts[0]);
			FooList.PushBack(testFoos[0]);

			Assert::AreEqual(intList.Back(), testInts[0]);
			Assert::AreEqual(pIntList.Back(), &testInts[0]);
			Assert::AreEqual(FooList.Front().Data(), testFoos[0].Data());

			Assert::AreEqual(intList.Back(), intList.Back());
			Assert::AreEqual(pIntList.Back(), pIntList.Back());
			Assert::AreEqual(FooList.Back().Data(), FooList.Back().Data());

			//Tests pushing to non-empty list branch
			intList.PushBack(testInts[1]);
			pIntList.PushBack(&testInts[1]);
			FooList.PushBack(testFoos[1]);

			Assert::AreNotEqual(intList.Back(), testInts[0]);
			Assert::AreNotEqual(pIntList.Back(), &testInts[0]);
			Assert::AreNotEqual(FooList.Back().Data(), testFoos[0].Data());
		}


		TEST_METHOD(SListTestIsEmpty)
		{
			SList<int> intList;
			SList<int*> pIntList;
			SList<Foo> FooList;

			int testInt = 1337;
			Foo testFoo(testInt);

			Assert::IsTrue(intList.IsEmpty());
			Assert::IsTrue(pIntList.IsEmpty());
			Assert::IsTrue(FooList.IsEmpty());

			intList.PushBack(testInt);
			pIntList.PushBack(&testInt);
			FooList.PushBack(testFoo);
			intList.PushFront(testInt);
			pIntList.PushFront(&testInt);
			FooList.PushFront(testFoo);
			intList.PushFront(testInt);
			pIntList.PushFront(&testInt);
			FooList.PushFront(testFoo);
			intList.PushBack(testInt);
			pIntList.PushBack(&testInt);
			FooList.PushBack(testFoo);

			Assert::IsFalse(intList.IsEmpty());
			Assert::IsFalse(pIntList.IsEmpty());
			Assert::IsFalse(FooList.IsEmpty());

			intList.PopFront();
			pIntList.PopFront();
			FooList.PopFront();

			Assert::IsFalse(intList.IsEmpty());
			Assert::IsFalse(pIntList.IsEmpty());
			Assert::IsFalse(FooList.IsEmpty());

			intList.Clear();
			pIntList.Clear();
			FooList.Clear();

			Assert::IsTrue(intList.IsEmpty());
			Assert::IsTrue(pIntList.IsEmpty());
			Assert::IsTrue(FooList.IsEmpty());
		}

		TEST_METHOD(SListTestFront)
		{
			SList<int> intList;
			SList<int*> pIntList;
			SList<Foo> FooList;

			int testInt = 1337;
			Foo testFoo(testInt);

			Assert::ExpectException<std::exception>([&] {return intList.Front(); });
			Assert::ExpectException<std::exception>([&] {return pIntList.Front(); });
			Assert::ExpectException<std::exception>([&] {return FooList.Front(); });

			intList.PushFront(testInt);
			pIntList.PushFront(&testInt);
			FooList.PushFront(testFoo);

			Assert::AreEqual(intList.Front(), testInt);
			Assert::AreEqual(pIntList.Front(), &testInt);
			Assert::AreEqual(FooList.Front().Data(), testFoo.Data());
		}

		TEST_METHOD(SListTestBack)
		{
			SList<int> intList;
			SList<int*> pIntList;
			SList<Foo> FooList;

			int testInt = 1337;
			Foo testFoo(testInt);

			Assert::ExpectException<std::exception>([&] {return intList.Back(); });
			Assert::ExpectException<std::exception>([&] {return pIntList.Back(); });
			Assert::ExpectException<std::exception>([&] {return FooList.Back(); });

			intList.PushBack(testInt);
			pIntList.PushBack(&testInt);
			FooList.PushBack(testFoo);

			Assert::AreEqual(intList.Back(), testInt);
			Assert::AreEqual(pIntList.Back(), &testInt);
			Assert::AreEqual(FooList.Back().Data(), testFoo.Data());
		}

		TEST_METHOD(SListTestPopFront)
		{
			SList<int> intList;
			SList<int*> pIntList;
			SList<Foo> FooList;

			int testInt = 1337;
			unsigned int testSize = 1;
			Foo testFoo(testInt);

			Assert::ExpectException<std::exception>([&] {return intList.PopFront(); });
			Assert::ExpectException<std::exception>([&] {return pIntList.PopFront(); });
			Assert::ExpectException<std::exception>([&] {return FooList.PopFront(); });

			intList.PushFront(testInt);
			pIntList.PushFront(&testInt);
			FooList.PushFront(testFoo);

			Assert::AreEqual(intList.Size(), testSize);
			Assert::AreEqual(pIntList.Size(), testSize);
			Assert::AreEqual(FooList.Size(), testSize);

			intList.PopFront();
			pIntList.PopFront();
			FooList.PopFront();

			Assert::IsTrue(intList.IsEmpty());
			Assert::IsTrue(pIntList.IsEmpty());
			Assert::IsTrue(FooList.IsEmpty());
		}

		TEST_METHOD(SListTestClear)
		{
			SList<int> intList;
			SList<int*> pIntList;
			SList<Foo> FooList;

			int testInt = 1337;
			Foo testFoo(testInt);

			intList.PushFront(testInt);
			intList.PushBack(testInt);
			pIntList.PushFront(&testInt);
			pIntList.PushBack(&testInt);
			FooList.PushFront(testFoo);
			FooList.PushBack(testFoo);

			intList.Clear();
			pIntList.Clear();
			FooList.Clear();

			Assert::IsTrue(intList.IsEmpty());
			Assert::IsTrue(pIntList.IsEmpty());
			Assert::IsTrue(FooList.IsEmpty());
		}

		TEST_METHOD(SListTestSize)
		{
			SList<int> intList;
			SList<int*> pIntList;
			SList<Foo> FooList;

			int testInt = 1337;
			unsigned int testSize = 0;
			Foo testFoo(testInt);

			Assert::AreEqual(intList.Size(), testSize);
			Assert::AreEqual(pIntList.Size(), testSize);
			Assert::AreEqual(FooList.Size(), testSize);

			intList.PushFront(testInt);
			pIntList.PushFront(&testInt);
			FooList.PushFront(testFoo);
			intList.PushBack(testInt);
			pIntList.PushBack(&testInt);
			FooList.PushBack(testFoo);
			testSize+=2;
			Assert::AreEqual(intList.Size(), testSize);
			Assert::AreEqual(pIntList.Size(), testSize);
			Assert::AreEqual(FooList.Size(), testSize);

			intList.PopFront();
			pIntList.PopFront();
			FooList.PopFront();
			testSize--;
			Assert::AreEqual(intList.Size(), testSize);
			Assert::AreEqual(pIntList.Size(), testSize);
			Assert::AreEqual(FooList.Size(), testSize);

			intList.Clear();
			pIntList.Clear();
			FooList.Clear();
			testSize = 0;
			Assert::AreEqual(intList.Size(), testSize);
			Assert::AreEqual(pIntList.Size(), testSize);
			Assert::AreEqual(FooList.Size(), testSize);
		}

		TEST_METHOD(SListTestCopy)
		{
			SList<int> intList;
			SList<int*> pIntList;
			SList<Foo> FooList;

			int testInts[3] = { 55, 77, 100 };
			Foo testFoos[3] = { Foo(testInts[0]), Foo(testInts[1]), Foo(testInts[2]) };

			intList.PushFront(testInts[0]);
			intList.PushBack(testInts[1]);
			intList.PushBack(testInts[2]);
			pIntList.PushFront(&testInts[0]);
			pIntList.PushBack(&testInts[1]);
			pIntList.PushBack(&testInts[2]);
			FooList.PushFront(testFoos[0]);
			FooList.PushBack(testFoos[1]);
			FooList.PushBack(testFoos[2]);

			SList<int> intList2(intList);
			SList<int*> pIntList2(pIntList);
			SList<Foo> FooList2(FooList);

			Assert::AreEqual(intList.Front(), intList2.Front());
			Assert::AreEqual(pIntList.Front(), pIntList2.Front());
			Assert::AreEqual(FooList.Front().Data(), FooList2.Front().Data());

			intList.PopFront();
			intList2.PopFront();
			pIntList.PopFront();
			pIntList2.PopFront();
			FooList.PopFront();
			FooList2.PopFront();

			Assert::AreEqual(intList.Front(), intList2.Front());
			Assert::AreEqual(pIntList.Front(), pIntList2.Front());
			Assert::AreEqual(FooList.Front().Data(), FooList2.Front().Data());

			intList.PopFront();
			intList2.PopFront();
			pIntList.PopFront();
			pIntList2.PopFront();
			FooList.PopFront();
			FooList2.PopFront();

			Assert::AreEqual(intList.Front(), intList2.Front());
			Assert::AreEqual(pIntList.Front(), pIntList2.Front());
			Assert::AreEqual(FooList.Front().Data(), FooList2.Front().Data());

			intList.PopFront();
			intList2.PopFront();
			pIntList.PopFront();
			pIntList2.PopFront();
			FooList.PopFront();
			FooList2.PopFront();

			Assert::ExpectException<std::exception>([&] {return intList.Front(); });
			Assert::ExpectException<std::exception>([&] {return pIntList.Front(); });
			Assert::ExpectException<std::exception>([&] {return FooList.Front(); });
		}

		TEST_METHOD(IteratorTestConstructor)
		{
			SList<int> intList;
			SList<int*> pIntList;
			SList<Foo> FooList;
			SList<int>::Iterator intItr;
			SList<int>::Iterator pIntItr;
			SList<int>::Iterator fooItr;
			//Assert::IsNull(intItr.getOwner());
			//Assert::IsNull(pIntItr.getOwner());
			//Assert::IsNull(fooItr.getOwner());
		}

		TEST_METHOD(IteratorTestCopy)
		{
			SList<int> intList;
			SList<int*> pIntList;
			SList<Foo> FooList;

			int testInt = 1337;
			Foo testFoo(testInt);

			intList.PushFront(testInt);
			pIntList.PushFront(&testInt);
			FooList.PushFront(testFoo);

			SList<int> intList2(intList);
			SList<int*> pIntList2(pIntList);
			SList<Foo> FooList2(FooList);
			SList<int>::Iterator intItr = intList.begin();
			SList<int*>::Iterator pIntItr = pIntList.begin();
			SList<Foo>::Iterator FooItr = FooList.begin();
			SList<int>::Iterator intItr2(intItr);
			SList<int*>::Iterator pIntItr2(pIntItr);
			SList<Foo>::Iterator FooItr2(FooItr);

			Assert::AreEqual(*intItr, *intItr2);
			Assert::AreEqual(*pIntItr, *pIntItr2);
			Assert::AreEqual(FooItr.operator*().Data(), FooItr2.operator*().Data());
		}

		TEST_METHOD(IteratorTestComparison)
		{
			SList<int> intList;
			SList<int*> pIntList;
			SList<Foo> FooList;

			int testInt = 1337;
			Foo testFoo(testInt);

			intList.PushFront(testInt);
			pIntList.PushFront(&testInt);
			FooList.PushFront(testFoo);

			SList<int> intList2(intList);
			SList<int*> pIntList2(pIntList);
			SList<Foo> FooList2(FooList);

			SList<int>::Iterator intItr;
			SList<int*>::Iterator pIntItr;
			SList<Foo>::Iterator FooItr;

			intItr = intList.begin();
			pIntItr = pIntList.begin();
			FooItr = FooList.begin();

			SList<int>::Iterator intItr2(intItr);
			SList<int*>::Iterator pIntItr2(pIntItr);
			SList<Foo>::Iterator FooItr2(FooItr);

			Assert::IsTrue(intItr == intItr2);
			Assert::IsTrue(pIntItr == pIntItr2);
			Assert::IsTrue(FooItr == FooItr2);

			Assert::IsFalse(intItr != intItr2);
			Assert::IsFalse(pIntItr != pIntItr2);
			Assert::IsFalse(FooItr != FooItr2);

			intItr2 = intList.end();
			pIntItr2 = pIntList.end();
			FooItr2 = FooList.end();

			Assert::IsFalse(intItr == intItr2);
			Assert::IsFalse(pIntItr == pIntItr2);
			Assert::IsFalse(FooItr == FooItr2);

			Assert::IsTrue(intItr != intItr2);
			Assert::IsTrue(pIntItr != pIntItr2);
			Assert::IsTrue(FooItr != FooItr2);
		}

		TEST_METHOD(IteratorTestIncrement)
		{
			SList<int> intList;
			SList<int*> pIntList;
			SList<Foo> FooList;

			int testInts[3] = { 1337, 100, 3 };
			Foo testFoos[3] = { Foo(testInts[0]), Foo(testInts[1]) , Foo(testInts[2]) };

			intList.PushFront(testInts[0]);
			pIntList.PushFront(&testInts[0]);
			FooList.PushFront(testFoos[0]);
			intList.PushFront(testInts[1]);
			pIntList.PushFront(&testInts[1]);
			FooList.PushFront(testFoos[1]);
			intList.PushFront(testInts[2]);
			pIntList.PushFront(&testInts[2]);
			FooList.PushFront(testFoos[2]);

			SList<int>::Iterator intItr = intList.begin();
			SList<int*>::Iterator pIntItr = pIntList.begin();
			SList<Foo>::Iterator FooItr = FooList.begin();

			Assert::AreEqual(*(intItr++), testInts[2]);
			Assert::AreEqual(*(++intItr), testInts[0]);
			Assert::AreEqual(*(pIntItr++), &testInts[2]);
			Assert::AreEqual(*(++pIntItr), &testInts[0]);
			Assert::IsTrue(*(FooItr++) == testFoos[2]);
			Assert::IsTrue(*(++FooItr) == testFoos[0]);

			SList<int>::Iterator intItr2;
			SList<int*>::Iterator pIntItr2;
			SList<Foo>::Iterator FooItr2;

			auto expression1 = [&] { intItr2.operator++(); };
			auto expression2 = [&] { pIntItr2.operator++(); };
			auto expression3 = [&] { FooItr2.operator++(); };
			auto expression4 = [&] { intItr2.operator++(0); };
			auto expression5 = [&] { pIntItr2.operator++(0); };
			auto expression6 = [&] { FooItr2.operator++(0); };

			Assert::ExpectException<std::exception>(expression1);
			Assert::ExpectException<std::exception>(expression2);
			Assert::ExpectException<std::exception>(expression3);
			Assert::ExpectException<std::exception>(expression4);
			Assert::ExpectException<std::exception>(expression5);
			Assert::ExpectException<std::exception>(expression6);
		}

		TEST_METHOD(IteratorTestBegin)
		{
			SList<int> intList;
			SList<int*> pIntList;
			SList<Foo> FooList;

			int testInt = 1337;
			Foo testFoo(testInt);

			intList.PushFront(testInt);
			pIntList.PushFront(&testInt);
			FooList.PushFront(testFoo);

			SList<int>::Iterator intItr = intList.begin();
			SList<int*>::Iterator pIntItr = pIntList.begin();
			SList<Foo>::Iterator FooItr = FooList.begin();

			Assert::AreEqual(*intItr, testInt);
			Assert::AreEqual(*pIntItr, &testInt);
			Assert::AreEqual(FooItr.operator*().Data(), testFoo.Data());
		}

		TEST_METHOD(IteratorTestEnd)
		{
			SList<int> intList;
			SList<int*> pIntList;
			SList<Foo> FooList;

			int testInt = 1337;
			int testInt2 = 55;
			Foo testFoo(testInt);
			Foo testFoo2(testInt2);

			intList.PushFront(testInt);
			pIntList.PushFront(&testInt);
			FooList.PushFront(testFoo);
			intList.PushBack(testInt2);
			pIntList.PushBack(&testInt2);
			FooList.PushBack(testFoo2);

			SList<int>::Iterator intItr = intList.end();
			SList<int*>::Iterator pIntItr = pIntList.end();
			SList<Foo>::Iterator FooItr = FooList.end();

			auto expression1 = [&] { intItr.operator*(); };
			auto expression2 = [&] { pIntItr.operator*(); };
			auto expression3 = [&] { FooItr.operator*(); };
			Assert::ExpectException<std::exception>(expression1);
			Assert::ExpectException<std::exception>(expression2);
			Assert::ExpectException<std::exception>(expression3);
		}

		TEST_METHOD(IteratorTestFind)
		{
			SList<int> intList;
			SList<int*> pIntList;
			SList<Foo> FooList;

			int testInts[3] = { 1337, 100, 3 };
			Foo testFoos[3] = { Foo(testInts[0]), Foo(testInts[1]) , Foo(testInts[2]) };

			intList.PushFront(testInts[0]);
			pIntList.PushFront(&testInts[0]);
			FooList.PushFront(testFoos[0]);
			intList.PushBack(testInts[1]);
			pIntList.PushBack(&testInts[1]);
			FooList.PushBack(testFoos[1]);
			intList.PushBack(testInts[2]);
			pIntList.PushBack(&testInts[2]);
			FooList.PushBack(testFoos[2]);

			SList<int>::Iterator intItr = intList.Find(testInts[0]);
			SList<int*>::Iterator pIntItr = pIntList.Find(&testInts[1]);
			SList<Foo>::Iterator FooItr = FooList.Find(testFoos[2]);

			Assert::AreEqual(*intItr, 1337);
			Assert::AreEqual(*pIntItr, &testInts[1]);
			Assert::AreEqual(FooItr.operator*().Data(), 3);
		}

		TEST_METHOD(IteratorTestRemove)
		{
			SList<int> intList;
			SList<int*> pIntList;
			SList<Foo> FooList;

			int testInts[3] = { 1337, 100, 3 };
			Foo testFoos[3] = { Foo(testInts[0]), Foo(testInts[1]) , Foo(testInts[2]) };
			uint32_t testSize = 3;

			intList.Remove(1337);
			pIntList.Remove(&testInts[1]);
			FooList.Remove(testFoos[2]);

			intList.PushFront(testInts[0]);
			pIntList.PushFront(&testInts[0]);
			FooList.PushFront(testFoos[0]);
			intList.PushBack(testInts[1]);
			pIntList.PushBack(&testInts[1]);
			FooList.PushBack(testFoos[1]);
			intList.PushBack(testInts[2]);
			pIntList.PushBack(&testInts[2]);
			FooList.PushBack(testFoos[2]);
			intList.PushFront(testInts[0]);
			pIntList.PushFront(&testInts[0]);
			FooList.PushFront(testFoos[0]);
			intList.PushBack(testInts[1]);
			pIntList.PushBack(&testInts[1]);
			FooList.PushBack(testFoos[1]);
			intList.PushBack(testInts[2]);
			pIntList.PushBack(&testInts[2]);
			FooList.PushBack(testFoos[2]);

			intList.Remove(3);
			pIntList.Remove(&testInts[2]);
			FooList.Remove(testFoos[2]);

			Assert::AreNotEqual(intList.Size(), testSize);
			Assert::AreNotEqual(pIntList.Size(), testSize);
			Assert::AreNotEqual(FooList.Size(), testSize);

			intList.Clear();
			pIntList.Clear();
			FooList.Clear();

			intList.PushFront(testInts[0]);
			pIntList.PushFront(&testInts[0]);
			FooList.PushFront(testFoos[0]);

			intList.Remove(1337);
			pIntList.Remove(&testInts[0]);
			FooList.Remove(testFoos[0]);

			Assert::AreEqual(intList.Size(), 0U);
			Assert::AreEqual(pIntList.Size(), 0U);
			Assert::AreEqual(FooList.Size(), 0U);
		}

		TEST_METHOD(IteratorTestInsert)
		{
			SList<int> intList;
			SList<int*> pIntList;
			SList<Foo> FooList;

			int testInts[3] = { 1337, 100, 3 };
			Foo testFoos[3] = { Foo(testInts[0]), Foo(testInts[1]) , Foo(testInts[2]) };

			SList<int>::Iterator intItr;
			SList<int*>::Iterator pIntItr;
			SList<Foo>::Iterator FooItr;

			auto expression1 = [&] { intList.InsertAfter(intItr, testInts[0]); };
			auto expression2 = [&] { pIntList.InsertAfter(pIntItr, &testInts[0]); };
			auto expression3 = [&] { FooList.InsertAfter(FooItr, testFoos[0]); };

			Assert::ExpectException<std::exception>(expression1);
			Assert::ExpectException<std::exception>(expression2);
			Assert::ExpectException<std::exception>(expression3);

			intList.PushFront(testInts[0]);
			pIntList.PushFront(&testInts[0]);
			FooList.PushFront(testFoos[0]);

			intItr = intList.begin();
			pIntItr = pIntList.begin();
			FooItr = FooList.begin();

			intList.InsertAfter(intItr, testInts[1]);
			pIntList.InsertAfter(pIntItr, &testInts[1]);
			FooList.InsertAfter(FooItr, testFoos[1]);

			Assert::AreEqual(intList.Back(), 100);
			Assert::AreEqual(intList.Back(), 100);
			Assert::AreEqual(intList.Back(), 100);

			intList.PushFront(testInts[0]);
			pIntList.PushFront(&testInts[0]);
			FooList.PushFront(testFoos[0]);

			intItr = intList.begin();
			pIntItr = pIntList.begin();
			FooItr = FooList.begin();

			intList.InsertAfter(intItr, testInts[2]);
			pIntList.InsertAfter(pIntItr, &testInts[2]);
			FooList.InsertAfter(FooItr, testFoos[2]);

			intItr++;
			pIntItr++;
			FooItr++;

			Assert::AreEqual(*intItr, 3);
			Assert::AreEqual(*pIntItr, &testInts[2]);
			Assert::AreEqual(FooItr.operator*().Data(), 3);

			intItr = intList.begin();
			pIntItr = pIntList.begin();
			FooItr = FooList.begin();

			intList.InsertAfter(intItr, testInts[1]);
			pIntList.InsertAfter(pIntItr, &testInts[1]);
			FooList.InsertAfter(FooItr, testFoos[1]);

			intItr++;
			pIntItr++;
			FooItr++;

			Assert::AreEqual(*intItr, 100);
			Assert::AreEqual(*pIntItr, &testInts[1]);
			Assert::AreEqual(FooItr.operator*().Data(), 100);
		}
	};
}