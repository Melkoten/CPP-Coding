#pragma once
#include <vector>
#include <functional>
#include "Blocks.h"
#include "SFML/Graphics.hpp"
using namespace std;
using namespace sf;
class Field {
	vector<vector<Block>> blocks; //first - height, second width
	int height;
	int width;
public:
	Field(int width, int height, std::function<BlockColor(pair<int, int> point)> colorGen);
	Block& curBlock(int const x, int const y) { return blocks[y][x]; }
	int const& getWidth() const { return width; }
	int const& getHeight() const { return height; }
};