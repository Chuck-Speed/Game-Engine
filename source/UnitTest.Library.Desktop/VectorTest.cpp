#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(VectorTest)
	{
	public:
		Vector<int> intVector;
		Vector<int*> pIntVector;
		Vector<Foo> fooVector;
		const Vector<int> constIntVector;
		const Vector<int*> constPIntVector;
		const Vector<Foo> constFooVector;

		int testInts[3] = { 8, 42, 1337 };
		int* testPInts[3] = { &testInts[0], &testInts[1], &testInts[2] };
		Foo testFoos[3] = { Foo(testInts[0]), Foo(testInts[1]), Foo(testInts[2]) };

		TEST_METHOD(VectorTestConstructor)
		{
			Assert::IsTrue(intVector.IsEmpty());
			Assert::IsTrue(pIntVector.IsEmpty());
			Assert::IsTrue(fooVector.IsEmpty());
			Assert::AreEqual(intVector.Capacity(), 0U);
			Assert::AreEqual(pIntVector.Capacity(), 0U);
			Assert::AreEqual(fooVector.Capacity(), 0U);
		}

		TEST_METHOD(VectorTestCopy)
		{
			Vector<int> intCopy(intVector);
			Vector<int*> pIntCopy(pIntVector);
			Vector<Foo> fooCopy(fooVector);

			Assert::AreEqual(intVector.Size(), intCopy.Size());
			Assert::AreEqual(pIntVector.Size(), pIntCopy.Size());
			Assert::AreEqual(fooVector.Size(), fooCopy.Size());

			auto expression1 = [this] { intVector.Front(); };
			auto expression2 = [this] { pIntVector.Front(); };
			auto expression3 = [this] { fooVector.Front(); };
			auto expression4 = [this] { intVector.Back(); };
			auto expression5 = [this] { pIntVector.Back(); };
			auto expression6 = [this] { fooVector.Back(); };

			Assert::ExpectException<std::exception>(expression1);
			Assert::ExpectException<std::exception>(expression2);
			Assert::ExpectException<std::exception>(expression3);
			Assert::ExpectException<std::exception>(expression4);
			Assert::ExpectException<std::exception>(expression5);
			Assert::ExpectException<std::exception>(expression6);

			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);
			intVector.PushBack(testInts[2]);
			pIntVector.PushBack(testPInts[2]);
			fooVector.PushBack(testFoos[2]);

			Vector<int> intCopy2(intVector);
			Vector<int*> pIntCopy2(pIntVector);
			Vector<Foo> fooCopy2(fooVector);

			Assert::AreEqual(intVector.Front(), intCopy2.Front());
			Assert::AreEqual(pIntVector.Front(), pIntCopy2.Front());
			Assert::IsTrue(fooVector.Front() == fooCopy2.Front());
			Assert::AreEqual(intVector.Back(), intCopy2.Back());
			Assert::AreEqual(pIntVector.Back(), pIntCopy2.Back());
			Assert::IsTrue(fooVector.Back() == fooCopy2.Back());
		}

		TEST_METHOD(VectorTestBracket)
		{
			auto expression1 = [this] { intVector.operator[](0U); };
			auto expression2 = [this] { pIntVector.operator[](0U); };
			auto expression3 = [this] { fooVector.operator[](0U); };

			Assert::ExpectException<std::out_of_range>(expression1);
			Assert::ExpectException<std::out_of_range>(expression2);
			Assert::ExpectException<std::out_of_range>(expression3);
			
			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);

			Assert::IsTrue(intVector[0] == testInts[0]);
			Assert::IsTrue(pIntVector[0] == testPInts[0]);
			Assert::IsTrue(fooVector[0] == testFoos[0]);
		}

		TEST_METHOD(VectorTestBracketConst)
		{
			auto expression1 = [this] { constIntVector.operator[](1U); };
			auto expression2 = [this] { constPIntVector.operator[](1U); };
			auto expression3 = [this] { constFooVector.operator[](1U); };

			Assert::ExpectException<std::out_of_range>(expression1);
			Assert::ExpectException<std::out_of_range>(expression2);
			Assert::ExpectException<std::out_of_range>(expression3);

			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);

			const Vector<int> constIntVector2(intVector);
			const Vector<int*> constPIntVector2(pIntVector);
			const Vector<Foo> constFooVector2(fooVector);

			Assert::IsTrue(constIntVector2[0] == testInts[0]);
			Assert::IsTrue(constPIntVector2[0] == testPInts[0]);
			Assert::IsTrue(constFooVector2[0] == testFoos[0]);
		}

		TEST_METHOD(VectorTestPopBack)
		{
			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);

			intVector.PopBack();
			pIntVector.PopBack();
			fooVector.PopBack();

			Assert::AreNotEqual(intVector.Back(), testInts[1]);
			Assert::AreNotEqual(pIntVector.Back(), testPInts[1]);
			Assert::IsFalse(fooVector.Back() == testFoos[1]);
		}

		TEST_METHOD(VectorTestPushBack)
		{
			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);
			intVector.PushBack(testInts[2]);
			pIntVector.PushBack(testPInts[2]);
			fooVector.PushBack(testFoos[2]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);

			Assert::AreEqual(intVector.Back(), testInts[1]);
			Assert::AreEqual(pIntVector.Back(), testPInts[1]);
			Assert::IsTrue(fooVector.Back() == testFoos[1]);
			Assert::AreEqual(intVector.Capacity(), 4U);
			Assert::AreEqual(pIntVector.Capacity(), 4U);
			Assert::AreEqual(fooVector.Capacity(), 4U);
		}

		TEST_METHOD(VectorTestReserve)
		{
			intVector.Reserve(1U);
			pIntVector.Reserve(1U);
			fooVector.Reserve(1U);
			intVector.Reserve(5U);
			pIntVector.Reserve(5U);
			fooVector.Reserve(5U);

			Assert::AreEqual(intVector.Capacity(), 5U);
			Assert::AreEqual(pIntVector.Capacity(), 5U);
			Assert::AreEqual(fooVector.Capacity(), 5U);

			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);

			Assert::AreEqual(intVector.Capacity(), 5U);
			Assert::AreEqual(pIntVector.Capacity(), 5U);
			Assert::AreEqual(fooVector.Capacity(), 5U);
		}

		TEST_METHOD(VectorTestFind)
		{
			Vector<int>::Iterator intItr = intVector.Find(testInts[2]);
			Vector<int*>::Iterator pIntItr = pIntVector.Find(testPInts[2]);
			Vector<Foo>::Iterator fooItr = fooVector.Find(testFoos[2]);

			auto expression1 = [&] { intItr.operator*(); };
			auto expression2 = [&] { pIntItr.operator*(); };
			auto expression3 = [&] { fooItr.operator*(); };

			Assert::ExpectException<std::exception>(expression1);
			Assert::ExpectException<std::exception>(expression2);
			Assert::ExpectException<std::exception>(expression3);

			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);
			intVector.PushBack(testInts[2]);
			pIntVector.PushBack(testPInts[2]);
			fooVector.PushBack(testFoos[2]);

			intItr = intVector.Find(testInts[1]);
			pIntItr = pIntVector.Find(testPInts[1]);
			fooItr = fooVector.Find(testFoos[1]);

			Assert::AreEqual(*intItr, testInts[1]);
			Assert::AreEqual(*pIntItr, testPInts[1]);
			Assert::IsTrue(*fooItr == testFoos[1]);
		}

		TEST_METHOD(VectorTestClear)
		{
			intVector.Clear();
			pIntVector.Clear();
			fooVector.Clear();

			Assert::IsTrue(intVector.IsEmpty());
			Assert::IsTrue(pIntVector.IsEmpty());
			Assert::IsTrue(fooVector.IsEmpty());

			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);
			intVector.PushBack(testInts[2]);
			pIntVector.PushBack(testPInts[2]);
			fooVector.PushBack(testFoos[2]);

			intVector.Clear();
			pIntVector.Clear();
			fooVector.Clear();

			Assert::IsTrue(intVector.IsEmpty());
			Assert::IsTrue(pIntVector.IsEmpty());
			Assert::IsTrue(fooVector.IsEmpty());

			Vector<int> intVector2(10U, true);
			Vector<int*> pIntVector2(10U, true);
			Vector<Foo> fooVector2(10U, true);

			intVector2.Clear();
			pIntVector2.Clear();
			fooVector2.Clear();

			Assert::IsTrue(intVector2.IsEmpty());
			Assert::IsTrue(pIntVector2.IsEmpty());
			Assert::IsTrue(fooVector2.IsEmpty());
		}

		TEST_METHOD(VectorTestRemove)
		{
			intVector.Remove(testInts[0]);
			pIntVector.Remove(testPInts[0]);
			fooVector.Remove(testFoos[0]);

			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);
			intVector.PushBack(testInts[2]);
			pIntVector.PushBack(testPInts[2]);
			fooVector.PushBack(testFoos[2]);

			intVector.Remove(testInts[0]);
			pIntVector.Remove(testPInts[0]);
			fooVector.Remove(testFoos[0]);

			Assert::AreEqual(intVector.Front(), testInts[1]);
			Assert::AreEqual(pIntVector.Front(), testPInts[1]);
			Assert::IsTrue(fooVector.Front() == testFoos[1]);
			Assert::AreEqual(intVector.Size(), 2U);
			Assert::AreEqual(pIntVector.Size(), 2U);
			Assert::AreEqual(fooVector.Size(), 2U);

			intVector.Remove(testInts[2]);
			pIntVector.Remove(testPInts[2]);
			fooVector.Remove(testFoos[2]);

			Assert::AreEqual(intVector.Back(), testInts[1]);
			Assert::AreEqual(pIntVector.Back(), testPInts[1]);
			Assert::IsTrue(fooVector.Back() == testFoos[1]);
			Assert::AreEqual(intVector.Size(), 1U);
			Assert::AreEqual(pIntVector.Size(), 1U);
			Assert::AreEqual(fooVector.Size(), 1U);
		}

		TEST_METHOD(VectorTestSize)
		{
			Vector<int> intVector2(5U, true);

			Assert::AreEqual(intVector.Size(), 0U);
			Assert::AreEqual(pIntVector.Size(), 0U);
			Assert::AreEqual(fooVector.Size(), 0U);

			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);
			intVector.PushBack(testInts[2]);
			pIntVector.PushBack(testPInts[2]);
			fooVector.PushBack(testFoos[2]);

			Assert::AreEqual(intVector.Size(), 3U);
			Assert::AreEqual(pIntVector.Size(), 3U);
			Assert::AreEqual(fooVector.Size(), 3U);

			intVector.PopBack();
			pIntVector.PopBack();
			fooVector.PopBack();

			Assert::AreEqual(intVector.Size(), 2U);
			Assert::AreEqual(pIntVector.Size(), 2U);
			Assert::AreEqual(fooVector.Size(), 2U);

			intVector.Clear();
			pIntVector.Clear();
			fooVector.Clear();

			Assert::AreEqual(intVector.Size(), 0U);
			Assert::AreEqual(pIntVector.Size(), 0U);
			Assert::AreEqual(fooVector.Size(), 0U);
		}

		TEST_METHOD(VectorTestCapacity)
		{
			Assert::AreEqual(intVector.Capacity(), 0U);
			Assert::AreEqual(pIntVector.Capacity(), 0U);
			Assert::AreEqual(fooVector.Capacity(), 0U);

			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);
			intVector.PushBack(testInts[2]);
			pIntVector.PushBack(testPInts[2]);
			fooVector.PushBack(testFoos[2]);
			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);
			intVector.PushBack(testInts[2]);
			pIntVector.PushBack(testPInts[2]);
			fooVector.PushBack(testFoos[2]);

			Assert::AreEqual(intVector.Capacity(), 7U);
			Assert::AreEqual(pIntVector.Capacity(), 7U);
			Assert::AreEqual(fooVector.Capacity(), 7U);

			intVector.Clear();
			pIntVector.Clear();
			fooVector.Clear();

			Assert::AreEqual(intVector.Capacity(), 0U);
			Assert::AreEqual(pIntVector.Capacity(), 0U);
			Assert::AreEqual(fooVector.Capacity(), 0U);
		}

		TEST_METHOD(VectorTestAt)
		{
			auto expression1 = [this] { intVector.At(1U); };
			auto expression2 = [this] { pIntVector.At(1U); };
			auto expression3 = [this] { fooVector.At(1U); };

			Assert::ExpectException<std::out_of_range>(expression1);
			Assert::ExpectException<std::out_of_range>(expression2);
			Assert::ExpectException<std::out_of_range>(expression3);

			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);
			intVector.PushBack(testInts[2]);
			pIntVector.PushBack(testPInts[2]);
			fooVector.PushBack(testFoos[2]);

			Assert::AreEqual(intVector.At(1U), testInts[1]);
			Assert::AreEqual(pIntVector.At(1U), testPInts[1]);
			Assert::IsTrue(fooVector.At(1U) == testFoos[1]);
		}

		TEST_METHOD(VectorTestIsEmpty)
		{
			Assert::IsTrue(intVector.IsEmpty());
			Assert::IsTrue(pIntVector.IsEmpty());
			Assert::IsTrue(fooVector.IsEmpty());

			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);
			intVector.PushBack(testInts[2]);
			pIntVector.PushBack(testPInts[2]);
			fooVector.PushBack(testFoos[2]);

			intVector.Clear();
			pIntVector.Clear();
			fooVector.Clear();

			Assert::IsTrue(intVector.IsEmpty());
			Assert::IsTrue(pIntVector.IsEmpty());
			Assert::IsTrue(fooVector.IsEmpty());
		}

		TEST_METHOD(VectorTestFront)
		{
			auto expression1 = [this] { intVector.Front(); };
			auto expression2 = [this] { pIntVector.Front(); };
			auto expression3 = [this] { fooVector.Front(); };

			Assert::ExpectException<std::exception>(expression1);
			Assert::ExpectException<std::exception>(expression2);
			Assert::ExpectException<std::exception>(expression3);

			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);
			intVector.PushBack(testInts[2]);
			pIntVector.PushBack(testPInts[2]);
			fooVector.PushBack(testFoos[2]);

			Assert::AreEqual(intVector.Front(), testInts[0]);
			Assert::AreEqual(pIntVector.Front(), testPInts[0]);
			Assert::IsTrue(fooVector.Front() == testFoos[0]);
		}

		TEST_METHOD(VectorTestFrontConst)
		{
			auto expression1 = [this] { constIntVector.Front(); };
			auto expression2 = [this] { constPIntVector.Front(); };
			auto expression3 = [this] { constFooVector.Front(); };

			Assert::ExpectException<std::exception>(expression1);
			Assert::ExpectException<std::exception>(expression2);
			Assert::ExpectException<std::exception>(expression3);

			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);
			intVector.PushBack(testInts[2]);
			pIntVector.PushBack(testPInts[2]);
			fooVector.PushBack(testFoos[2]);

			const Vector<int> constIntVector2(intVector);
			const Vector<int*> constPIntVector2(pIntVector);
			const Vector<Foo> constFooVector2(fooVector);

			Assert::AreEqual(constIntVector2.Front(), testInts[0]);
			Assert::AreEqual(constPIntVector2.Front(), testPInts[0]);
			Assert::IsTrue(constFooVector2.Front() == testFoos[0]);
		}


		TEST_METHOD(VectorTestBack)
		{
			auto expression1 = [this] { intVector.Back(); };
			auto expression2 = [this] { pIntVector.Back(); };
			auto expression3 = [this] { fooVector.Back(); };

			Assert::ExpectException<std::exception>(expression1);
			Assert::ExpectException<std::exception>(expression2);
			Assert::ExpectException<std::exception>(expression3);

			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);
			intVector.PushBack(testInts[2]);
			pIntVector.PushBack(testPInts[2]);
			fooVector.PushBack(testFoos[2]);

			Assert::AreEqual(intVector.Back(), testInts[2]);
			Assert::AreEqual(pIntVector.Back(), testPInts[2]);
			Assert::IsTrue(fooVector.Back() == testFoos[2]);
		}

		TEST_METHOD(VectorTestBackConst)
		{
			auto expression1 = [this] { constIntVector.Back(); };
			auto expression2 = [this] { constPIntVector.Back(); };
			auto expression3 = [this] { constFooVector.Back(); };

			Assert::ExpectException<std::exception>(expression1);
			Assert::ExpectException<std::exception>(expression2);
			Assert::ExpectException<std::exception>(expression3);

			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);
			intVector.PushBack(testInts[2]);
			pIntVector.PushBack(testPInts[2]);
			fooVector.PushBack(testFoos[2]);

			const Vector<int> constIntVector2(intVector);
			const Vector<int*> constPIntVector2(pIntVector);
			const Vector<Foo> constFooVector2(fooVector);

			Assert::AreEqual(constIntVector2.Back(), testInts[2]);
			Assert::AreEqual(constPIntVector2.Back(), testPInts[2]);
			Assert::IsTrue(constFooVector2.Back() == testFoos[2]);
		}

		TEST_METHOD(IteratorTestConstructor)
		{
			Vector<int>::Iterator intItr;
			Vector<int*>::Iterator pIntItr;
			Vector<Foo>::Iterator fooItr;

			auto expression1 = [&] { intItr.operator*(); };
			auto expression2 = [&] { pIntItr.operator*(); };
			auto expression3 = [&] { fooItr.operator*(); };

			Assert::ExpectException<std::exception>(expression1);
			Assert::ExpectException<std::exception>(expression2);
			Assert::ExpectException<std::exception>(expression3);
		}

		TEST_METHOD(IteratorTestCopy)
		{
			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);

			Vector<int>::Iterator intItr = intVector.begin();
			Vector<int*>::Iterator pIntItr = pIntVector.begin();
			Vector<Foo>::Iterator fooItr = fooVector.begin();
			Vector<int>::Iterator intItr2(intItr);
			Vector<int*>::Iterator pIntItr2(pIntItr);
			Vector<Foo>::Iterator fooItr2(fooItr);

			Assert::AreEqual(*intItr, *intItr2);
			Assert::AreEqual(*pIntItr, *pIntItr2);
			Assert::IsTrue(*fooItr == *fooItr2);
		}

		TEST_METHOD(IteratorTestComparison)
		{
			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);

			Vector<int>::Iterator intItr = intVector.begin();
			Vector<int*>::Iterator pIntItr = pIntVector.begin();
			Vector<Foo>::Iterator fooItr = fooVector.begin();
			Vector<int>::Iterator intItr2(intItr);
			Vector<int*>::Iterator pIntItr2(pIntItr);
			Vector<Foo>::Iterator fooItr2(fooItr);

			Assert::IsTrue(intItr == intItr2);
			Assert::IsTrue(pIntItr == pIntItr2);
			Assert::IsTrue(fooItr == fooItr2);

			Assert::IsFalse(intItr != intItr2);
			Assert::IsFalse(pIntItr != pIntItr2);
			Assert::IsFalse(fooItr != fooItr2);

			intItr2 = intVector.end();
			pIntItr2 = pIntVector.end();
			fooItr2 = fooVector.end();

			Assert::IsFalse(intItr == intItr2);
			Assert::IsFalse(pIntItr == pIntItr2);
			Assert::IsFalse(fooItr == fooItr2);

			Assert::IsTrue(intItr != intItr2);
			Assert::IsTrue(pIntItr != pIntItr2);
			Assert::IsTrue(fooItr != fooItr2);
		}

		TEST_METHOD(IteratorTestIncrement)
		{
			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);
			intVector.PushBack(testInts[2]);
			pIntVector.PushBack(testPInts[2]);
			fooVector.PushBack(testFoos[2]);

			Vector<int>::Iterator intItr = intVector.begin();
			Vector<int*>::Iterator pIntItr = pIntVector.begin();
			Vector<Foo>::Iterator fooItr = fooVector.begin();

			Assert::AreEqual(*(intItr++), testInts[0]);
			Assert::AreEqual(*(++intItr), testInts[2]);
			Assert::AreEqual(*(pIntItr++), testPInts[0]);
			Assert::AreEqual(*(++pIntItr), testPInts[2]);
			Assert::IsTrue(*(fooItr++) == testFoos[0]);
			Assert::IsTrue(*(++fooItr) ==  testFoos[2]);

			Vector<int>::Iterator intItr2;
			Vector<int*>::Iterator pIntItr2;
			Vector<Foo>::Iterator fooItr2;

			auto expression1 = [&] { intItr2.operator++(); };
			auto expression2 = [&] { pIntItr2.operator++(); };
			auto expression3 = [&] { fooItr2.operator++(); };
			auto expression4 = [&] { intItr2.operator++(0); };
			auto expression5 = [&] { pIntItr2.operator++(0); };
			auto expression6 = [&] { fooItr2.operator++(0); };

			Assert::ExpectException<std::exception>(expression1);
			Assert::ExpectException<std::exception>(expression2);
			Assert::ExpectException<std::exception>(expression3);
			Assert::ExpectException<std::exception>(expression4);
			Assert::ExpectException<std::exception>(expression5);
			Assert::ExpectException<std::exception>(expression6);
		}

		TEST_METHOD(IteratorTestDereference)
		{
			Vector<int>::Iterator intItr;
			Vector<int*>::Iterator pIntItr;
			Vector<Foo>::Iterator fooItr;

			auto expression1 = [&] { intItr.operator*(); };
			auto expression2 = [&] { pIntItr.operator*(); };
			auto expression3 = [&] { fooItr.operator*(); };

			Assert::ExpectException<std::exception>(expression1);
			Assert::ExpectException<std::exception>(expression2);
			Assert::ExpectException<std::exception>(expression3);

			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);
			intVector.PushBack(testInts[2]);
			pIntVector.PushBack(testPInts[2]);
			fooVector.PushBack(testFoos[2]);

			intItr = intVector.begin();
			pIntItr = pIntVector.begin();
			fooItr = fooVector.begin();

			Assert::AreEqual(*intItr, testInts[0]);
			Assert::AreEqual(*pIntItr, testPInts[0]);
			Assert::IsTrue(*fooItr == testFoos[0]);

			intItr = intVector.end();
			pIntItr = pIntVector.end();
			fooItr = fooVector.end();

			Assert::ExpectException<std::exception>(expression1);
			Assert::ExpectException<std::exception>(expression2);
			Assert::ExpectException<std::exception>(expression3);
		}

		TEST_METHOD(IteratorTestBegin)
		{
			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);

			Vector<int>::Iterator intItr = intVector.begin();
			Vector<int*>::Iterator pIntItr = pIntVector.begin();
			Vector<Foo>::Iterator fooItr = fooVector.begin();

			Assert::AreEqual(*intItr, testInts[0]);
			Assert::AreEqual(*pIntItr, testPInts[0]);
			Assert::IsTrue(*fooItr == testFoos[0]);
		}

		TEST_METHOD(IteratorTestEnd)
		{
			intVector.PushBack(testInts[0]);
			pIntVector.PushBack(testPInts[0]);
			fooVector.PushBack(testFoos[0]);
			intVector.PushBack(testInts[1]);
			pIntVector.PushBack(testPInts[1]);
			fooVector.PushBack(testFoos[1]);
			intVector.PushBack(testInts[2]);
			pIntVector.PushBack(testPInts[2]);
			fooVector.PushBack(testFoos[2]);

			Vector<int>::Iterator intItr = intVector.end();
			Vector<int*>::Iterator pIntItr = pIntVector.end();
			Vector<Foo>::Iterator fooItr = fooVector.end();

			auto expression1 = [&] { intItr.operator*(); };
			auto expression2 = [&] { pIntItr.operator*(); };
			auto expression3 = [&] { fooItr.operator*(); };

			Assert::ExpectException<std::exception>(expression1);
			Assert::ExpectException<std::exception>(expression2);
			Assert::ExpectException<std::exception>(expression3);
		}
	};
}