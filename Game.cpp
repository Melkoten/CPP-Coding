#include "Game.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include <sstream>
using namespace std;

void MeetWalls(Ball& ball, Plat& plat, pair<int, int> fieldData, int* score) {
	int midX = ball.GetPos().first + ball.GetRad();
	int midY = ball.GetPos().second + ball.GetRad();
	
	if ((midX > fieldData.first) || (midX < 0)) ball.ChangeSpeed({ ball.GetSpeed().first*(-1),ball.GetSpeed().second});
	if (midY < 0) ball.ChangeSpeed({ ball.GetSpeed().first, (ball.GetSpeed().second * (-1)) });
	if (midY > fieldData.second) {
		if (plat.GetSave() == 0) {
			*score = *score - 1;
			ball.ChangeSpeed({ ball.GetSpeed().first, (ball.GetSpeed().second * (-1)) });
		}
		if (plat.GetSave() > 0) {
			ball.ChangeSpeed({ ball.GetSpeed().first, (ball.GetSpeed().second * (-1)) });
			plat.ChangeSaveCount(plat.GetSave() - 1);
		}
	}
}
void MeetPlat(Ball& ball, Plat& plat) {
	sf::FloatRect intersection;
	if (ball.GetImage().getGlobalBounds().intersects(plat.GetImage().getGlobalBounds())) {
		ball.GetImage().getGlobalBounds().intersects(plat.GetImage().getGlobalBounds(), intersection);
		int k = 1;
		if (ball.GetSpeed().second < 0) {
			k = -1;
		}
		ball.ChangePos({ball.GetPos().first, (int)(ball.GetPos().second-intersection.height * k)});
		ball.ChangeSpeed({ball.GetSpeed().first, ball.GetSpeed().second * (-1)});
	}
}
void MeetBlocks(Ball& ball, shared_ptr<vector<Block>> blocks, BonusFunctions& bfunc, int* score) {
	for (int i = 0; i < blocks->size(); i++) {
		if (ball.GetImage().getGlobalBounds().intersects(blocks->at(i).GetImage().getGlobalBounds())) {
			sf::FloatRect intersection;
			ball.GetImage().getGlobalBounds().intersects(blocks->at(i).GetImage().getGlobalBounds(), intersection);
			if ((intersection.width) > intersection.height) {
				ball.ChangePos({ball.GetPos().first - ball.GetSpeed().first , ball.GetPos().second - ball.GetSpeed().second });// here
				ball.ChangeSpeed({ ball.GetSpeed().first, ball.GetSpeed().second * (-1) }); // left or right
				//ball.ChangePos({ ball.GetPos().first, ball.GetPos().second});
			}
			else if ((intersection.width) < intersection.height) {
				ball.ChangePos({ ball.GetPos().first - ball.GetSpeed().first , ball.GetPos().second - ball.GetSpeed().second }); //here
				ball.ChangeSpeed({ ball.GetSpeed().first * (-1), ball.GetSpeed().second});//up or down
				//ball.ChangePos({ ball.GetPos().first, ball.GetPos().second });
			}
			else {
				ball.ChangePos({ ball.GetPos().first - ball.GetSpeed().first , ball.GetPos().second - ball.GetSpeed().second }); //here
				ball.ChangeSpeed({ ball.GetSpeed().first*(-1), ball.GetSpeed().second * (-1)}); //ugol
			}
			if (blocks->at(i).CanDestroy()) {
				blocks->at(i).DecreaseHP();
				*score = *score + 1;
				bfunc.IncreaseSpeedByBlock(ball);
				bfunc.SpawnBonuses(blocks->at(i));
			}
		}
	}
}
void MeetBonus(Ball& ball, Plat& plat, BonusFunctions& bfunc) {
	vector<shared_ptr<Bonus>> allBonuses = bfunc.GetBonuses();
	for (int i = 0; i < size(allBonuses); i++) {
		if (plat.GetImage().getGlobalBounds().intersects(allBonuses[i]->GetImage().getGlobalBounds())) {
			allBonuses[i]->Action(ball, plat);
			bfunc.DeleteBonus(i);
			printf("bonus activated ");
			//i = i - 1; //mistake with memory may be here;
		}
	}
}
void DrawAll(sf::RenderWindow& window, Ball& ball, Plat& plat, BonusFunctions& bfunc, shared_ptr<vector<Block>> block, int score, int save) {
	window.clear();
	window.draw(ball.GetImage());
	window.draw(plat.GetImage());
	for (int i = 0; i < 50; i++) {
		window.draw(block->at(i).GetImage());
	}
	for (int i = 0; i < bfunc.GetBonuses().size(); i++) {
		vector<shared_ptr<Bonus>> allBonuses = bfunc.GetBonuses();
		window.draw(allBonuses[i]->GetImage());
	}
	PrintData(window, score, save);
	window.display();

}
void PrintData(sf::RenderWindow& window, int points, int saves) {
	ostringstream ss, ss2;
	ss << points;
	ss2 << saves;
	sf::Text text;
	sf::Text points_text;
	sf::Text text2;
	sf::Text points_text2;
	sf::Font font;
	if (font.loadFromFile("cheri.ttf")) {
		text.setFont(font);
		points_text.setFont(font);

		text.setString("SCORE");
		points_text.setString(ss.str().c_str());

		text.setCharacterSize(60);
		points_text.setCharacterSize(50);

		text.setPosition(1300, 100);
		points_text.setPosition(1350, 200);

		text.setFillColor(sf::Color::White);
		points_text.setFillColor(sf::Color::White);

		text.setStyle(sf::Text::Bold);
		points_text.setStyle(sf::Text::Bold);

		text.setFont(font);
		points_text.setFont(font);

		text2.setString("FREE LOSE");
		points_text2.setString(ss2.str().c_str());

		text2.setCharacterSize(60);
		points_text2.setCharacterSize(50);

		text2.setPosition(1300, 400);
		points_text2.setPosition(1350, 500);

		text2.setFillColor(sf::Color::White);
		points_text2.setFillColor(sf::Color::White);

		text2.setStyle(sf::Text::Bold);
		points_text2.setStyle(sf::Text::Bold);

		text2.setFont(font);
		points_text2.setFont(font);

		(window).draw(text);
		(window).draw(points_text);
		(window).draw(text2);
		(window).draw(points_text2);
	}
}
Game::Game(pair<int, int> fieldData, pair<int, int> fullWindow) {
	this->fieldData = fieldData;
	this->fullWindow = fullWindow;
}
Ball& Game::SpawnBall() {
	pair<int, int> pos = { this->fieldData.first / 2 - 10,(int)(this->fieldData.second * 0.9 - 20) };
	pair<int, int> speed = { 5,5 };
	Ball* ball = new Ball(speed, pos);
	return *ball;
}
Plat& Game::SpawnPlat() {
	pair<int, int> pos = { this->fieldData.first / 2 - 75, (int)(this->fieldData.second * 0.9)};
	Plat* plat = new Plat(pos);
	return *plat;
}
shared_ptr<vector<Block>> Game::SpawnBlocks() {
	shared_ptr<vector<Block>> blocks = make_shared<vector<Block>>();
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++) {
			int seed = time(NULL);
			srand(seed);
			int flag = (rand()+i*j) % 5;
			int startX = (this->fieldData.first -(60 * 10 + 15 * 9)) / 2;
			int startY = (this->fieldData.second - (60 * 6 + 15 * 5)) / 2;
			pair<int, int> pos = {60*i+15*i+startX, 60*j+15*j+startY};
			Block block(pos, { 60,60 });
			switch (flag) {
			case 1: {
				block.ChangeColor(BlockColor::NONDESTRUCT);
				break;
			}
			}
			blocks->push_back(block);
		}
	}
	return blocks;
}
BonusFunctions& Game::SpawnBfunc() {
	BonusFunctions* bfunc = new BonusFunctions();
	return *bfunc;
}

sf::RenderWindow& Game::SpawnWindow() {
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(fullWindow.first, fullWindow.second), "Game");
	window->setFramerateLimit(75);
	window->setKeyRepeatEnabled(false);
	return *window;
}
void Game::Movement(Ball& ball, Plat& plat, shared_ptr<vector<Block>> blocks, BonusFunctions& bfunc) {
	ball.Movement();
	MeetWalls(ball, plat, fieldData, &score);
	MeetPlat(ball, plat);
	MeetBlocks(ball, blocks, bfunc, &score);
	MeetBonus(ball, plat, bfunc);
}
bool Game::ZeroBlocks(shared_ptr<vector<Block>> blocks) {
	bool flag = true;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++) {
			if ((blocks->at(i*5+j).GetColor() != BlockColor::NONDESTRUCT) && (blocks->at(i * 5 + j).GetHealth()>0)) {
				flag = false;
			}
		}
	}
	return flag;
}
void Game::StartGame() {
	sf::RenderWindow& window = SpawnWindow();
	shared_ptr<vector<Block>> blocks = SpawnBlocks();
	BonusFunctions& bfunc = SpawnBfunc();
	Plat& plat = SpawnPlat();
	Ball& ball = SpawnBall();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if ((event.type) == sf::Event::Closed) {
				window.close();
			}
		} 
		if ((event.type) == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Left) {
					if (plat.GetPos().first > 0) {
						plat.ChangeSpeed({-10,0});
						plat.Movement();
						if (!ball.GetMoving()) {
							ball.ChangePos({ (ball.GetPos().first - 10), ball.GetPos().second});
						}
					}
				}
				if (event.key.code == sf::Keyboard::Right) {
					if (plat.GetPos().first < fieldData.first-plat.GetSize().first) {
						plat.ChangeSpeed({10,0 });
						plat.Movement();
						if (!ball.GetMoving()) {
							ball.ChangePos({ (ball.GetPos().first + 10), ball.GetPos().second });
						}
					}
				}
			}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				ball.ChangeMoving(true);
			}
		if (ball.GetMoving() == true) {
				Movement(ball, plat, blocks, bfunc);
			}
		bfunc.MovingBonusBlocks();
		if (ZeroBlocks(blocks)) {
				window.close();
				break;
		}
		DrawAll(window, ball, plat, bfunc, blocks, this->score, plat.GetSave());
		}
}