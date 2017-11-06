#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(StackTest)
	{
	public:
		Stack<int> intStack;
		Stack<int*> pIntStack;
		Stack<Foo> fooStack;
		const Stack<int> constIntStack;
		const Stack<int*> constPIntStack;
		const Stack<Foo> constFooStack;

		int testInts[3] = { 8, 42, 1337 };
		int* testPInts[3] = { &testInts[0], &testInts[1], &testInts[2] };
		Foo testFoos[3] = { Foo(testInts[0]), Foo(testInts[1]), Foo(testInts[2]) };

		TEST_METHOD(StackTestConstructor)
		{
			Assert::IsTrue(intStack.IsEmpty());
			Assert::IsTrue(pIntStack.IsEmpty());
			Assert::IsTrue(fooStack.IsEmpty());
		}

		TEST_METHOD(StackTestCopy)
		{
			Stack<int> intCopy(intStack);
			Stack<int*> pIntCopy(pIntStack);
			Stack<Foo> fooCopy(fooStack);

			Assert::AreEqual(intStack.Size(), intCopy.Size());
			Assert::AreEqual(pIntStack.Size(), pIntCopy.Size());
			Assert::AreEqual(fooStack.Size(), fooCopy.Size());

			auto expression1 = [this] { intStack.Top(); };
			auto expression2 = [this] { pIntStack.Top(); };
			auto expression3 = [this] { fooStack.Top(); };

			Assert::ExpectException<std::exception>(expression1);
			Assert::ExpectException<std::exception>(expression2);
			Assert::ExpectException<std::exception>(expression3);

			intStack.Push(testInts[0]);
			pIntStack.Push(testPInts[0]);
			fooStack.Push(testFoos[0]);
			intStack.Push(testInts[1]);
			pIntStack.Push(testPInts[1]);
			fooStack.Push(testFoos[1]);
			intStack.Push(testInts[2]);
			pIntStack.Push(testPInts[2]);
			fooStack.Push(testFoos[2]);

			Stack<int> intCopy2(intStack);
			Stack<int*> pIntCopy2(pIntStack);
			Stack<Foo> fooCopy2(fooStack);

			Assert::AreEqual(intStack.Top(), intCopy2.Top());
			Assert::AreEqual(pIntStack.Top(), pIntCopy2.Top());
			Assert::IsTrue(fooStack.Top() == fooCopy2.Top());

			intStack.Clear();
			pIntStack.Clear();
			fooStack.Clear();

			Assert::AreEqual(testInts[2], intCopy2.Top());
			Assert::AreEqual(testPInts[2], pIntCopy2.Top());
			Assert::IsTrue(testFoos[2] == fooCopy2.Top());
		}

		TEST_METHOD(StackTestPop)
		{
			intStack.Push(testInts[0]);
			pIntStack.Push(testPInts[0]);
			fooStack.Push(testFoos[0]);
			intStack.Push(testInts[1]);
			pIntStack.Push(testPInts[1]);
			fooStack.Push(testFoos[1]);

			intStack.Pop();
			pIntStack.Pop();
			fooStack.Pop();

			Assert::AreNotEqual(intStack.Top(), testInts[1]);
			Assert::AreNotEqual(pIntStack.Top(), testPInts[1]);
			Assert::IsFalse(fooStack.Top() == testFoos[1]);
		}

		TEST_METHOD(StackTestPush)
		{
			intStack.Push(testInts[0]);
			pIntStack.Push(testPInts[0]);
			fooStack.Push(testFoos[0]);
			intStack.Push(testInts[1]);
			pIntStack.Push(testPInts[1]);
			fooStack.Push(testFoos[1]);
			intStack.Push(testInts[2]);
			pIntStack.Push(testPInts[2]);
			fooStack.Push(testFoos[2]);
			intStack.Push(testInts[1]);
			pIntStack.Push(testPInts[1]);
			fooStack.Push(testFoos[1]);

			Assert::AreEqual(intStack.Top(), testInts[1]);
			Assert::AreEqual(pIntStack.Top(), testPInts[1]);
			Assert::IsTrue(fooStack.Top() == testFoos[1]);
		}

		TEST_METHOD(StackTestClear)
		{
			intStack.Clear();
			pIntStack.Clear();
			fooStack.Clear();

			Assert::IsTrue(intStack.IsEmpty());
			Assert::IsTrue(pIntStack.IsEmpty());
			Assert::IsTrue(fooStack.IsEmpty());

			intStack.Push(testInts[0]);
			pIntStack.Push(testPInts[0]);
			fooStack.Push(testFoos[0]);
			intStack.Push(testInts[1]);
			pIntStack.Push(testPInts[1]);
			fooStack.Push(testFoos[1]);
			intStack.Push(testInts[2]);
			pIntStack.Push(testPInts[2]);
			fooStack.Push(testFoos[2]);

			intStack.Clear();
			pIntStack.Clear();
			fooStack.Clear();

			Assert::IsTrue(intStack.IsEmpty());
			Assert::IsTrue(pIntStack.IsEmpty());
			Assert::IsTrue(fooStack.IsEmpty());
		}

		TEST_METHOD(StackTestSize)
		{
			Assert::AreEqual(intStack.Size(), 0U);
			Assert::AreEqual(pIntStack.Size(), 0U);
			Assert::AreEqual(fooStack.Size(), 0U);

			intStack.Push(testInts[0]);
			pIntStack.Push(testPInts[0]);
			fooStack.Push(testFoos[0]);
			intStack.Push(testInts[1]);
			pIntStack.Push(testPInts[1]);
			fooStack.Push(testFoos[1]);
			intStack.Push(testInts[2]);
			pIntStack.Push(testPInts[2]);
			fooStack.Push(testFoos[2]);

			Assert::AreEqual(intStack.Size(), 3U);
			Assert::AreEqual(pIntStack.Size(), 3U);
			Assert::AreEqual(fooStack.Size(), 3U);

			intStack.Pop();
			pIntStack.Pop();
			fooStack.Pop();

			Assert::AreEqual(intStack.Size(), 2U);
			Assert::AreEqual(pIntStack.Size(), 2U);
			Assert::AreEqual(fooStack.Size(), 2U);

			intStack.Clear();
			pIntStack.Clear();
			fooStack.Clear();

			Assert::AreEqual(intStack.Size(), 0U);
			Assert::AreEqual(pIntStack.Size(), 0U);
			Assert::AreEqual(fooStack.Size(), 0U);
		}

		TEST_METHOD(StackTestIsEmpty)
		{
			Assert::IsTrue(intStack.IsEmpty());
			Assert::IsTrue(pIntStack.IsEmpty());
			Assert::IsTrue(fooStack.IsEmpty());

			intStack.Push(testInts[0]);
			pIntStack.Push(testPInts[0]);
			fooStack.Push(testFoos[0]);
			intStack.Push(testInts[1]);
			pIntStack.Push(testPInts[1]);
			fooStack.Push(testFoos[1]);
			intStack.Push(testInts[2]);
			pIntStack.Push(testPInts[2]);
			fooStack.Push(testFoos[2]);

			intStack.Clear();
			pIntStack.Clear();
			fooStack.Clear();

			Assert::IsTrue(intStack.IsEmpty());
			Assert::IsTrue(pIntStack.IsEmpty());
			Assert::IsTrue(fooStack.IsEmpty());
		}

		TEST_METHOD(StackTestTop)
		{
			auto expression1 = [this] { intStack.Top(); };
			auto expression2 = [this] { pIntStack.Top(); };
			auto expression3 = [this] { fooStack.Top(); };

			Assert::ExpectException<std::exception>(expression1);
			Assert::ExpectException<std::exception>(expression2);
			Assert::ExpectException<std::exception>(expression3);

			intStack.Push(testInts[0]);
			pIntStack.Push(testPInts[0]);
			fooStack.Push(testFoos[0]);
			intStack.Push(testInts[1]);
			pIntStack.Push(testPInts[1]);
			fooStack.Push(testFoos[1]);
			intStack.Push(testInts[2]);
			pIntStack.Push(testPInts[2]);
			fooStack.Push(testFoos[2]);

			Assert::AreEqual(intStack.Top(), testInts[2]);
			Assert::AreEqual(pIntStack.Top(), testPInts[2]);
			Assert::IsTrue(fooStack.Top() == testFoos[2]);
		}

		TEST_METHOD(StackTestTopConst)
		{
			auto expression1 = [this] { constIntStack.Top(); };
			auto expression2 = [this] { constPIntStack.Top(); };
			auto expression3 = [this] { constFooStack.Top(); };

			Assert::ExpectException<std::exception>(expression1);
			Assert::ExpectException<std::exception>(expression2);
			Assert::ExpectException<std::exception>(expression3);

			intStack.Push(testInts[0]);
			pIntStack.Push(testPInts[0]);
			fooStack.Push(testFoos[0]);
			intStack.Push(testInts[1]);
			pIntStack.Push(testPInts[1]);
			fooStack.Push(testFoos[1]);
			intStack.Push(testInts[2]);
			pIntStack.Push(testPInts[2]);
			fooStack.Push(testFoos[2]);

			const Stack<int> constIntStack2(intStack);
			const Stack<int*> constPIntStack2(pIntStack);
			const Stack<Foo> constFooStack2(fooStack);

			Assert::AreEqual(constIntStack2.Top(), testInts[2]);
			Assert::AreEqual(constPIntStack2.Top(), testPInts[2]);
			Assert::IsTrue(constFooStack2.Top() == testFoos[2]);
		}
	};
}