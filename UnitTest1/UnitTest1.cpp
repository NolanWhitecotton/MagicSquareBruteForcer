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
			Assert::AreEqual(true, st->getIsCompact());
			Assert::AreEqual(3, st->getSquareSize());
			Assert::AreEqual(9, st->getRecurMax());
			Assert::AreEqual(1, st->getRecurOffset());
			Assert::AreEqual(false, st->getShowIdentical());
		}

		TEST_METHOD(TestSquareIntConstructor) {
			//prep
			SquareTemplate *st = new SquareTemplate(true, 3, 1, 9, false); //-m 9 -c -s 3

			//construct
			Square* sq = new Square(3, st);

			//asserts
			Assert::AreEqual(3, sq->getSize());
			Assert::AreEqual(true, sq->getTemplate()==st);
		}

		TEST_METHOD(TestSquareAdd) {
			//prep
			SquareTemplate* st = new SquareTemplate(true, 3, 1, 9, false); //-m 9 -c -s 3
			Square* sq = new Square(3, st);

			//test
			sq->add(1);
			sq->add(5);

			//asserts
			Assert::AreEqual(2, sq->getAddedNumCount());
			Assert::AreEqual(1, sq->getNum(0));
			Assert::AreEqual(5, sq->getNum(1));
		}
	TEST_METHOD(TestRemove) {
			//setup square
			SquareTemplate* st = new SquareTemplate(true, 3, 1, 9, false); //-m 9 -c -s 3
			Square* sq = new Square(3, st);
			sq->add(2);
			sq->add(7);

			//check that it got added correctly
			Assert::AreEqual(2, sq->getAddedNumCount());
			
			//remove 7
			sq->removeLastAdd();
			
			//check that one got removed, and cache still isnt set
			Assert::AreEqual(1, sq->getAddedNumCount());
			Assert::AreEqual(0, sq->getLineSumCache());

			//add the 7 back and add a 6
			sq->add(7);
			sq->add(6);

			//check that linesum is now set
			Assert::AreEqual(15, sq->getLineSumCache());

			//remove the 6
			sq->removeLastAdd();

			//check that linesum is not set anymore
			Assert::AreEqual(0, sq->getLineSumCache());
		}
	};
}
