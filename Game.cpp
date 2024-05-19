#include "Game.h"
#include <iostream>

using namespace std;
Field const& Game::getField() {
	return *field;
}
Game::Game(int const& width, int const& height) : randgen(device()) {
	if ((width < 2 || height < 2) || (width == 2) && (height == 2)) {
		throw std::runtime_error("Игровое поле слишком мало");
	}
	uniform_int_distribution<mt19937::result_type> dist(0, int(BlockColor::NONE) - 1);

	function<BlockColor(pair<int, int>)> generation = [&dist, this](pair<int, int> point) { return BlockColor(dist(this->randgen)); };
	field = make_unique<Field>(width, height, generation);
}

void Game::FindChain(vector<pair<int, int>>& chain, int const& startX, int const& startY) {
	BlockColor DeletingColor = field->curBlock(startX, startY).getcolor();
	if (DeletingColor != BlockColor::NONE) { //find chain only if colored
		int width = field->getWidth() - 1;
		int height = field->getHeight() - 1;
		pair<int, int> start;
		start.first = startX;
		start.second = startY;
		chain.push_back(start);
		int prevsize = 0;
		pair<int, int> point;
		while (prevsize != chain.size()) {
			int checked = prevsize; //this points already checked all neighbour
			int prevsize = chain.size();
			for (int i = checked; i < prevsize; i++) {
				point.first = chain[i].first - 1;
				point.second = chain[i].second;
				if (((point.first <= width) && (point.first >= 0))) {
					bool flag = true;
					for (int j = 0; j < chain.size(); j++) {
						if ((chain[j].first == point.first) && (chain[j].second == chain[i].second)) flag = false;
					}
					if (flag && DeletingColor == field->curBlock(point.first, chain[i].second).getcolor()) chain.push_back(point);
				}
				point.first = chain[i].first + 1;
				if (((point.first <= width) && (point.first >= 0))) {
					bool flag = true;
					for (int j = 0; j < chain.size(); j++) {
						if ((chain[j].first == point.first) && (chain[j].second == chain[i].second)) flag = false;
					}
					if (flag && DeletingColor == field->curBlock(point.first, chain[i].second).getcolor()) chain.push_back(point);
				}
				point.first = chain[i].first;
				point.second = chain[i].second - 1;
				if (((point.second <= height) && (point.second >= 0))) {
					bool flag = true;
					for (int j = 0; j < chain.size(); j++) {
						if ((chain[j].first == point.first) && (chain[j].second == chain[i].second)) flag = false;
					}
					if (flag && DeletingColor == field->curBlock(point.first, chain[i].second).getcolor()) chain.push_back(point);
				}
				point.second = chain[i].second + 1;
			}
		}
	}
}

void Game::RemoveChain(vector<pair<int, int>>& removed, int const& startX, int const& startY) {
	vector<pair<int, int>> chain;
	FindChain(chain, startX, startY);
	if (chain.size() < 3 || field->curBlock(startX, startY).getcolor() == BlockColor::NONE) return;
	for (int i = 0; i < chain.size(); i++) {
		field->curBlock(chain[i].first, chain[i].second) = Block(BlockColor::NONE);
		removed.push_back(chain[i]);
	}
}
bool Game::movedownBlocks() {
	bool flag = false; // if True, we should try to find new chains, if false - were can't be any new chains
	for (int i = field->getHeight() - 1; i >= 1; i--) {
		for (int j = 0; j < field->getWidth(); j++) {
			if ((field->curBlock(j, i).getcolor() != BlockColor::NONE) && (field->curBlock(j, i - 1).getcolor() == BlockColor::NONE)) {
				field->curBlock(j, i-1) = Block(field->curBlock(j, i).getcolor());
				field->curBlock(j, i) = Block(BlockColor::NONE);
				flag = true;
			}
		}
	}
	return flag;
}