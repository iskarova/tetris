#include "block.h"
#include "position.h"

class LBlcok : public Block{

public: 
	LBlock() {
		id = 1;
		cells[0] = { Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2) };
	}
};