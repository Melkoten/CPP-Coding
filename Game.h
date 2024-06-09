#pragma once
#include "SFML/Graphics.hpp"
#include "Blocks.h"
#include "Ball.h"
#include "Bonus.h"
#include "Plat.h"

using namespace std;

void MeetWalls(Ball& ball, Plat& plat, pair<int, int> fieldData, int* score);
void MeetPlat(Ball& ball, Plat& plat);
void MeetBlocks(Ball& ball, shared_ptr<vector<Block>>  block, BonusFunctions& bfunc, int* score);
void MeetBonus(shared_ptr<vector<Ball>> balls, Plat& plat, BonusFunctions& bfunc);
void MeetBall(Ball& ball1, Ball& ball2);
void DrawAll(sf::RenderWindow& window, shared_ptr<vector<Ball>> balls, Plat& plat, BonusFunctions& bfunc, shared_ptr<vector<Block>> block, int score, int save);
void PrintData(sf::RenderWindow& window, int points, int save);
class Game {
private: 
	pair<int, int> fieldData;
	pair<int, int> fullWindow;
	int score=0;
	shared_ptr<vector<Ball>> SpawnBall();
	Plat& SpawnPlat();
	shared_ptr<vector<Block>> SpawnBlocks();
	BonusFunctions& SpawnBfunc();
	sf::RenderWindow& SpawnWindow();
	void Movement(shared_ptr<vector<Ball>> ball, Plat& plat, shared_ptr<vector<Block>> blocks, BonusFunctions& bfunc);

public:
	Game(pair<int, int> fieldData, pair<int, int> fullWindow);
	void StartGame();
	bool ZeroBlocks(shared_ptr<vector<Block>> blocks);
};