#pragma once
#include <stdint.h>

struct Location {
	int row;
	int column;

	Location(int row, int column) {
		this->row = row;
		this->column = column;
	}
};