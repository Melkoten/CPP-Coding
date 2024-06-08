#include "Ball.h"
using namespace std;

Ball::Ball(pair<int, int> speedXY, pair<int, int> position) {
	this->position = position;
	this->speedXY = speedXY;
	image = sf::CircleShape(this->radius);
	image.setFillColor(sf::Color::Red);
	sf::Vector2f pos = sf::Vector2f(position.first, position.second);
	image.setPosition(pos);
}
void Ball::ChangePos(pair<int, int> newpos) {
	this->position = newpos;
	sf::Vector2f pos = sf::Vector2f(newpos.first, newpos.second);
	image.setPosition(pos);
}
void Ball::ChangeSpeed(pair<int, int> speed) {
	this->speedXY = speed;
}
void Ball::ChangeImage(sf::CircleShape img) {
	this->image = img;
}
void Ball::ChangeMoving(bool flag) {
	this->Moving = flag;
}
void Ball::Start(pair<int, int> fieldData) {
	this->Moving = false;
	fieldData.first = fieldData.first / 2;
	fieldData.second = fieldData.second * 0.9 - 20;
	this->ChangePos(fieldData);
	pair<int, int> Speed;
	Speed.first = 5; Speed.second = 5;
	this->ChangeSpeed(Speed);
}
void Ball::Movement() {
	sf::Vector2f sd = sf::Vector2f(this->speedXY.first, this->speedXY.second);
	image.move(sd);
	position.first = position.first + (this->speedXY.first);
	position.second = position.second + (this->speedXY.second);
}