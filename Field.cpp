#include "Field.h"
#include <algorithm>
#include "SFML/Graphics.hpp"
using namespace sf;
Field::Field(int  width, int  height, std::function<BlockColor(pair<int, int> point)> colorgen) : width(width), height(height) {
	for (int i = 0; i < height; i++) {
		vector<Block> line;
		for (int j = 0; j < width; j++) {
			pair<int, int> point;
			point.first = i;
			point.second = j;
			line.push_back(Block(colorgen(point)));
		}
		blocks.push_back(line);
	}
}