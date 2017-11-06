#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{

	class FHash
	{
	public:
		std::uint32_t operator()(const Foo& key) const
		{
			uint32_t hash = 0;

			for (uint32_t i = 0; i < sizeof(key); ++i)
			{
				hash = 33 * hash + key.Data() + (key.MoreData());
			}
			return (hash);
		}
	};


	TEST_CLASS(HashmapTest)
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

		Hashmap<int, int> intHash;
		Hashmap<int*, int> pIntHash;
		Hashmap<char*, int> charHash;
		Hashmap<std::string, int> stringHash;
		Hashmap<Foo, int, FHash> FooHash;


		int testInts[3] = { 8, 42, 1337 };
		int* testPInts[3] = { &testInts[0], &testInts[1], &testInts[2] };
		Foo testFoos[3] = { Foo(testInts[0]), Foo(testInts[1]), Foo(testInts[2]) };

		TEST_METHOD(HashmapTestConstructor)
		{
			Hashmap<int, int> intHash2(5U);
			Assert::AreEqual(intHash.Size(), 0U);

			Hashmap<int*, int> pIntHash2(5U);
			Assert::AreEqual(pIntHash.Size(), 0U);

			Hashmap<char*, int> charHash2(5U);
			Assert::AreEqual(charHash.Size(), 0U);

			Hashmap<std::string, int> stringHash2(5U);
			Assert::AreEqual(stringHash.Size(), 0U);

			Hashmap<Foo, int> FooHash2(5U);
			Assert::AreEqual(FooHash2.Size(), 0U);
		}

		TEST_METHOD(HashmapTestFind)
		{
			Hashmap<int, int> intHashEmpty;
			auto testPair = Hashmap<int, int>::PairType(5, 9001);

			auto expression1 = [&] { *intHash.Find(testPair.first); };
			Assert::ExpectException<std::exception>(expression1);

			intHash.Insert(Hashmap<int, int>::PairType(5, 9001));
			auto itr = intHash.Find(testPair.first);

			Assert::IsTrue(*itr == testPair);
			intHash = intHashEmpty;

			Hashmap<int*, int> pIntHashEmpty;
			int a = 4;
			auto testPair2 = Hashmap<int*, int>::PairType(&a, 9001);

			auto expression2 = [&] { *pIntHash.Find(testPair2.first); };
			Assert::ExpectException<std::exception>(expression2);

			pIntHash.Insert(Hashmap<int*, int>::PairType(&a, 9001));
			auto itr2 = pIntHash.Find(testPair2.first);

			Assert::IsTrue(*itr2 == testPair2);
			pIntHash = pIntHashEmpty;

			Hashmap<char*, int> charHashEmpty;
			char* b = "Test";
			auto testPair3 = Hashmap<char*, int>::PairType(b, 9001);

			auto expression3 = [&] { *charHash.Find(testPair3.first); };
			Assert::ExpectException<std::exception>(expression2);

			charHash.Insert(Hashmap<char*, int>::PairType(b, 9001));
			auto itr3 =charHash.Find(testPair3.first);

			Assert::IsTrue(*itr3 == testPair3);
			charHash = charHashEmpty;

			Hashmap<std::string, int> stringHashEmpty;
			std::string d = "Testing";
			auto testPair4 = Hashmap<std::string, int>::PairType(d, 9001);

			auto expression4 = [&] { *stringHash.Find(testPair4.first); };
			Assert::ExpectException<std::exception>(expression4);

			stringHash.Insert(Hashmap<std::string, int>::PairType(d, 9001));
			auto itr4 = stringHash.Find(testPair4.first);

			Assert::IsTrue(*itr4 == testPair4);
			stringHash = stringHashEmpty;

			Hashmap<Foo, int, FHash> FooHashEmpty;
			Foo e(55);
			auto testPair5 = Hashmap<Foo, int>::PairType(e, 9001);

			auto expression5 = [&] { *FooHash.Find(testPair5.first); };
			Assert::ExpectException<std::exception>(expression5);

			FooHash.Insert(Hashmap<Foo, int>::PairType(e, 9001));
			auto itr5 = FooHash.Find(testPair5.first);

			Assert::IsTrue(*itr5 == testPair5);
			FooHash = FooHashEmpty;
		}

		TEST_METHOD(HashmapTestClear)
		{
			Hashmap<int, int> intHashEmpty;
			intHash.Clear();
			intHash.Insert(Hashmap<int, int>::PairType(5, 9001));
			intHash = intHashEmpty;

			Hashmap<int*, int> pIntHashEmpty;
			int a = 5;
			pIntHash.Clear();
			pIntHash.Insert(Hashmap<int*, int>::PairType(&a, 9001));
			pIntHash = pIntHashEmpty;

			Hashmap<char*, int> charHashEmpty;
			char* b = "test";
			charHash.Clear();
			charHash.Insert(Hashmap<char*, int>::PairType(b, 9001));
			charHash = charHashEmpty;

			Hashmap<std::string, int> stringHashEmpty;
			std::string c = "Testing";
			stringHash.Clear();
			stringHash.Insert(Hashmap<std::string, int>::PairType(c, 9001));
			stringHash = stringHashEmpty;

			Hashmap<Foo, int, FHash> FooHashEmpty;
			Foo e(55);
			FooHash.Clear();
			FooHash.Insert(Hashmap<Foo, int>::PairType(e, 9001));
			FooHash = FooHashEmpty;
		}

		TEST_METHOD(HashmapTestIndexOperator)
		{
			Hashmap<int, int> intHashEmpty;
			auto testPair = Hashmap<int, int>::PairType(5, 9001);
			auto a = intHash[testPair.first];

			Assert::AreEqual(a, 0);

			intHash.Insert(testPair);
			auto b = intHash[testPair.first];

			Assert::AreEqual(a, b);
			intHash = intHashEmpty;

			Hashmap<int*, int> pIntHashEmpty;
			auto testPair2 = Hashmap<int*, int>::PairType(&a, 9001);
			auto c = pIntHash[testPair2.first];

			Assert::AreEqual(c, 0);

			pIntHash.Insert(testPair2);
			auto d = pIntHash[testPair2.first];

			Assert::AreEqual(c, d);
			pIntHash = pIntHashEmpty;

			Hashmap<char*, int> charHashEmpty;
			char* e = "test";
			auto testPair3 = Hashmap<char*, int>::PairType(e, 9001);
			auto f = charHash[testPair3.first];

			Assert::AreEqual(f, 0);

			charHash.Insert(testPair3);
			auto g = charHash[testPair3.first];

			Assert::AreEqual(f, g);
			charHash = charHashEmpty;

			Hashmap<std::string, int> stringHashEmpty;
			std::string h = "Testing";
			auto testPair4 = Hashmap<std::string, int>::PairType(h, 9001);
			auto i = stringHash[testPair4.first];

			Assert::AreEqual(i, 0);

			stringHash.Insert(testPair4);
			auto j = stringHash[testPair4.first];

			Assert::AreEqual(i, j);
			stringHash = stringHashEmpty;

			Hashmap<Foo, int, FHash> FooHashEmpty;
			Foo k(55);
			auto testPair5 = Hashmap<Foo, int>::PairType(k, 9001);
			auto l = FooHash[testPair5.first];

			Assert::AreEqual(l, 0);

			FooHash.Insert(testPair5);
			auto m = FooHash[testPair5.first];

			Assert::AreEqual(l, m);
			FooHash = FooHashEmpty;
		}

			TEST_METHOD(HashmapTestRemove)
			{
				auto testPair = Hashmap<int, int>::PairType(5, 9001);
				intHash.Insert(testPair);
				intHash.Remove(testPair.first);
				Assert::AreEqual(intHash.Size(), 0U);

				int a = 5;
				auto testPair2 = Hashmap<int*, int>::PairType(&a, 9001);
				pIntHash.Insert(testPair2);
				pIntHash.Remove(testPair2.first);
				Assert::AreEqual(pIntHash.Size(), 0U);

				char* b = "test";
				auto testPair3 = Hashmap<char*, int>::PairType(b, 9001);
				charHash.Insert(testPair3);
				charHash.Remove(testPair3.first);
				Assert::AreEqual(charHash.Size(), 0U);

				std::string c = "testing";
				auto testPair4 = Hashmap<std::string, int>::PairType(c, 9001);
				stringHash.Insert(testPair4);
				stringHash.Remove(testPair4.first);
				Assert::AreEqual(stringHash.Size(), 0U);

				Foo e(55);
				auto testPair5 = Hashmap<Foo, int>::PairType(e, 9001);
				FooHash.Insert(testPair5);
				FooHash.Remove(testPair5.first);
				Assert::AreEqual(FooHash.Size(), 0U);
			}

			TEST_METHOD(HashmapTestSize)
			{
				Assert::AreEqual(intHash.Size(), 0U);

				auto testPair = Hashmap<int, int>::PairType(5, 9001);
				intHash.Insert(testPair);
				intHash.Insert(testPair);
				intHash.Insert(testPair);

				Assert::AreEqual(intHash.Size(), 1U);

				intHash.Remove(testPair.first);
				Assert::AreEqual(intHash.Size(), 0U);

				Assert::AreEqual(pIntHash.Size(), 0U);
				int a = 5;
				auto testPair2 = Hashmap<int*, int>::PairType(&a, 9001);
				pIntHash.Insert(testPair2);
				pIntHash.Insert(testPair2);
				pIntHash.Insert(testPair2);

				Assert::AreEqual(pIntHash.Size(), 1U);

				pIntHash.Remove(testPair2.first);
				Assert::AreEqual(pIntHash.Size(), 0U);

				char* b = "test";
				auto testPair3 = Hashmap<char*, int>::PairType(b, 9001);
				charHash.Insert(testPair3);
				charHash.Insert(testPair3);
				charHash.Insert(testPair3);
				Assert::AreEqual(charHash.Size(), 1U);

				charHash.Remove(testPair3.first);
				Assert::AreEqual(charHash.Size(), 0U);

				std::string c = "testing";
				auto testPair4 = Hashmap<std::string, int>::PairType(b, 9001);
				stringHash.Insert(testPair4);
				stringHash.Insert(testPair4);
				stringHash.Insert(testPair4);
				Assert::AreEqual(stringHash.Size(), 1U);

				stringHash.Remove(testPair4.first);
				Assert::AreEqual(stringHash.Size(), 0U);

				Assert::AreEqual(pIntHash.Size(), 0U);
				Foo e(55);
				auto testPair5 = Hashmap<Foo, int>::PairType(e, 9001);
				FooHash.Insert(testPair5);
				FooHash.Insert(testPair5);
				FooHash.Insert(testPair5);

				Assert::AreEqual(FooHash.Size(), 1U);

				FooHash.Remove(testPair5.first);
				Assert::AreEqual(FooHash.Size(), 0U);
			}

		TEST_METHOD(HashmapTestContainsKey)
		{
			auto testPair = Hashmap<int, int>::PairType(5, 9001);
			Assert::IsFalse(intHash.ContainsKey(testPair.first));

			intHash.Insert(testPair);
			Assert::IsTrue(intHash.ContainsKey(testPair.first));

			intHash.Remove(testPair.first);
			Assert::IsFalse(intHash.ContainsKey(testPair.first));

			int a = 5;
			auto testPair2 = Hashmap<int*, int>::PairType(&a, 9001);
			Assert::IsFalse(pIntHash.ContainsKey(testPair2.first));

			pIntHash.Insert(testPair2);
			Assert::IsTrue(pIntHash.ContainsKey(testPair2.first));

			pIntHash.Remove(testPair2.first);
			Assert::IsFalse(pIntHash.ContainsKey(testPair2.first));

			char* b = "test";
			auto testPair3 = Hashmap<char*, int>::PairType(b, 9001);
			Assert::IsFalse(charHash.ContainsKey(testPair3.first));

			charHash.Insert(testPair3);
			Assert::IsTrue(charHash.ContainsKey(testPair3.first));

			charHash.Remove(testPair3.first);
			Assert::IsFalse(charHash.ContainsKey(testPair3.first));

			std::string d = "testing";
			auto testPair4 = Hashmap<std::string, int>::PairType(d, 9001);
			Assert::IsFalse(stringHash.ContainsKey(testPair4.first));

			stringHash.Insert(testPair4);
			Assert::IsTrue(stringHash.ContainsKey(testPair4.first));

			stringHash.Remove(testPair4.first);
			Assert::IsFalse(stringHash.ContainsKey(testPair4.first));

			Foo e(55);
			auto testPair5 = Hashmap<Foo, int>::PairType(e, 9001);
			Assert::IsFalse(FooHash.ContainsKey(testPair5.first));

			FooHash.Insert(testPair5);
			Assert::IsTrue(FooHash.ContainsKey(testPair5.first));

			FooHash.Remove(testPair5.first);
			Assert::IsFalse(FooHash.ContainsKey(testPair5.first));
		}

		TEST_METHOD(HashmapTestBegin)
		{
			auto testPair = Hashmap<int, int>::PairType(5, 9001);

			Assert::IsTrue(intHash.begin() == intHash.end());

			intHash.Insert(testPair);
			Assert::IsTrue(intHash.begin() != intHash.end());

			intHash.Remove(testPair.first);
			Assert::IsTrue(intHash.begin() == intHash.end());

			int a = 5;
			auto testPair2 = Hashmap<int*, int>::PairType(&a, 9001);

			Assert::IsTrue(pIntHash.begin() == pIntHash.end());

			pIntHash.Insert(testPair2);
			Assert::IsTrue(pIntHash.begin() != pIntHash.end());

			pIntHash.Remove(testPair2.first);
			Assert::IsTrue(pIntHash.begin() == pIntHash.end());

			char* b = "test";
			auto testPair3 = Hashmap<char*, int>::PairType(b, 9001);

			Assert::IsTrue(charHash.begin() == charHash.end());

			charHash.Insert(testPair3);
			Assert::IsTrue(charHash.begin() != charHash.end());

			charHash.Remove(testPair3.first);
			Assert::IsTrue(charHash.begin() == charHash.end());

			std::string d = "testing";
			auto testPair4 = Hashmap<std::string, int>::PairType(d, 9001);

			Assert::IsTrue(stringHash.begin() == stringHash.end());

			stringHash.Insert(testPair4);
			Assert::IsTrue(stringHash.begin() != stringHash.end());

			stringHash.Remove(testPair4.first);
			Assert::IsTrue(stringHash.begin() == stringHash.end());

			Foo e(55);
			auto testPair5 = Hashmap<Foo, int>::PairType(e, 9001);

			Assert::IsTrue(FooHash.begin() == FooHash.end());

			FooHash.Insert(testPair5);
			Assert::IsTrue(FooHash.begin() != FooHash.end());

			FooHash.Remove(testPair5.first);
			Assert::IsTrue(FooHash.begin() == FooHash.end());
		}

		TEST_METHOD(HashmapTestEnd)
		{
			auto testPair = Hashmap<int, int>::PairType(5, 9001);

			auto expression1 = [&] { *intHash.end(); };
			Assert::ExpectException<std::exception>(expression1);

			int a = 5;
			auto testPair2 = Hashmap<int*, int>::PairType(&a, 9001);

			auto expression2 = [&] { *pIntHash.end(); };
			Assert::ExpectException<std::exception>(expression2);

			char* b = "test";
			auto testPair3 = Hashmap<char*, int>::PairType(b, 9001);

			auto expression3 = [&] { *charHash.end(); };
			Assert::ExpectException<std::exception>(expression3);

			std::string d = "testing";
			auto testPair4 = Hashmap<std::string, int>::PairType(d, 9001);

			auto expression4 = [&] { *stringHash.end(); };
			Assert::ExpectException<std::exception>(expression4);

			Foo e(55);
			auto testPair5 = Hashmap<Foo, int>::PairType(e, 9001);

			auto expression5 = [&] { *FooHash.end(); };
			Assert::ExpectException<std::exception>(expression5);
		}


		TEST_METHOD(HashmapTestInsert)
		{
			Hashmap<int, int> intHashEmpty;
			auto testPair = Hashmap<int, int>::PairType(5, 9001);
			intHash.Insert(testPair);
			intHash.Insert(testPair);

			Assert::AreEqual(intHash.Size(), 1U);
			intHash = intHashEmpty;

			Hashmap<int*, int> pIntHashEmpty;
			int a = 5;
			auto testPair2 = Hashmap<int*, int>::PairType(&a, 9001);
			pIntHash.Insert(testPair2);
			pIntHash.Insert(testPair2);

			Assert::AreEqual(pIntHash.Size(), 1U);
			pIntHash = pIntHashEmpty;

			Hashmap<char*, int> charHashEmpty;
			char* b = "test";
			auto testPair3 = Hashmap<char*, int>::PairType(b, 9001);
			charHash.Insert(testPair3);
			charHash.Insert(testPair3);

			Assert::AreEqual(charHash.Size(), 1U);
			charHash = charHashEmpty;

			Hashmap<std::string, int> stringHashEmpty;
			std::string d = "testing";
			auto testPair4 = Hashmap<std::string, int>::PairType(d, 9001);
			stringHash.Insert(testPair4);
			stringHash.Insert(testPair4);

			Assert::AreEqual(stringHash.Size(), 1U);
			stringHash = stringHashEmpty;

			Hashmap<Foo, int, FHash> FooHashEmpty;
			Foo e(55);
			auto testPair5 = Hashmap<Foo, int>::PairType(e, 9001);
			FooHash.Insert(testPair5);
			FooHash.Insert(testPair5);

			Assert::AreEqual(FooHash.Size(), 1U);
			FooHash = FooHashEmpty;
		}

		TEST_METHOD(IteratorTestConstructor)
		{
			auto expression1 = [&] { *intHash.begin(); };
			auto expression2 = [&] { *intHash.end(); };

			Assert::ExpectException<std::exception>(expression1);
			Assert::ExpectException<std::exception>(expression2);

			auto expression3 = [&] { *pIntHash.begin(); };
			auto expression4 = [&] { *pIntHash.end(); };

			Assert::ExpectException<std::exception>(expression3);
			Assert::ExpectException<std::exception>(expression4);

			auto expression5 = [&] { *charHash.begin(); };
			auto expression6 = [&] { *charHash.end(); };

			Assert::ExpectException<std::exception>(expression5);
			Assert::ExpectException<std::exception>(expression6);

			auto expression7 = [&] { *stringHash.begin(); };
			auto expression8 = [&] { *stringHash.end(); };

			Assert::ExpectException<std::exception>(expression7);
			Assert::ExpectException<std::exception>(expression8);

			auto expression9 = [&] { *FooHash.begin(); };
			auto expression10 = [&] { *FooHash.end(); };

			Assert::ExpectException<std::exception>(expression9);
			Assert::ExpectException<std::exception>(expression10);
		}

		TEST_METHOD(IteratorTestCopy)
		{
			Hashmap<int, int> intHashEmpty;
			auto testPair = Hashmap<int, int>::PairType(5, 9001);
			auto testPair2 = Hashmap<int, int>::PairType(54, 42);
			intHash.Insert(testPair);
			intHash.Insert(testPair2);
			auto itr = intHash.begin();

			auto itr2(itr);
			Assert::IsTrue(itr == itr2);
			intHash = intHashEmpty;

			Hashmap<int*, int> pIntHashEmpty;
			int a = 5;
			int b = 7;
			auto testPair3 = Hashmap<int*, int>::PairType(&a, 9001);
			auto testPair4 = Hashmap<int*, int>::PairType(&b, 42);
			pIntHash.Insert(testPair3);
			pIntHash.Insert(testPair4);
			auto itr3 = pIntHash.begin();

			auto itr4(itr3);
			Assert::IsTrue(itr3 == itr4);
			pIntHash = pIntHashEmpty;

			Hashmap<char*, int> charHashEmpty;
			char* c = "test";
			char* d = "testing";
			auto testPair5 = Hashmap<char*, int>::PairType(c, 9001);
			auto testPair6 = Hashmap<char*, int>::PairType(d, 42);
			charHash.Insert(testPair5);
			charHash.Insert(testPair6);
			auto itr5 = charHash.begin();

			auto itr6(itr5);
			Assert::IsTrue(itr5 == itr6);
			charHash = charHashEmpty;

			Hashmap<std::string, int> stringHashEmpty;
			std::string e = "test";
			std::string f = "testing";
			auto testPair7 = Hashmap<std::string, int>::PairType(e, 9001);
			auto testPair8 = Hashmap<std::string, int>::PairType(f, 42);
			stringHash.Insert(testPair7);
			stringHash.Insert(testPair8);
			auto itr7 = stringHash.begin();

			auto itr8(itr7);
			Assert::IsTrue(itr7 == itr8);
			stringHash = stringHashEmpty;

			Hashmap<Foo, int, FHash> FooHashEmpty;
			Foo g(55);
			Foo h(69);
			auto testPair9 = Hashmap<Foo, int>::PairType(g, 9001);
			auto testPair10 = Hashmap<Foo, int>::PairType(h, 42);
			FooHash.Insert(testPair9);
			FooHash.Insert(testPair10);
			auto itr9 = FooHash.begin();

			auto itr10(itr9);
			Assert::IsTrue(itr9 == itr10);
			FooHash = FooHashEmpty;
		}


		TEST_METHOD(IteratorTestComparison)
		{
			Hashmap<int, int> intHashEmpty;
			auto testPair = Hashmap<int, int>::PairType(5, 9001);
			auto testPair2 = Hashmap<int, int>::PairType(54, 42);
			intHash.Insert(testPair);
			intHash.Insert(testPair2);
			auto itr = intHash.begin();

			auto itr2(itr);
			Assert::IsTrue(itr == itr2);
			Assert::IsFalse(itr != itr2);
			intHash = intHashEmpty;

			Hashmap<int*, int> pIntHashEmpty;
			int a = 5;
			int b = 7;
			auto testPair3 = Hashmap<int*, int>::PairType(&a, 9001);
			auto testPair4 = Hashmap<int*, int>::PairType(&b, 42);
			pIntHash.Insert(testPair3);
			pIntHash.Insert(testPair4);
			auto itr3 = pIntHash.begin();

			auto itr4(itr3);
			Assert::IsTrue(itr3 == itr4);
			Assert::IsFalse(itr3 != itr4);
			pIntHash = pIntHashEmpty;

			Hashmap<char*, int> charHashEmpty;
			char* c = "test";
			char* d = "testing";
			auto testPair5 = Hashmap<char*, int>::PairType(c, 9001);
			auto testPair6 = Hashmap<char*, int>::PairType(d, 42);
			charHash.Insert(testPair5);
			charHash.Insert(testPair6);
			auto itr5 = charHash.begin();

			auto itr6(itr5);
			Assert::IsTrue(itr5 == itr6);
			Assert::IsFalse(itr5 != itr6);
			charHash = charHashEmpty;

			Hashmap<std::string, int> stringHashEmpty;
			std::string e = "test";
			std::string f = "testing";
			auto testPair7 = Hashmap<std::string, int>::PairType(e, 9001);
			auto testPair8 = Hashmap<std::string, int>::PairType(f, 42);
			stringHash.Insert(testPair7);
			stringHash.Insert(testPair8);
			auto itr7 = stringHash.begin();

			auto itr8(itr7);
			Assert::IsTrue(itr7 == itr8);
			Assert::IsFalse(itr7 != itr8);
			stringHash = stringHashEmpty;

			Hashmap<Foo, int, FHash> FooHashEmpty;
			Foo g(55);
			Foo h(67);
			auto testPair9 = Hashmap<Foo, int>::PairType(g, 9001);
			auto testPair10 = Hashmap<Foo, int>::PairType(h, 42);
			FooHash.Insert(testPair9);
			FooHash.Insert(testPair10);
			auto itr9 = charHash.begin();

			auto itr10(itr9);
			Assert::IsTrue(itr9 == itr10);
			Assert::IsFalse(itr9 != itr10);
			FooHash = FooHashEmpty;
		}

		TEST_METHOD(IteratorTestIncrement)
		{
			Hashmap<int, int> intHashEmpty;
			auto testPair = Hashmap<int, int>::PairType(5, 9001);
			auto testPair2 = Hashmap<int, int>::PairType(54, 42);
			auto testPair3 = Hashmap<int, int>::PairType(566, 1088);
			intHash.Insert(testPair);
			auto itr = intHash.begin();

			Assert::IsTrue(*(itr++) == testPair);
			++itr;

			auto expression1 = [&] { itr.operator++(); };
			Assert::ExpectException<std::exception>(expression1);

			auto itr2 = intHash.end();
			auto itr3 = intHash.end();

			auto expression2 = [&] { itr2.operator++(); };
			auto expression3 = [&] { itr3.operator++(0); };

			Assert::ExpectException<std::exception>(expression2);
			Assert::ExpectException<std::exception>(expression3);
			intHash = intHashEmpty;

			Hashmap<int*, int> pIntHashEmpty;
			int a = 5;
			int b = 7;
			int c = 55;
			auto testPair4 = Hashmap<int*, int>::PairType(&a, 9001);
			auto testPair5 = Hashmap<int*, int>::PairType(&b, 42);
			auto testPair6 = Hashmap<int*, int>::PairType(&c, 1088);
			pIntHash.Insert(testPair4);
			auto itr4 = pIntHash.begin();

			Assert::IsTrue(*(itr4++) == testPair4);
			++itr4;

			auto expression4 = [&] { itr4.operator++(); };
			Assert::ExpectException<std::exception>(expression4);

			auto itr5 = pIntHash.end();
			auto itr6 = pIntHash.end();

			auto expression5 = [&] { itr5.operator++(); };
			auto expression6 = [&] { itr6.operator++(0); };

			Assert::ExpectException<std::exception>(expression5);
			Assert::ExpectException<std::exception>(expression6);
			pIntHash = pIntHashEmpty;

			Hashmap<char*, int> charHashEmpty;
			char* d = "test";
			char* e = "testing";
			char* f = "TESTING";
			auto testPair7 = Hashmap<char*, int>::PairType(d, 9001);
			auto testPair8 = Hashmap<char*, int>::PairType(e, 42);
			auto testPair9 = Hashmap<char*, int>::PairType(f, 1088);
			charHash.Insert(testPair7);
			auto itr7 = charHash.begin();

			Assert::IsTrue(*(itr7++) == testPair7);
			++itr7;

			auto expression7 = [&] { itr7.operator++(); };
			Assert::ExpectException<std::exception>(expression7);

			auto itr8 = charHash.end();
			auto itr9 = charHash.end();

			auto expression8 = [&] { itr8.operator++(); };
			auto expression9 = [&] { itr9.operator++(0); };

			Assert::ExpectException<std::exception>(expression8);
			Assert::ExpectException<std::exception>(expression9);
			charHash = charHashEmpty;

			Hashmap<std::string, int> stringHashEmpty;
			std::string h = "test";
			std::string i = "testing";
			std::string j = "TESTING";
			auto testPair10 = Hashmap<std::string, int>::PairType(h, 9001);
			auto testPair11 = Hashmap<std::string, int>::PairType(i, 42);
			auto testPair12 = Hashmap<std::string, int>::PairType(j, 1088);
			stringHash.Insert(testPair10);
			auto itr10 = stringHash.begin();

			Assert::IsTrue(*(itr10++) == testPair10);
			++itr10;

			auto expression10 = [&] { itr10.operator++(); };
			Assert::ExpectException<std::exception>(expression10);

			auto itr11 = stringHash.end();
			auto itr12 = stringHash.end();

			auto expression11 = [&] { itr11.operator++(); };
			auto expression12 = [&] { itr12.operator++(0); };

			Assert::ExpectException<std::exception>(expression11);
			Assert::ExpectException<std::exception>(expression12);
			stringHash = stringHashEmpty;

			Hashmap<Foo, int, FHash> FooHashEmpty;
			Foo k(44);
			auto testPair13 = Hashmap<Foo, int>::PairType(k, 9001);
			FooHash.Insert(testPair13);
			auto itr13 = FooHash.begin();

			Assert::IsTrue(*(itr13++) == testPair13);
			++itr13;

			auto expression13 = [&] { itr13.operator++(); };
			Assert::ExpectException<std::exception>(expression13);

			auto itr14 = FooHash.end();
			auto itr15 = FooHash.end();

			auto expression14 = [&] { itr14.operator++(); };
			auto expression15 = [&] { itr15.operator++(0); };

			Assert::ExpectException<std::exception>(expression14);
			Assert::ExpectException<std::exception>(expression15);
			FooHash = FooHashEmpty;
		}

		TEST_METHOD(IteratorTestDereference)
		{
			Hashmap<int, int>::Iterator intHashItr;
			auto expression1 = [&] { intHash.end().operator*(); };
			auto expression2 = [&] { intHashItr.operator*(); };
			auto expression3 = [&] { intHash.end().operator->(); };
			auto expression4 = [&] { intHashItr.operator->(); };

			Assert::ExpectException<std::exception>(expression1);
			Assert::ExpectException<std::exception>(expression2);
			Assert::ExpectException<std::exception>(expression3);
			Assert::ExpectException<std::exception>(expression4);

			Hashmap<int*, int>::Iterator pIntHashItr;
			auto expression5 = [&] { pIntHash.end().operator*(); };
			auto expression6 = [&] { pIntHashItr.operator*(); };
			auto expression7 = [&] { pIntHash.end().operator->(); };
			auto expression8 = [&] { pIntHashItr.operator->(); };

			Assert::ExpectException<std::exception>(expression5);
			Assert::ExpectException<std::exception>(expression6);
			Assert::ExpectException<std::exception>(expression7);
			Assert::ExpectException<std::exception>(expression8);

			Hashmap<char*, int>::Iterator charHashItr;
			auto expression9 = [&] { charHash.end().operator*(); };
			auto expression10 = [&] { charHashItr.operator*(); };
			auto expression11 = [&] { charHash.end().operator->(); };
			auto expression12 = [&] { charHashItr.operator->(); };

			Assert::ExpectException<std::exception>(expression9);
			Assert::ExpectException<std::exception>(expression10);
			Assert::ExpectException<std::exception>(expression11);
			Assert::ExpectException<std::exception>(expression12);

			Hashmap<std::string, int>::Iterator stringHashItr;
			auto expression13 = [&] { stringHash.end().operator*(); };
			auto expression14 = [&] { stringHashItr.operator*(); };
			auto expression15 = [&] { stringHash.end().operator->(); };
			auto expression16 = [&] { stringHashItr.operator->(); };

			Assert::ExpectException<std::exception>(expression13);
			Assert::ExpectException<std::exception>(expression14);
			Assert::ExpectException<std::exception>(expression15);
			Assert::ExpectException<std::exception>(expression16);

			Hashmap<Foo, int, FHash>::Iterator FooHashItr;
			auto expression17 = [&] { stringHash.end().operator*(); };
			auto expression18 = [&] { stringHashItr.operator*(); };
			auto expression19 = [&] { stringHash.end().operator->(); };
			auto expression20 = [&] { stringHashItr.operator->(); };

			Assert::ExpectException<std::exception>(expression17);
			Assert::ExpectException<std::exception>(expression18);
			Assert::ExpectException<std::exception>(expression19);
			Assert::ExpectException<std::exception>(expression20);
		}
	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState HashmapTest::sStartMemState;
#endif
}