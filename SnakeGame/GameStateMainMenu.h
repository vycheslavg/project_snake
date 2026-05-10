#pragma once
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include <string>

namespace SnakeGame
{
	struct Game;

	struct GameStateMainMenuData
	{
		sf::Font font;

		// ¬вод имени игрока перед стартом
		std::string enteredName = "";
		sf::Text nameInputText;
		sf::Text nameHintText;
		bool isEnteringName = true;

		// √лавное меню
		MenuItem startGameItem;

		MenuItem difficultyItem;
		MenuItem easyItem;
		MenuItem normalItem;
		MenuItem hardItem;

		MenuItem optionsItem;
		MenuItem optionsInfiniteApplesItem;
		MenuItem optionsWithAccelerationItem;

		MenuItem recordsItem;
		MenuItem exitGameItem;

		MenuItem yesItem;
		MenuItem noItem;

		Menu menu;
	};

	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void ShutdownGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void HandleGameStateMainMenuWindowEvent(
		GameStateMainMenuData& data,
		Game& game,
		const sf::Event& event
	);
	void UpdateGameStateMainMenu(
		GameStateMainMenuData& data,
		Game& game,
		float timeDelta
	);
	void DrawGameStateMainMenu(
		GameStateMainMenuData& data,
		Game& game,
		sf::RenderWindow& window
	);
}