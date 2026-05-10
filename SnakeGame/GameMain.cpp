#include <SFML/Graphics.hpp>
#include <cstdlib>

#include "Game.h"

using namespace SnakeGame;

int main()
{
	unsigned int seed = (unsigned int)time(nullptr); 
	srand(seed);

	sf::RenderWindow window(sf::VideoMode(SnakeGame::SCREEN_WIDTH, SnakeGame::SCREEN_HEGHT), "SnakeGame");

	SnakeGame::Game* game = new SnakeGame::Game();
	InitGame(*game);

	sf::Clock gameClock;
	
	while (window.isOpen()) {
		
		float startTime = gameClock.getElapsedTime().asSeconds();
		
		HandleWindowEvents(*game, window);

		if (!window.isOpen()) {
			break;
		}

		if (UpdateGame(*game, TIME_PER_FRAME))
		{

			window.clear();

			DrawGame(*game, window);

			window.display();
		}
		else
		{
			window.close();
		}

		float endTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = endTime - startTime;
		if (deltaTime < TIME_PER_FRAME) {
			sf::sleep(sf::seconds(TIME_PER_FRAME - deltaTime));
		}
	}

	ShutdownGame(*game);
	delete game;
	game = nullptr;

	return 0;
}
