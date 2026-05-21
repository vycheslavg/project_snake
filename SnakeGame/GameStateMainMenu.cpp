#include "GameStateMainMenu.h"
#include "Game.h"
#include <assert.h>

namespace SnakeGame
{
	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));


		data.nameHintText.setString("Enter your name:");
		data.nameHintText.setFont(data.font);
		data.nameHintText.setCharacterSize(40);
		data.nameHintText.setFillColor(sf::Color::White);

		data.nameInputText.setString("_");
		data.nameInputText.setFont(data.font);
		data.nameInputText.setCharacterSize(32);
		data.nameInputText.setFillColor(sf::Color::Yellow);

		data.menu.rootItem.hintText.setString("Snake Game");
		data.menu.rootItem.hintText.setFont(data.font);
		data.menu.rootItem.hintText.setCharacterSize(48);
		data.menu.rootItem.hintText.setFillColor(sf::Color::Red);

		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 10.f;

		data.menu.rootItem.children.push_back(&data.startGameItem);
		data.menu.rootItem.children.push_back(&data.difficultyItem);
		data.menu.rootItem.children.push_back(&data.optionsItem);
		data.menu.rootItem.children.push_back(&data.recordsItem);
		data.menu.rootItem.children.push_back(&data.exitGameItem);

		
		data.startGameItem.text.setString("Start Game");
		data.startGameItem.text.setFont(data.font);
		data.startGameItem.text.setCharacterSize(24);

		data.difficultyItem.text.setString("Select Difficulty");
		data.difficultyItem.text.setFont(data.font);
		data.difficultyItem.text.setCharacterSize(24);

		data.difficultyItem.hintText.setString("Difficulty");
		data.difficultyItem.hintText.setFont(data.font);
		data.difficultyItem.hintText.setCharacterSize(48);
		data.difficultyItem.hintText.setFillColor(sf::Color::Red);

		data.difficultyItem.childrenOrientation = Orientation::Vertical;
		data.difficultyItem.childrenAlignment = Alignment::Middle;
		data.difficultyItem.childrenSpacing = 10.f;

		data.difficultyItem.children.push_back(&data.easyItem);
		data.difficultyItem.children.push_back(&data.normalItem);
		data.difficultyItem.children.push_back(&data.hardItem);

		data.easyItem.text.setString("Easy");
		data.easyItem.text.setFont(data.font);
		data.easyItem.text.setCharacterSize(24);

		data.normalItem.text.setString("Normal");
		data.normalItem.text.setFont(data.font);
		data.normalItem.text.setCharacterSize(24);

		data.hardItem.text.setString("Hard");
		data.hardItem.text.setFont(data.font);
		data.hardItem.text.setCharacterSize(24);

		data.optionsItem.text.setString("Options");
		data.optionsItem.text.setFont(data.font);
		data.optionsItem.text.setCharacterSize(24);

		data.optionsItem.hintText.setString("Options");
		data.optionsItem.hintText.setFont(data.font);
		data.optionsItem.hintText.setCharacterSize(48);
		data.optionsItem.hintText.setFillColor(sf::Color::Red);

		data.optionsItem.childrenOrientation = Orientation::Vertical;
		data.optionsItem.childrenAlignment = Alignment::Middle;
		data.optionsItem.childrenSpacing = 10.f;

		data.optionsItem.children.push_back(&data.optionsInfiniteApplesItem);
		data.optionsItem.children.push_back(&data.optionsWithAccelerationItem);
		data.optionsItem.children.push_back(&data.optionsSoundItem);

		data.optionsInfiniteApplesItem.text.setFont(data.font);
		data.optionsInfiniteApplesItem.text.setCharacterSize(24);

		data.optionsWithAccelerationItem.text.setFont(data.font);
		data.optionsWithAccelerationItem.text.setCharacterSize(24);

				data.optionsSoundItem.text.setFont(data.font);
		data.optionsSoundItem.text.setCharacterSize(24);

		data.recordsItem.text.setString("Records");
		data.recordsItem.text.setFont(data.font);
		data.recordsItem.text.setCharacterSize(24);

		data.exitGameItem.text.setString("Exit Game");
		data.exitGameItem.text.setFont(data.font);
		data.exitGameItem.text.setCharacterSize(24);

		data.exitGameItem.hintText.setString("Are you sure?");
		data.exitGameItem.hintText.setFont(data.font);
		data.exitGameItem.hintText.setCharacterSize(48);
		data.exitGameItem.hintText.setFillColor(sf::Color::Red);

		data.exitGameItem.childrenOrientation = Orientation::Horizontal;
		data.exitGameItem.childrenAlignment = Alignment::Middle;
		data.exitGameItem.childrenSpacing = 10.f;

		data.exitGameItem.children.push_back(&data.yesItem);
		data.exitGameItem.children.push_back(&data.noItem);

		data.yesItem.text.setString("Yes");
		data.yesItem.text.setFont(data.font);
		data.yesItem.text.setCharacterSize(24);

		data.noItem.text.setString("No");
		data.noItem.text.setFont(data.font);
		data.noItem.text.setCharacterSize(24);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.startGameItem);
	}

	void ShutdownGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
	}

	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event)
	{
		if (data.isEnteringName)
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode >= 32 && event.text.unicode < 128 &&
					data.enteredName.size() < 12)
				{
					data.enteredName += static_cast<char>(event.text.unicode);
				}
				else if (event.text.unicode == 8 && !data.enteredName.empty())
				{
					data.enteredName.pop_back();
				}

				if (data.enteredName.empty())
					data.nameInputText.setString("_");
				else
					data.nameInputText.setString(data.enteredName);
			}

			if (event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Enter &&
				!data.enteredName.empty())
			{
				game.playerName = data.enteredName;
				data.isEnteringName = false;
			}

			return;
		}

		if (!data.menu.selectedItem)
			return;

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				CollapseSelectedItem(data.menu);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (data.menu.selectedItem == &data.startGameItem)
					SwitchGameState(game, GameStateType::Playing);
				else if (data.menu.selectedItem == &data.difficultyItem)
					ExpandSelectedItem(data.menu);
				else if (data.menu.selectedItem == &data.easyItem)
				{
					game.difficulty = GameDifficulty::Easy;
					CollapseSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.normalItem)
				{
					game.difficulty = GameDifficulty::Normal;
					CollapseSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.hardItem)
				{
					game.difficulty = GameDifficulty::Hard;
					CollapseSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.optionsItem)
					ExpandSelectedItem(data.menu);
				else if (data.menu.selectedItem == &data.optionsInfiniteApplesItem)
					game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::InfiniteApples);
				else if (data.menu.selectedItem == &data.optionsWithAccelerationItem)
					game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::WithAcceleration);
				else if (data.menu.selectedItem == &data.optionsSoundItem)
					game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::SoundEnabled);
				else if (data.menu.selectedItem == &data.recordsItem)
					PushGameState(game, GameStateType::Records, true);
				else if (data.menu.selectedItem == &data.exitGameItem)
					ExpandSelectedItem(data.menu);
				else if (data.menu.selectedItem == &data.yesItem)
					SwitchGameState(game, GameStateType::None);
				else if (data.menu.selectedItem == &data.noItem)
					CollapseSelectedItem(data.menu);
			}

			Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;

			if ((orientation == Orientation::Vertical && event.key.code == sf::Keyboard::W) ||
				(orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left))
			{
				SelectPreviousMenuItem(data.menu);
			}
			else if ((orientation == Orientation::Vertical && event.key.code == sf::Keyboard::S) ||
				(orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right))
			{
				SelectNextMenuItem(data.menu);
			}
		}
	}

	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game, float timeDelta)
	{
		bool isInfiniteApples = ((std::uint8_t)game.options & (std::uint8_t)GameOptions::InfiniteApples) != 0;
		data.optionsInfiniteApplesItem.text.setString("Infinite Apples: " + std::string(isInfiniteApples ? "On" : "Off"));

		bool isWithAcceleration = ((std::uint8_t)game.options & (std::uint8_t)GameOptions::WithAcceleration) != 0;
		data.optionsWithAccelerationItem.text.setString("With Acceleration: " + std::string(isWithAcceleration ? "On" : "Off"));

		bool isSoundEnabled = ((std::uint8_t)game.options & (std::uint8_t)GameOptions::SoundEnabled) != 0;
		data.optionsSoundItem.text.setString("Sound: " + std::string(isSoundEnabled ? "On" : "Off"));
	}

	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();

		if (data.isEnteringName)
		{
			data.nameHintText.setOrigin(GetTextOrigin(data.nameHintText, { 0.5f, 0.f }));
			data.nameHintText.setPosition(viewSize.x / 2.f, 220.f);

			data.nameInputText.setOrigin(GetTextOrigin(data.nameInputText, { 0.5f, 0.f }));
			data.nameInputText.setPosition(viewSize.x / 2.f, 300.f);

			window.draw(data.nameHintText);
			window.draw(data.nameInputText);
			return;
		}

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);

		window.draw(*hintText);
		DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });
	}
}