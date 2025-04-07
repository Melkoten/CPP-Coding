#include "Blocks.h"

using namespace std;

Block::Block(pair<int, int> position, pair<int, int> size) {
	this->position = position;
	this->size = size;
	sf::Vector2f pos = sf::Vector2f(position.first, position.second);
	sf::Vector2f sz = sf::Vector2f(size.first, size.second);
	image = sf::RectangleShape(sz);
	image.setPosition(pos);
}
void Block::ChangePos(pair<int, int> pos) {
	position = pos;
	sf::Vector2f newpos = sf::Vector2f(pos.first, pos.second);
	image.setPosition(newpos);
}
void Block::ChangeSize(pair<int, int> sz) {
	this->size = sz;
	sf::Vector2f newsize = sf::Vector2f(sz.first, sz.second);
	image.setSize(newsize); //ne uveren tuta
}
void Block::ChangeImage(sf::RectangleShape img) {
	this->image = img;
}
void Block::ChangeColor(BlockColor col) {
	color = col;
	switch (col) {
	case (BlockColor::NONDESTRUCT):
		image.setFillColor(sf::Color::Cyan);
		break;
	case (BlockColor::HP1):
		image.setFillColor(sf::Color::Red);
		break;
	case (BlockColor::HP2):
		image.setFillColor(sf::Color::Yellow);
		break;
	case (BlockColor::HP3):
		image.setFillColor(sf::Color::Magenta);
		break;
	}
}
void Block::DecreaseHP() {
	int newhealth = this->GetHealth() - 1;
	this->health = newhealth;
	switch (newhealth) {
		case 0:
			this->ChangePos({ -1000,-1000 });
			break;
		case 1:
			this->ChangeColor(BlockColor::HP1);
			break;
		case 2:
			this->ChangeColor(BlockColor::HP2);
			break;
		case 3:
			this->ChangeColor(BlockColor::HP3);
			break;
	}
}
bool const Block::CanDestroy() {
	if (this->GetColor() == BlockColor::NONDESTRUCT) return false;
	else return true;
}