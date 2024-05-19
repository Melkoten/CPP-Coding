#pragma once
#include <vector>
#include <functional>
#include "Blocks.h"
using namespace std;
class Field {
	vector<vector<Block>> blocks; //first - height, second width
	int height;
	int width;
public:
	Field(int const& width, int const& height, std::function<BlockColor(pair<int, int> point)> colorGen);
	Block& curBlock(int const x, int const y) { return blocks[y][x]; }
	int const& getWidth() const { return width; }
	int const& getHeight() const { return height; }
};