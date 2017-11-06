#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{

	TEST_CLASS(DatumTest)
	{
	public:
		typedef Datum::DatumType DatumType;
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


		TEST_METHOD(DatumTestConstructor)
		{
			Datum a(DatumType::INTEGER, 1U);
			auto expression1 = [&] { a.SetType(DatumType::INTEGER); };
			Assert::ExpectException<std::exception>(expression1);

			a.Reserve(1);
			a.Reserve(2);
			a.Set(5);
			a.Set(43, 4);
			int b = a.Get<int>();
			a.Remove();

			Assert::IsTrue(a.Type() == DatumType::INTEGER);
			Assert::AreNotEqual(a.Get<int>(), b);
		}

		TEST_METHOD(DatumTestCopy)
		{
			Datum iDatum(DatumType::INTEGER, 1U);
			iDatum.Set(100, 40);
			Datum iCopy(iDatum);
			Assert::AreEqual(iDatum.Get<int>(0), iCopy.Get<int>(0));

			int* a = new int[10];
			iCopy.SetStorage(a, 10U);

			Datum iCopy2(DatumType::INTEGER), iCopy3(DatumType::INTEGER);
			iCopy3 = iCopy;
			delete[] a;

			Datum fDatum(DatumType::FLOAT, 1U);
			fDatum.Set(100.0f, 40U);
			Datum fCopy(fDatum);
			Assert::AreEqual(fDatum.Get<float>(0), fCopy.Get<float>(0));

			float* b = new float[10];
			fCopy.SetStorage(b, 10U);

			Datum fCopy2(DatumType::FLOAT), fCopy3(DatumType::FLOAT);
			fCopy3 = fCopy;
			delete[] b;

			Datum vDatum(DatumType::VECTOR, 1U);
			vDatum.Set(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f), 40);
			Datum vCopy(vDatum);
			Assert::IsTrue(vDatum.Get<glm::vec4>(0) == vCopy.Get<glm::vec4>(0));

			glm::vec4* c = new glm::vec4[10];
			vCopy.SetStorage(c, 10U);

			Datum vCopy2(DatumType::VECTOR), vCopy3(DatumType::VECTOR);
			vCopy3 = vCopy;
			delete[] c;

			Datum mDatum(DatumType::MATRIX, 1U);
			mDatum.Set(glm::mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f), 40);
			Datum mCopy(mDatum);
			Assert::IsTrue(mDatum.Get<glm::mat4>(0) == mCopy.Get<glm::mat4>(0));

			glm::mat4* d = new glm::mat4[10];
			mCopy.SetStorage(d, 10U);

			Datum mCopy2(DatumType::MATRIX), mCopy3(DatumType::MATRIX);
			mCopy3 = mCopy;
			delete[] d;

			Datum sDatum(DatumType::STRING, 1U);
			sDatum.Set(std::string("Hello"), 40U);
			Datum sCopy(sDatum);
			Assert::IsTrue(sDatum.Get<std::string>(0) == sCopy.Get<std::string>(0));

			std::string* e = new std::string[10];
			sCopy.SetStorage(e, 10U);

			Datum sCopy2(DatumType::STRING), sCopy3(DatumType::STRING);
			sCopy3 = sCopy;
			delete[] e;

			Datum pDatum(DatumType::POINTER, 1);
			RTTI* pRTTI = nullptr;
			pDatum.Set(pRTTI, 40U);
			Datum pCopy(pDatum);
			Assert::IsTrue(pDatum.Get<RTTI*>(0) == pCopy.Get<RTTI*>(0));

			RTTI** f = new RTTI*[10];
			pCopy.SetStorage(f, 10U);

			Datum pCopy2(DatumType::POINTER), pCopy3(DatumType::POINTER);
			pCopy3 = pCopy;
			delete[] f;
		}

		TEST_METHOD(DatumTestAssignment)
		{
			Datum iDatum(DatumType::INTEGER, 1U);
			Datum iCopy(DatumType::INTEGER);

			int a = 5;
			iCopy = a;
			Assert::AreEqual(iCopy.Get<int>(), a);

			iDatum = a;
			Assert::AreEqual(iCopy.Get<int>(), a);

			Datum fDatum(DatumType::FLOAT, 1U);
			Datum fCopy(DatumType::FLOAT, 1U);

			float b = 5.0f;
			fCopy = b;
			Assert::AreEqual(fCopy.Get<float>(), b);

			fDatum = b;
			Assert::AreEqual(fCopy.Get<float>(), b);

			Datum vDatum(DatumType::VECTOR, 1U);
			Datum vCopy(DatumType::VECTOR, 1U);

			glm::vec4 c = glm::vec4(1.0f, 2.0, 3.0f, 4.0f);
			vCopy = c;
			Assert::IsTrue(vCopy.Get<glm::vec4>() == c);

			vDatum = c;
			Assert::IsTrue(vCopy.Get<glm::vec4>() == c);

			Datum mDatum(DatumType::MATRIX, 1U);
			Datum mCopy(DatumType::MATRIX, 1U);

			glm::mat4 d = glm::mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
			mCopy = d;
			Assert::IsTrue(mCopy.Get<glm::mat4>() == d);

			mDatum = d;
			Assert::IsTrue(mCopy.Get<glm::mat4>() == d);

			Datum sDatum(DatumType::STRING, 1U);
			Datum sCopy(DatumType::STRING, 1U);

			std::string e = "Hello";
			sCopy = e;
			Assert::IsTrue(sCopy.Get<std::string>() == e);

			sDatum = e;
			Assert::IsTrue(sCopy.Get<std::string>() == e);

			Datum pDatum(DatumType::POINTER, 1U);
			Datum pCopy(DatumType::POINTER, 1U);

			RTTI* f = nullptr;
			pCopy = f;
			Assert::IsTrue(pCopy.Get<RTTI*>() == f);

			pDatum = f;
			Assert::IsTrue(pCopy.Get<RTTI*>() == f);
		}

		TEST_METHOD(DatumTestClear)
		{
			Datum iDatum(DatumType::INTEGER, 3U);
			iDatum.Set(1);
			iDatum.Set(2, 1);
			iDatum.Set(3, 2);
			iDatum.Clear();
			Assert::AreEqual(iDatum.Size(), 0U);

			Datum fDatum(DatumType::FLOAT, 3U);
			fDatum.Set(1.0f);
			fDatum.Set(2.0f, 1);
			fDatum.Set(3.0f, 2);
			fDatum.Clear();
			Assert::AreEqual(fDatum.Size(), 0U);

			Datum vDatum(DatumType::VECTOR, 3U);
			vDatum.Set(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f));
			vDatum.Set(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f), 1);
			vDatum.Set(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f), 2);
			vDatum.Clear();
			Assert::AreEqual(vDatum.Size(), 0U);

			Datum mDatum(DatumType::MATRIX, 3U);
			mDatum.Set(glm::mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));
			mDatum.Set(glm::mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f), 1);
			mDatum.Set(glm::mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f), 2);
			mDatum.Clear();
			Assert::AreEqual(mDatum.Size(), 0U);

			Datum sDatum(DatumType::STRING, 3U);
			sDatum.Set(std::string("Hello"));
			sDatum.Set(std::string("Hello~"), 1);
			sDatum.Set(std::string("Hello!"), 2);
			sDatum.Clear();
			Assert::AreEqual(sDatum.Size(), 0U);

			Datum pDatum(DatumType::POINTER, 3U);
			RTTI* pRTTI = nullptr;
			pDatum.Set(pRTTI);
			pDatum.Set(pRTTI, 1);
			pDatum.Set(pRTTI, 2);
			pDatum.Clear();
			Assert::AreEqual(pDatum.Size(), 0U);
		}

		TEST_METHOD(DatumTestSetStorage)
		{
			Datum iDatum(DatumType::INTEGER);

			int* a = new int[10];
			iDatum.SetStorage(a, 10);
			Assert::AreEqual(iDatum.Size(), 10U);
			delete[] a;

			Datum fDatum(DatumType::FLOAT);
			float* b = new float[10];

			fDatum.SetStorage(b, 10);
			Assert::AreEqual(fDatum.Size(), 10U);
			delete[] b;

			Datum vDatum(DatumType::VECTOR);
			glm::vec4* c = new glm::vec4[10];

			vDatum.SetStorage(c, 10);
			Assert::AreEqual(vDatum.Size(), 10U);
			delete[] c;

			Datum mDatum(DatumType::MATRIX);
			glm::mat4* d = new glm::mat4[10];

			mDatum.SetStorage(d, 10);
			Assert::AreEqual(mDatum.Size(), 10U);
			delete[] d;

			Datum sDatum(DatumType::STRING);
			std::string* e = new std::string[10];

			sDatum.SetStorage(e, 10);
			Assert::AreEqual(sDatum.Size(), 10U);
			delete[] e;

			Datum pDatum(DatumType::POINTER);
			RTTI* f = nullptr;
			RTTI** g = &f;
			RTTI** h = new RTTI*[10];

			pDatum.SetStorage(g, 10);
			Assert::AreEqual(mDatum.Size(), 10U);
			delete[] h;
		}

		TEST_METHOD(DatumTestDatumComparison)
		{
			Datum iDatum(DatumType::INTEGER, 3U);
			Datum iDatum2(DatumType::INTEGER);

			Assert::IsTrue(iDatum != iDatum2);
			Assert::IsFalse(iDatum == iDatum2);

			iDatum.Set(1);
			iDatum2 = iDatum;
			Assert::IsTrue(iDatum == iDatum2);
			Assert::IsFalse(iDatum != iDatum2);

			iDatum.Set(2, 1);
			iDatum2.Set(3, 1);
			Assert::IsTrue(iDatum != iDatum2);
			Assert::IsFalse(iDatum == iDatum2);

			Datum fDatum(DatumType::FLOAT, 3U);
			Datum fDatum2(DatumType::FLOAT);

			Assert::IsTrue(fDatum != fDatum2);
			Assert::IsFalse(fDatum == fDatum2);

			fDatum.Set(1.0f);
			fDatum2 = fDatum;
			Assert::IsTrue(fDatum == fDatum2);
			Assert::IsFalse(fDatum != fDatum2);

			fDatum.Set(2.0f, 1);
			fDatum2.Set(3.0f, 1);
			Assert::IsTrue(fDatum != fDatum2);
			Assert::IsFalse(fDatum == fDatum2);

			Datum vDatum(DatumType::VECTOR, 3U);
			Datum vDatum2(DatumType::VECTOR);

			Assert::IsTrue(vDatum != vDatum2);
			Assert::IsFalse(vDatum == vDatum2);

			vDatum.Set(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
			vDatum2 = vDatum;
			Assert::IsTrue(vDatum == vDatum2);
			Assert::IsFalse(vDatum != vDatum2);

			vDatum.Set(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f), 1);
			vDatum2.Set(glm::vec4(5.0f, 6.0f, 7.0f, 8.0f), 1);
			Assert::IsTrue(vDatum != vDatum2);
			Assert::IsFalse(vDatum == vDatum2);

			Datum mDatum(DatumType::MATRIX, 3U);
			Datum mDatum2(DatumType::MATRIX);

			Assert::IsTrue(mDatum != mDatum2);
			Assert::IsFalse(mDatum == mDatum2);

			mDatum.Set(glm::mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));
			mDatum2 = mDatum;
			Assert::IsTrue(mDatum == mDatum2);
			Assert::IsFalse(mDatum != mDatum2);

			mDatum.Set(glm::mat4(100.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f), 1);
			mDatum2.Set(glm::mat4(1000.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f), 1);
			Assert::IsTrue(mDatum != mDatum2);
			Assert::IsFalse(mDatum == mDatum2);

			Datum sDatum(DatumType::STRING, 3U);
			Datum sDatum2(DatumType::STRING);

			Assert::IsTrue(sDatum != sDatum2);
			Assert::IsFalse(sDatum == sDatum2);

			sDatum.Set(std::string("Hello"));
			sDatum2 = sDatum;
			Assert::IsTrue(sDatum == sDatum2);
			Assert::IsFalse(sDatum != sDatum2);

			sDatum.Set(std::string("Hello~"), 1);
			sDatum2.Set(std::string("Hello!"), 1);
			Assert::IsTrue(sDatum != sDatum2);
			Assert::IsFalse(sDatum == sDatum2);

			Datum pDatum(DatumType::POINTER, 3U);
			Datum pDatum2(DatumType::POINTER);
			RTTI* pRTTI = nullptr;

			Assert::IsTrue(pDatum != pDatum2);
			Assert::IsFalse(pDatum == pDatum2);

			pDatum.Set(pRTTI);
			pDatum2 = pDatum;
			auto expression1 = [&] { pDatum2 == pDatum; };
			auto expression2 = [&] { pDatum2 != pDatum; };
			Assert::ExpectException<std::exception>(expression1);
			Assert::ExpectException<std::exception>(expression2);
		}

		TEST_METHOD(DatumTestScalarComparison)
		{
			Datum iDatum(DatumType::INTEGER);
			int a = 5;

			iDatum.Set(a);
			Assert::IsTrue(iDatum == a);
			Assert::IsFalse(iDatum != a);

			Datum fDatum(DatumType::FLOAT);
			float b = 5.0f;

			fDatum.Set(b);
			Assert::IsTrue(fDatum == b);
			Assert::IsFalse(fDatum != b);

			Datum vDatum(DatumType::VECTOR);
			glm::vec4 c = glm::vec4(1.0f, 2.0f, 3.0f, 4.0f);

			vDatum.Set(c);
			Assert::IsTrue(vDatum == c);
			Assert::IsFalse(vDatum != c);

			Datum mDatum(DatumType::MATRIX);
			glm::mat4 d = glm::mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

			mDatum.Set(d);
			Assert::IsTrue(mDatum == d);
			Assert::IsFalse(mDatum != d);

			Datum sDatum(DatumType::STRING);
			std::string e = "Hello";

			sDatum.Set(e);
			Assert::IsTrue(sDatum == e);
			Assert::IsFalse(sDatum != e);

			Datum pDatum(DatumType::POINTER);
			RTTI* f = nullptr;

			pDatum.Set(f);
			Assert::IsTrue(pDatum == f);
			Assert::IsFalse(pDatum != f);
		}

		TEST_METHOD(DatumTestPushBack)
		{
			Datum iDatum(DatumType::INTEGER);
			iDatum.PushBack(1);
			iDatum.PushBack(2);
			Assert::AreEqual(iDatum.Size(), 2U);
			Assert::AreEqual(iDatum.Get<int>(1), 2);

			Datum fDatum(DatumType::FLOAT);
			fDatum.PushBack(1.0f);
			fDatum.PushBack(2.0f);
			Assert::AreEqual(fDatum.Size(), 2U);
			Assert::AreEqual(fDatum.Get<float>(1), 2.0f);

			Datum vDatum(DatumType::VECTOR);
			vDatum.PushBack(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f));
			vDatum.PushBack(glm::vec4(5.0f, 6.0f, 7.0f, 8.0f));
			Assert::AreEqual(vDatum.Size(), 2U);
			Assert::IsTrue(vDatum.Get<glm::vec4>(1) == glm::vec4(5.0f, 6.0f, 7.0f, 8.0f));

			Datum mDatum(DatumType::MATRIX);
			mDatum.PushBack(glm::mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));
			mDatum.PushBack(glm::mat4(100.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));
			Assert::AreEqual(mDatum.Size(), 2U);
			Assert::IsTrue(mDatum.Get<glm::mat4>(1) == glm::mat4(100.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));

			Datum sDatum(DatumType::STRING);
			sDatum.PushBack(std::string("Hello"));
			sDatum.PushBack(std::string("Hello!"));
			Assert::AreEqual(sDatum.Size(), 2U);
			Assert::AreEqual(sDatum.Get<std::string>(1), std::string("Hello!"));

			Datum pDatum(DatumType::POINTER);
			RTTI* pRTTI = nullptr;
			pDatum.PushBack(pRTTI);
			pDatum.PushBack(pRTTI);
			Assert::AreEqual(pDatum.Size(), 2U);
			Assert::IsTrue(pDatum.Get<RTTI*>(1) == pRTTI);
		}

		TEST_METHOD(DatumTestPopBack)
		{
			Datum iDatum(DatumType::INTEGER);
			iDatum.PopBack();
			Assert::AreEqual(iDatum.Size(), 0U);

			Datum fDatum(DatumType::FLOAT);
			fDatum.PopBack();
			Assert::AreEqual(fDatum.Size(), 0U);

			Datum vDatum(DatumType::VECTOR);
			vDatum.PopBack();
			Assert::AreEqual(vDatum.Size(), 0U);

			Datum mDatum(DatumType::MATRIX);
			mDatum.PopBack();
			Assert::AreEqual(mDatum.Size(), 0U);

			Datum sDatum(DatumType::STRING);
			sDatum.PopBack();
			Assert::AreEqual(sDatum.Size(), 0U);

			Datum pDatum(DatumType::POINTER);
			pDatum.PopBack();
			Assert::AreEqual(pDatum.Size(), 0U);
		}

		TEST_METHOD(DatumTestRemove)
		{
			Datum iDatum(DatumType::INTEGER, 5U);

			auto expression1 = [&] { iDatum.Get<int>(4); };
			Assert::ExpectException<std::out_of_range>(expression1);

			iDatum.PushBack(1);
			iDatum.PushBack(2);
			iDatum.PushBack(3);
			iDatum.PushBack(4);
			iDatum.PushBack(5);
			iDatum.Remove(2);
			Assert::AreEqual(iDatum.Get<int>(2), 4);

			Datum fDatum(DatumType::FLOAT, 5U);
			auto expression3 = [&] { fDatum.Get<float>(4); };
			Assert::ExpectException<std::out_of_range>(expression3);

			fDatum.PushBack(1.0f);
			fDatum.PushBack(2.0f);
			fDatum.PushBack(3.0f);
			fDatum.PushBack(4.0f);
			fDatum.PushBack(5.0f);
			fDatum.Remove(2);
			Assert::AreEqual(fDatum.Get<float>(2), 4.0f);

			Datum vDatum(DatumType::VECTOR, 5U);
			auto expression5 = [&] { vDatum.Get<glm::vec4>(4); };
			Assert::ExpectException<std::out_of_range>(expression5);

			vDatum.PushBack(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f));
			vDatum.PushBack(glm::vec4(10.0f, 2.0f, 3.0f, 40.0f));
			vDatum.PushBack(glm::vec4(100.0f, 2.0f, 3.0f, 40.0f));
			vDatum.PushBack(glm::vec4(1000.0f, 2.0f, 3.0f, 400.0f));
			vDatum.PushBack(glm::vec4(10000.0f, 2.0f, 3.0f, 4000.0f));
			vDatum.Remove(2);
			Assert::IsTrue(vDatum.Get<glm::vec4>(2) == glm::vec4(1000.0f, 2.0f, 3.0f, 400.0f));

			Datum mDatum(DatumType::MATRIX, 5U);
			auto expression7 = [&] { mDatum.Get<glm::mat4>(4); };
			Assert::ExpectException<std::out_of_range>(expression7);

			mDatum.PushBack(glm::mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));
			mDatum.PushBack(glm::mat4(10.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));
			mDatum.PushBack(glm::mat4(100.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));
			mDatum.PushBack(glm::mat4(1000.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));
			mDatum.PushBack(glm::mat4(10000.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));
			mDatum.Remove(2);
			Assert::IsTrue(mDatum.Get<glm::mat4>(2) == glm::mat4(1000.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));

			Datum sDatum(DatumType::STRING, 5U);
			auto expression9 = [&] { sDatum.Get<std::string>(4); };
			Assert::ExpectException<std::out_of_range>(expression9);

			sDatum.PushBack(std::string("Hello"));
			sDatum.PushBack(std::string("Hello~"));
			sDatum.PushBack(std::string("Hello!"));
			sDatum.PushBack(std::string("Hello@"));
			sDatum.PushBack(std::string("Hello%"));
			sDatum.Remove(2);
			Assert::AreEqual(sDatum.Get<std::string>(2), std::string("Hello@"));

			Datum pDatum(DatumType::POINTER, 5U);
			RTTI* pRTTI = nullptr;
			auto expression11 = [&] { pDatum.Get<RTTI*>(4); };
			Assert::ExpectException<std::out_of_range>(expression11);

			pDatum.PushBack(pRTTI);
			pDatum.PushBack(pRTTI);
			pDatum.PushBack(pRTTI);
			pDatum.PushBack(pRTTI);
			pDatum.PushBack(pRTTI);
			pDatum.Remove(2);
			Assert::IsTrue(pDatum.Get<RTTI*>(2) == pRTTI);
			Assert::AreEqual(pDatum.Size(), 4U);
		}

		TEST_METHOD(DatumTestSet)
		{
			Datum iDatum;
			iDatum.Set(1);
			iDatum.Set(2,1);
			Assert::AreEqual(iDatum.Get<int>(), 1);

			Datum fDatum;
			fDatum.Set(1.0f);
			fDatum.Set(2.0f, 1);
			Assert::AreEqual(fDatum.Get<float>(), 1.0f);

			Datum vDatum;
			vDatum.Set(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f));
			vDatum.Set(glm::vec4(5.0f, 6.0f, 7.0f, 8.0f), 1);
			Assert::IsTrue(vDatum.Get<glm::vec4>() == glm::vec4(1.0f, 2.0f, 3.0f, 4.0f));

			Datum mDatum;
			mDatum.Set(glm::mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));
			mDatum.Set(glm::mat4(1000.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f), 1);
			Assert::IsTrue(mDatum.Get<glm::mat4>() == glm::mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));

			Datum sDatum;
			sDatum.Set(std::string("Hello"));
			sDatum.Set(std::string("Hello!"), 1);
			Assert::AreEqual(sDatum.Get<std::string>(), std::string("Hello"));

			Datum pDatum;
			RTTI* pRTTI = nullptr;
			pDatum.Set(pRTTI);
			Assert::IsTrue(pDatum.Get<RTTI*>() == pRTTI);
		}

		TEST_METHOD(DatumTestSetFromString)
		{
			Datum iDatum(DatumType::INTEGER);
			iDatum.SetFromString("123");
			Assert::AreEqual(iDatum.Get<int>(), 123);

			Datum fDatum(DatumType::FLOAT);
			fDatum.SetFromString("1.0");
			Assert::AreEqual(fDatum.Get<float>(), 1.0f);

			Datum vDatum(DatumType::VECTOR);
			vDatum.SetFromString("1.0 2.0 3.0 4.0");
			Assert::IsTrue(vDatum.Get<glm::vec4>() == glm::vec4(1.0f, 2.0f, 3.0f, 4.0f));

			Datum mDatum(DatumType::MATRIX);
			mDatum.SetFromString("1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0 10.0 11.0 12.0 13.0 14.0 15.0 16.0");
			Assert::IsTrue(mDatum.Get<glm::mat4>() == glm::mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));

			Datum sDatum(DatumType::STRING);
			sDatum.SetFromString("Hello");
			Assert::AreEqual(sDatum.Get<std::string>(), std::string("Hello"));

			Datum pDatum(DatumType::POINTER);
			auto expression1 = [&] { pDatum.SetFromString(std::string("Exception.")); };
			Assert::ExpectException<std::exception>(expression1);
		}

		TEST_METHOD(DatumTestToString)
		{
			Datum unknownDatum(DatumType::UNKNOWN);
			auto expression1 = [&] { unknownDatum.ToString(0); };
			Assert::ExpectException<std::exception>(expression1);

			Datum iDatum(DatumType::INTEGER);
			iDatum.Set(123);
			Assert::IsTrue(iDatum.ToString() == "123");

			Datum fDatum(DatumType::FLOAT);
			fDatum.Set(123.0f);
			Assert::IsTrue(fDatum.ToString() == "123.000000");

			Datum vDatum(DatumType::VECTOR);
			vDatum.Set(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f));
			Assert::IsTrue(vDatum.ToString() == "vec4(1.000000, 2.000000, 3.000000, 4.000000)");

			Datum mDatum(DatumType::MATRIX);
			mDatum.Set(glm::mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f));
			Assert::IsTrue(mDatum.ToString() == "mat4x4((1.000000, 2.000000, 3.000000, 4.000000), (5.000000, 6.000000, 7.000000, 8.000000), (9.000000, 10.000000, 11.000000, 12.000000), (13.000000, 14.000000, 15.000000, 16.000000))");

			Datum pDatum(DatumType::POINTER);
			RTTI* pRTTI = nullptr;
			pDatum.Set(pRTTI);
			auto expression2 = [&] { pDatum.ToString(0); };
			Assert::ExpectException<std::exception>(expression2);
		}
	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState DatumTest::sStartMemState;
#endif
}