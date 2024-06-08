#include "SFML/Graphics.hpp"
#include "Bonus.h"
#include <ctime>
#include <iostream>
#include <math.h>

using namespace std;

Bonus::Bonus(pair<int, int> position) {
	this->position = position;
}
void Bonus::Movement() {
	sf::Vector2f sd = sf::Vector2f(this->speedXY.first, this->speedXY.second);
	image.move(sd);
	position.first = position.first + (this->speedXY.first);
	position.second = position.second + (this->speedXY.second);
}
void  Bonus::ChangePos(pair<int, int> pos) {
	position = pos;
	sf::Vector2f newpos = sf::Vector2f(pos.first, pos.second);
	image.setPosition(newpos);
}
void  Bonus::ChangeSize(pair<int, int> sz) {
	this->size = sz;
	sf::Vector2f newsize = sf::Vector2f(sz.first, sz.second);
	image.setSize(newsize);
}
void  Bonus::ChangeSpeed(pair<int, int> sd) {
	this->speedXY = sd;
}
void  Bonus::ChangeImage(sf::RectangleShape img) {
	this->image = img;
}
IncreaseSpeed::IncreaseSpeed(pair<int, int> position): Bonus(position) {
	this->size = {30,30};
	sf::Vector2f pos = sf::Vector2f(position.first, position.second);
	sf::Vector2f sz = sf::Vector2f(size.first, size.second);
	image = sf::RectangleShape(sz);
	image.setPosition(pos);
	image.setFillColor(sf::Color::Blue);
}
IncreasePlat::IncreasePlat(pair<int, int> position) : Bonus(position) {
	this->size = { 30,30 };
	sf::Vector2f pos = sf::Vector2f(position.first, position.second);
	sf::Vector2f sz = sf::Vector2f(size.first, size.second);
	image = sf::RectangleShape(sz);
	image.setPosition(pos);
	image.setFillColor(sf::Color::Blue);
}
SaveOneLose::SaveOneLose(pair<int, int> position) : Bonus(position) {
	this->size = { 30,30 };
	sf::Vector2f pos = sf::Vector2f(position.first, position.second);
	sf::Vector2f sz = sf::Vector2f(size.first, size.second);
	image = sf::RectangleShape(sz);
	image.setPosition(pos);
	image.setFillColor(sf::Color::Blue);
}
ChangeDirection::ChangeDirection(pair<int, int> position) : Bonus(position) {
	this->size = { 30,30 };
	sf::Vector2f pos = sf::Vector2f(position.first, position.second);
	sf::Vector2f sz = sf::Vector2f(size.first, size.second);
	image = sf::RectangleShape(sz);
	image.setPosition(pos);
	image.setFillColor(sf::Color::Blue);
}
void IncreaseSpeed::Action(Ball& ball, Plat& plat) {
	printf("speed ");
	int incrX = this->incr;
	int incrY = this->incr;
	if (ball.GetSpeed().first < 0) {
		incrX = incrX * (-1);
	}
	if (ball.GetSpeed().second < 0) { 
		incrY = incrY* (-1); 
	}

	ball.ChangeSpeed({ball.GetSpeed().first+incrX, ball.GetSpeed().second+incrY});
}
void IncreasePlat::Action(Ball& ball, Plat& plat) {
	printf("plat ");
	plat.ChangeSize({ plat.GetSize().first + this->incr,plat.GetSize().second });
}
void SaveOneLose::Action(Ball& ball, Plat& plat) {
	printf("+ save ");
	plat.ChangeSaveCount(plat.GetSave() + 1);
}
void ChangeDirection::Action(Ball& ball, Plat& plat) {
	printf("direction ");
	int seed = time(NULL);
	srand(seed);
	int angle = rand() % 360;
	int speedX = ball.GetSpeed().first * cos(angle/180* 3.1415926535) - ball.GetSpeed().second * sin(angle/180* 3.1415926535);
	int speedY = ball.GetSpeed().first * sin(angle / 180 * 3.1415926535) + ball.GetSpeed().second * cos(angle / 180 * 3.1415926535);
	ball.ChangeSpeed({ speedX,speedY });
}
void BonusFunctions::NewBonus(shared_ptr<Bonus> newbonus) {
	allBonuses.push_back(newbonus);
}
void BonusFunctions::DeleteBonus(int num) {
	allBonuses.erase(allBonuses.begin()+num);
}
void BonusFunctions::MovingBonusBlocks() {
	for (int i = 0; i < allBonuses.size(); i++) {
		allBonuses[i]->Movement();
	}
}
void BonusFunctions::IncreaseSpeedByBlock(Ball& ball) {
	int seed = time(NULL);
	srand(seed);
	int flag = rand() % 10;
	if (flag == 9) {
		int speedX = ball.GetSpeed().first;
		int speedY = ball.GetSpeed().second;
		if (speedX < 0) {
			ball.ChangeSpeed({ speedX - 1,speedY });
		}
		else ball.ChangeSpeed({ speedX + 1,speedY });
		if (speedY < 0) {
			ball.ChangeSpeed({ speedX,speedY -1});
		}
		else ball.ChangeSpeed({ speedX,speedY+1});
	}
	int rad = ball.GetRad();
	if (ball.GetSpeed().first < (rad * (-1)))  ball.ChangeSpeed({ (rad * (-1)), ball.GetSpeed().second });
	if (ball.GetSpeed().second < (rad * (-1)))  ball.ChangeSpeed({ ball.GetSpeed().first,( rad*(-1))});
	if (ball.GetSpeed().first > rad)  ball.ChangeSpeed({ rad, ball.GetSpeed().second });
	if (ball.GetSpeed().second > rad)  ball.ChangeSpeed({ ball.GetSpeed().first, rad});
}
void BonusFunctions::SpawnBonuses(Block block) {
	int seed = time(NULL);
	srand(seed);
	int flag = rand() % 15;
	if (block.CanDestroy()) {
		switch (flag) {
		case 1: {
			shared_ptr<Bonus> newbonus = make_shared<IncreasePlat>(block.GetPos());
			this->NewBonus(newbonus);
			break;
		}
		case 2: {
			shared_ptr<Bonus> newbonus = make_shared<IncreaseSpeed>(block.GetPos());
			this->NewBonus(newbonus);
			break;
		}
		case 3: {
			shared_ptr<Bonus> newbonus = make_shared<ChangeDirection>(block.GetPos());
			this->NewBonus(newbonus);
			break;
		}
		case 4: {
			shared_ptr<Bonus> newbonus = make_shared<SaveOneLose>(block.GetPos());
			this->NewBonus(newbonus);
			break;
		}
		}
	}
}