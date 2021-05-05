#include "Square.h"
#include "Validators.h"

bool UniquenessValidator::run(const Square* sq) const {
	for (int i = 0; i < numPos; i++) {
		if (sq->getNum(i) == sq->getNum(numPos)) {
			return false;
		}
	}
	return true;
}

bool MirrorValidator::run(const Square* sq) const {
	return (sq->getNum(msmaller) < sq->getNum(mlarger));
}
