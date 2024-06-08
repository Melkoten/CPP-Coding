#include "Game.h"
#include <iostream>
#include "SFML/Graphics.hpp"

int main() {
	Game game({1200, 900}, {1600, 900});
	game.StartGame();
	return 0;
}