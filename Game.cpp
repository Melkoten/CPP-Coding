#include "Game.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include <sstream>

using namespace std;
using namespace sf;
Field const& Game::getField() {
	return *field;
}
Game::Game(int  width, int  height) : randgen(device()) {
	if ((width < 2 || height < 2) || (width == 2) && (height == 2)) {
		throw std::runtime_error("Игровое поле слишком мало");
	}
	uniform_int_distribution<mt19937::result_type> dist(0, int(BlockColor::NONE) - 1);

	function<BlockColor(pair<int, int>)> generation = [&dist, this](pair<int, int> point) { return BlockColor(dist(this->randgen)); };
	field = make_unique<Field>(width, height, generation);//
}
void Game::BonusProc(vector<pair<vector<pair<int, int>>, BlockColor>> const& points) {
	std::uniform_real_distribution<float> distProcChance(0.0f, 2.0f);
	std::uniform_int_distribution<std::mt19937::result_type> distProcType(0, 1);
	for (int k = 0; k < points.size(); k++) {
		for (int l = 0; l < points[k].first.size(); l++) {
			if (distProcChance(randgen) < bonusChance) {
				if (distProcType(randgen) == 0) {
					BonusRecolor(points[k].first[l].first, points[k].first[l].second, points[k].second);
				}
				if (distProcType(randgen) == 0) {
					BonusBomb(points[k].first[l].first, points[k].first[l].second);
				}
			}
		}

	}
}
void Game::BonusBomb(int const& x, int const& y) {
	std::uniform_int_distribution<std::mt19937::result_type> distX(0, field->getWidth() - 1); //4 random on field
	std::uniform_int_distribution<std::mt19937::result_type> distY(0, field->getHeight() - 1);
	for (int i = 0; i < 4; i++) {
		int xbomb = distX(randgen);
		int ybomb = distY(randgen);
		if (field->curBlock(xbomb, ybomb).getcolor() != BlockColor::NONE) data = data + 1;
		field->curBlock(xbomb,ybomb) = Block(BlockColor::NONE);
		printf("BOOOOM");
	}
	std::uniform_int_distribution<std::mt19937::result_type> distXl(max(0, (x - Radius)), min(x + Radius, field->getWidth()-1)); //1 in radius
	std::uniform_int_distribution<std::mt19937::result_type> distYl(max(0, (y - Radius)), min(y + Radius, field->getHeight() - 1));
	int xbomb = distXl(randgen);
	int ybomb = distYl(randgen);
	if (field->curBlock(xbomb, ybomb).getcolor() != BlockColor::NONE) data = data + 1;
	field->curBlock(xbomb, ybomb) = Block(BlockColor::NONE);
	printf("BOOOOM");

}
void Game::BonusRecolor(int const& x, int const& y, BlockColor Color) {
	std::uniform_int_distribution<std::mt19937::result_type> distX(0, field->getWidth() - 1);
	std::uniform_int_distribution<std::mt19937::result_type> distY(0, field->getHeight() - 1);
	std::uniform_int_distribution<std::mt19937::result_type> distXl(max(0, (x - Radius)), min(x + Radius, field->getWidth()-1));
	std::uniform_int_distribution<std::mt19937::result_type> distYl(max(0, (y - Radius)), min(y + Radius, field->getHeight() - 1));
	int xrec = distXl(randgen);
	int yrec = distYl(randgen);
	field->curBlock(xrec, yrec) = Block(Color);
	printf("recolor");
	int count = 0;
	while (count < 2) {
		xrec = distX(randgen);
		yrec = distY(randgen);
		if ((abs(xrec - x) > 1) || (abs(yrec - y) > 1)) { //isn't a neighbour
			field->curBlock(xrec, yrec) = Block(Color);
			printf("recolorNN");
			count = count + 1;
		}
	}
}
void Game::FindChain(vector<pair<int, int>>& chain, int const& startX, int const& startY) {
	BlockColor DeletingColor = field->curBlock(startX, startY).getcolor();
	if (DeletingColor != BlockColor::NONE) { //find chain only if colored
		int width = field->getWidth() - 1;
		int height = field->getHeight() - 1;
		pair<int, int> start;
		start = { startX, startY };
		chain.push_back(start);
		//printf_s("chain started");
		int prevsize = 0;
		pair<int, int> point;
		while (prevsize != chain.size()) {
			//printf_s(" START prevsize = %d, chainsize= %d", prevsize, chain.size());
			int checked = prevsize; //this points already checked all neighbour
			prevsize = chain.size();//
			//printf_s(" CHANGED prevsize = %d, chainsize= %d", prevsize, chain.size());
			for (int i = checked; i < prevsize; i++) {
				point.first = chain[i].first - 1;
				point.second = chain[i].second;
				if (((point.first <= width) && (point.first >= 0))) {
					bool flag = true;
					for (int j = 0; j < chain.size(); j++) {
						if ((chain[j].first == point.first) && (chain[j].second == point.second)) flag = false;
					}
					if (flag && DeletingColor == field->curBlock(point.first, point.second).getcolor()) {
						chain.push_back(point);
						//printf("left");
					}
				}
				point.first = chain[i].first + 1;
				point.second = chain[i].second;
				if (((point.first <= width) && (point.first >= 0))) {
					bool flag = true;
					for (int j = 0; j < chain.size(); j++) {
						if ((chain[j].first == point.first) && (chain[j].second == point.second)) flag = false;
					}
					if (flag && DeletingColor == field->curBlock(point.first, point.second).getcolor()) {
						chain.push_back(point);
						//printf("right");
					}
				}
				point.first = chain[i].first;
				point.second = chain[i].second - 1;
				if (((point.second <= height) && (point.second >= 0))) {
					bool flag = true;
					for (int j = 0; j < chain.size(); j++) {
						if ((chain[j].first == point.first) && (chain[j].second == point.second)) flag = false;
					}
					if (flag && DeletingColor == field->curBlock(point.first, point.second).getcolor()) {
						chain.push_back(point);
						//printf("down");
					}
				}
				point.first = chain[i].first;
				point.second = chain[i].second + 1;
				if (((point.second <= height) && (point.second >= 0))) {
					bool flag = true;
					for (int j = 0; j < chain.size(); j++) {
						if ((chain[j].first == point.first) && (chain[j].second == point.second)) flag = false;
					}
					if (flag && DeletingColor == field->curBlock(point.first, point.second).getcolor()) {
						chain.push_back(point);
						//printf("left");
					}
				}
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
		data = data + 1;
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
void Game::Click(int x, int y) {
	x = x / (800/(field->getWidth()));
	//y = y / (800 / (field->getHeight()));
	y = (field->getHeight() - 1) - y / (800 / (field->getHeight()));
	if (field->curBlock(x, y).getcolor() == BlockColor::NONE || y < 0 || y >= field->getHeight() || x < 0 || x >= field->getWidth()) return;
	switch (stage) {
	case StageOfGame::FIRSTCLICK:
		currentpoint = { x,y };
		stage = StageOfGame::SECONDCLICK;
		break;
	case StageOfGame::SECONDCLICK:
		if (currentpoint.first == x && currentpoint.second == y) {
			stage = StageOfGame::FIRSTCLICK;
		}
		else if ((abs(currentpoint.first - x) <= 1 && abs(currentpoint.second - y)==0) || (abs(currentpoint.first - x) ==0 && abs(currentpoint.second - y) <= 1)) {
			swap(field->curBlock(x,y), field->curBlock(currentpoint.first, currentpoint.second));
			stage = StageOfGame::FIRSTCLICK;
			bool flag = true;
			while (flag == true) {
				vector<pair<vector<pair<int, int>>, BlockColor>> forBonus;
				for (int i = field->getHeight() - 1; i >= 0; i--) {
					for (int j = 0; j < field->getWidth(); j++) {
						BlockColor DeletingColor = field->curBlock(j, i).getcolor();
						vector<pair<int, int>> removed;
						RemoveChain(removed, j, i);
						forBonus.push_back({ removed, DeletingColor });
					}
				}
				BonusProc(forBonus);
				flag = movedownBlocks();
			}

		}
		else {
			currentpoint = { x,y };
		}
		break;
	default:
		break;
	}
}
void Game::printData(RenderWindow* window, int points) {
	ostringstream ss;
	ss << points;
	Text text;
	Text points_text;
	Font font;
	if (font.loadFromFile("cheri.ttf")) {
		text.setFont(font);
		points_text.setFont(font);

		text.setString("SCORE");
		points_text.setString(ss.str().c_str());

		text.setCharacterSize(60); 
		points_text.setCharacterSize(50);

		text.setPosition(1000, 100);
		points_text.setPosition(1050, 200);

		text.setFillColor(Color::White);
		points_text.setFillColor(Color::White);

		text.setStyle(Text::Bold);
		points_text.setStyle(Text::Bold);

		(*window).draw(text);
		(*window).draw(points_text);
	}
}
void Game::printgame(RenderWindow* window) {
	window->clear(Color::Black);
	for (int i = 0; i < field->getHeight(); i++) {
		for (int j=0; j < field->getWidth(); j++){
			RectangleShape myQuads({ 40, 40 });
			//myQuads.setPosition(Vector2f(i * (800 / field->getWidth()), j * (800 /field->getHeight())));
			myQuads.setPosition(Vector2f(i * (800 / field->getWidth()), (19-j) * (800 / field->getHeight())));
			switch ((field->curBlock(i, j).getcolor())) {
			case BlockColor::BLUE:
				myQuads.setFillColor(Color{ 0, 0, 255, 255 });
				break;
			case BlockColor::RED:
				myQuads.setFillColor(Color::Red);
				break;
			case BlockColor::GREEN:
				myQuads.setFillColor(Color{ 0, 255, 0, 127 });
				break;
			case BlockColor::YELLOW:
				myQuads.setFillColor(Color::Yellow);
				break;
			case BlockColor::PURPLY:
				myQuads.setFillColor(Color::Magenta);
				break;

			case BlockColor::NONE:
				myQuads.setFillColor(Color::White);
				break;
			}////
			(*window).draw(myQuads);
		}
	}
	printData(window, data);
	window->display();
}
