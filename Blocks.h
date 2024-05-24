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
		explicit Block(BlockColor color) : color(color) {}
		BlockColor const& getcolor() const { return color; }
};