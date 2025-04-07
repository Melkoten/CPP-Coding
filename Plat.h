#pragma once
#include "SFML/Graphics.hpp"
using namespace std;

class Plat {
private:
	pair<int, int> speedXY = {10,0};
	pair<int, int> position;
	pair<int, int> size = {150, 10};
	sf::RectangleShape image;
	int SaveCount = 0;
public:
	Plat(pair<int, int> position);
	void ChangePos(pair<int, int> pos);
	void ChangeSpeed(pair<int, int> sd);
	void ChangeSize(pair<int, int> sz);
	void ChangeImage(sf::RectangleShape img);
	void ChangeSaveCount(int cnt);

	pair<int, int> const GetPos() { return (this->position); }
	pair<int, int> const GetSpeed() { return (this->speedXY); }
	pair<int, int> const GetSize() { return (this->size); }
	int const GetSave() { return (this->SaveCount); }
	sf::RectangleShape GetImage() { return(this->image); };
	void Start(pair<int, int> start);
	void Movement();
};