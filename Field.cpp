#include "Field.h"
#include <algorithm>

Field::Field(int const& width, int const& height, std::function<BlockColor(pair<int, int> point)> colorgen) : width(width), height(height) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pair<int, int> point;
			point.first = i;
			point.second = j;
			blocks[i][j] = Block(colorgen(point));
		}
	}
}