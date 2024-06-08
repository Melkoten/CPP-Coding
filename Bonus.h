#pragma once
#include "SFML/Graphics.hpp"
#include "Ball.h"
#include "Blocks.h"
#include "Plat.h"

using namespace std;
class Bonus {
protected:
		sf::RectangleShape image;
		pair<int, int> position;
		pair<int, int> size;
		pair<int, int> speedXY = {0,5};
public:
	Bonus(pair<int, int> position);
	virtual ~Bonus() = default;
	virtual void Action(Ball& ball, Plat& plat) = 0;
	void Movement();
	void ChangePos(pair<int, int> pos);
	void ChangeSize(pair<int, int> sz);
	void ChangeSpeed(pair<int, int> sd);
	void ChangeImage(sf::RectangleShape image);
	pair<int, int> const GetPos() { return (this->position); }
	pair<int, int> const GetSize() { return (this->size); }
	pair<int, int> const GetSpeed() { return (this->speedXY); }
	sf::RectangleShape GetImage() { return(this->image); };	
};

class IncreaseSpeed : public Bonus {
private:
	int incr = 1;
public:
	IncreaseSpeed(pair<int, int> position);
	void Action(Ball& ball, Plat& plat)  override;
};

class IncreasePlat : public Bonus {
private:
	int incr = 20;
public:
	IncreasePlat(pair<int, int> position);
	void Action(Ball& ball, Plat& plat)  override;
};

class ChangeDirection : public Bonus {
public:
	ChangeDirection(pair<int, int> position);
	void Action(Ball& ball, Plat& plat)  override;
};

class SaveOneLose : public Bonus {
public:
	SaveOneLose(pair<int, int> position);
	void Action(Ball& ball, Plat& plat)  override;
};

class BonusFunctions {
private:
	vector<shared_ptr<Bonus>> allBonuses;
public:
	BonusFunctions() {};
	void NewBonus(shared_ptr<Bonus> newbonus);
	void DeleteBonus(int num);
	void MovingBonusBlocks();
	vector<shared_ptr<Bonus>> const GetBonuses() { return allBonuses; };
	void SpawnBonuses(Block block); //add new bonus (one of five types)
	void IncreaseSpeedByBlock(Ball& ball);
};