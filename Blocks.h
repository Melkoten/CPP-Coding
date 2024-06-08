#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

using namespace std;
enum class BlockColor {
	NONDESTRUCT = 0,
	HP1,
	HP2,
	HP3
};

class Block {
private:
	BlockColor color=BlockColor::HP3;
	pair<int, int> position;
	pair<int, int> size;
	sf::RectangleShape image;
	int health = 3;
public:
	explicit Block(pair<int, int> position, pair<int, int> size);
	void ChangePos(pair<int, int> pos);
	void ChangeSize(pair<int, int> sz);
	void ChangeColor(BlockColor col);
	void ChangeImage(sf::RectangleShape img);
	pair<int, int> const GetPos() { return (this->position); }
	pair<int, int> const GetSize() { return (this->size); }
	BlockColor const GetColor() { return (this->color); }
	int const GetHealth() { return (this->health); }
	sf::RectangleShape GetImage() { return(this->image); };
	bool const CanDestroy();
	void DecreaseHP();
};