#include "Game.h"
#include <iostream>
#include "SFML/Graphics.hpp"

int main() {
	RenderWindow window(VideoMode(1920, 1080), "GameWindow");
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);
	int x = 20; //40px on one block
	int y = 20; //40px on one block
	Game game(x, y);
	Time elapsedTime;
	Clock clock;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					game.Click(event.mouseButton.x, event.mouseButton.y);
					break;
				}
			}
		}
		game.printgame(&window);
	}
	return 0;
}