#pragma once
#include "SFML/Graphics.hpp"
using namespace std;

class Ball {
private:
	pair<int, int> speedXY;
	pair<int, int> position;
	int radius = 10;
	sf::CircleShape image;
	bool Moving=false;
public:
	Ball(pair<int, int> speedXY, pair<int, int> position);
	void ChangePos(pair<int, int> pos);
	void ChangeSpeed(pair<int, int> sd);
	void ChangeImage(sf::CircleShape img);
	void ChangeMoving(bool flag);
	pair<int, int> const GetPos() { return (this->position); }
	pair<int, int> const GetSpeed() { return (this->speedXY); }
	int const GetRad() { return (this->radius); }
	sf::CircleShape GetImage() { return(this->image); }
	bool const GetMoving() { return (this->Moving); }
	void Start(pair<int, int> start);
	void Movement();
};