#include "Square.h"
#include "Validators.h"

bool UniquenessValidator::run(const Square* sq) const {
	for (int i = 0; i < numPos - 1; i++) {
		if (sq->getNum(i) == sq->getNum(numPos - 1)) {
			return false;
		}
	}
	return true;
}

bool MirrorValidator::run(const Square* sq) const {
	return (sq->getNum(msmaller) < sq->getNum(mlarger));
}
