#pragma once
//#include <array>
enum class BlockColor {
	GREEN = 0,
	BLUE,
	RED,
	YELLOW,
	PURPLY,
	NONE,
};

class Block {
	BlockColor color;
	public:
		BlockColor const& getcolor() const { return color; }
		Block(BlockColor color) : color(color) {}
};