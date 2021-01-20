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
			Assert::AreEqual(sq->getSize(),3);
			
		}

		TEST_METHOD(test) {
			Assert::AreEqual(1, 1);
		}
	};
}
