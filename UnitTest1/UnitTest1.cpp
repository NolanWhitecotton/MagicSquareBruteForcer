#include "pch.h"
#include "CppUnitTest.h"

#include "../MagicSquare/src/MagicSquareBruteForcer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1{
	TEST_CLASS(UnitTest1){
	public:

		TEST_METHOD(TestGenericTemplateConstructor) {
			//construct
			SquareTemplate *st = new SquareTemplate(true, 3, 1, 9, false); //-m 9 -c -s 3

			//asserts
			Assert::AreEqual(st->getIsCompact(), true);
			Assert::AreEqual(st->getSquareSize(), 3);
			Assert::AreEqual(st->getRecurMax(), 9);
			Assert::AreEqual(st->getRecurOffset(), 1);
			Assert::AreEqual(st->getShowIdentical(), false);
		}

		TEST_METHOD(TestSquareIntConstructor) {
			//prep
			SquareTemplate *st = new SquareTemplate(true, 3, 1, 9, false); //-m 9 -c -s 3

			//construct
			Square* sq = new Square(3, st);

			//asserts
			Assert::AreEqual(sq->getSize(), 3);
			Assert::AreEqual(sq->getTemplate()==st,true);
		}

		TEST_METHOD(TestSquareAdd) {
			//prep
			SquareTemplate* st = new SquareTemplate(true, 3, 1, 9, false); //-m 9 -c -s 3
			Square* sq = new Square(3, st);

			//test
			sq->add(1);
			sq->add(5);

			//asserts
			Assert::AreEqual(sq->getAddedNumCount(), 2);
			Assert::AreEqual(sq->getNum(0), 1);
			Assert::AreEqual(sq->getNum(1), 5);
		}
	};
}
