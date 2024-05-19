#pragma once
#include <memory>
#include <random>
#include "Field.h"
using namespace std;
enum class StageOfGame {
	FIRSTBLOCK = 0,
	SECONDCLICK,
	PROCESS
};

class Game {
	struct BonusPointsFrom {
		BlockColor color;
		vector<pair<int, int>> points;
	};
	StageOfGame stage = StageOfGame::FIRSTBLOCK;
	std::unique_ptr<Field> field;
	std::random_device device;
	std::mt19937 randgen;
	float bonusChance = 0.1;
	int const Radius = 3;
	bool movedownBlocks();
	void BonusProc(vector<BonusPointsFrom> const& points);
	void BonusRecolor(int const& x, int const& y, BlockColor Color);
	void BonusBomb(int const& x, int const& y);
	void FindChain(std::vector<pair<int, int>>& chain, int const& startX, int const& startY);
	void RemoveChain(std::vector<pair<int, int>>& removed, int const& startX, int const& startY);

public:
	Field const& getField();
	Game(int const& width, int const& height);
	void Click(int x, int y);
};