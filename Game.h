#pragma once
#include <memory>
#include <random>
#include "SFML/Graphics.hpp"
#include "Field.h"
#include <sstream>
using namespace std;
enum class StageOfGame {
	FIRSTCLICK = 0,
	SECONDCLICK,
};

class Game {
	pair<int, int> currentpoint = { -1,-1 };
	StageOfGame stage = StageOfGame::FIRSTCLICK;
	std::unique_ptr<Field> field;
	std::random_device device;
	std::mt19937 randgen;
	float bonusChance = 0.1;
	int const Radius = 3;
	int data=0;
	bool movedownBlocks();
	void BonusProc(vector<pair<vector<pair<int, int>>, BlockColor>> const& points);
	void BonusRecolor(int const& x, int const& y, BlockColor Color);
	void BonusBomb(int const& x, int const& y);
	void FindChain(vector<pair<int, int>>& chain, int const& startX, int const& startY);
	void RemoveChain(vector<pair<int, int>>& removed, int const& startX, int const& startY);

public:
	Field const& getField();
	explicit Game(int width, int height); //const
	void Click(int x, int y);
	void printgame(RenderWindow* window);
	void printData(RenderWindow* window, int points);
};