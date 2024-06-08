#include "Plat.h"

using namespace std;
Plat::Plat(pair<int, int> position) {
	this->position = position;
	sf::Vector2f pos = sf::Vector2f(position.first, position.second);
	sf::Vector2f sz = sf::Vector2f(this->GetSize().first, this->GetSize().second);
	image = sf::RectangleShape(sz);
	image.setFillColor(sf::Color::Red);
	image.setPosition(pos);
}
void Plat::ChangePos(pair<int, int> pos) {
	position = pos;
	sf::Vector2f newpos = sf::Vector2f(pos.first, pos.second);
	image.setPosition(newpos);
}
void Plat::ChangeSpeed(pair<int, int> sd) {
	this->speedXY = sd;
}
void Plat::ChangeImage(sf::RectangleShape img) {
	this->image = img;
}
void Plat::ChangeSize(pair<int, int> sz) {
	this->size = sz;
	sf::Vector2f newsize = sf::Vector2f(sz.first, sz.second);
	image.setSize(newsize); //ne uveren tuta
}
void Plat::ChangeSaveCount(int cnt) {
	this->SaveCount = cnt;
}
void Plat::Start(pair<int, int> fieldData) {
	fieldData.first = fieldData.first / 2 - this->size.first / 2;
	fieldData.second = fieldData.second * 0.9;
	this->ChangePos(fieldData);
	pair<int, int> Speed;
	Speed.first = 5; Speed.second = 5;
	this->ChangeSpeed(Speed);
}
void Plat::Movement() {
	sf::Vector2f sd = sf::Vector2f(this->speedXY.first, this->speedXY.second);
	image.move(sd);
	position.first = position.first + (this->speedXY.first);
	position.second = position.second + (this->speedXY.second);
}