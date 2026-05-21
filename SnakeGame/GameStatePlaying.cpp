#include "GameStatePlaying.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>

namespace SnakeGame
{
	void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
	{

		LoadSnakeTextures(data.snake);
		assert(data.appleTexture.loadFromFile(TEXTURES_PATH + "Apple.png"));
		assert(data.rockTexture.loadFromFile(TEXTURES_PATH + "Rock.png"));
		assert(data.font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(data.eatAppleSoundBuffer.loadFromFile(SOUNDS_PATH + "AppleEat.wav"));
		assert(data.gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));


		data.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEGHT));
		data.background.setPosition(0.f, 0.f);
		data.background.setFillColor(sf::Color(0, 200, 0));


		InitSnake(data.snake);

		switch (game.difficulty)
		{
		case GameDifficulty::Easy:
			data.snake.speed = INITIAL_SPEED * 0.75f;
			break;
		case GameDifficulty::Hard:
			data.snake.speed = INITIAL_SPEED * 1.5f;
			break;
		default:
			break;
		}


		InitSprite(data.apple, APPLE_SIZE, APPLE_SIZE, data.appleTexture);
		SetSpriteRandomPosition(data.apple, data.background.getGlobalBounds(), data.snake.body);


		data.rocks.resize(ROCKS_COUNT);
		for (sf::Sprite& rock : data.rocks) {
			InitSprite(rock, ROCK_SIZE, ROCK_SIZE, data.rockTexture);
			SetSpriteRandomPosition(rock, data.background.getGlobalBounds(), data.snake.body);
		}

		data.numEatenApples = 0;

		data.scoreText.setFont(data.font);
		data.scoreText.setCharacterSize(24);
		data.scoreText.setFillColor(sf::Color::Yellow);

		data.inputHintText.setFont(data.font);
		data.inputHintText.setCharacterSize(24);
		data.inputHintText.setFillColor(sf::Color::White);
		data.inputHintText.setString("Use arrow keys to move, ESC to pause");
		data.inputHintText.setOrigin(GetTextOrigin(data.inputHintText, { 1.f, 0.f }));


		data.eatAppleSound.setBuffer(data.eatAppleSoundBuffer);
		data.gameOverSound.setBuffer(data.gameOverSoundBuffer);
	}

	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game)
	{

	}

	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PushGameState(game, GameStateType::ExitDialog, false);
			}
		}
	}

	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			data.snake.direction = SnakeDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			data.snake.direction = SnakeDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			data.snake.direction = SnakeDirection::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			data.snake.direction = SnakeDirection::Left;
		}

		MoveSnake(data.snake, timeDelta);

		if (CheckSpriteIntersection(*data.snake.head, data.apple)) {
			if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::SoundEnabled)
				data.eatAppleSound.play();

			GrowSnake(data.snake);

			data.numEatenApples++;

			SetSpriteRandomPosition(data.apple, data.background.getGlobalBounds(), data.snake.body);

			if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::WithAcceleration) {
				data.snake.speed += ACCELERATION;
			}
		}

		bool isGameFinished = false;

		const bool isInfiniteApples = ((std::uint8_t)game.options & (std::uint8_t)GameOptions::InfiniteApples) != 0;
		if (!isInfiniteApples)
		{
			int applesToWin = (MIN_APPLES + MAX_APPLES) / 2;
			if (game.difficulty == GameDifficulty::Easy)
				applesToWin = MIN_APPLES;
			else if (game.difficulty == GameDifficulty::Hard)
				applesToWin = MAX_APPLES;

			isGameFinished = data.numEatenApples >= applesToWin;
		}

		if (isGameFinished
			|| !HasSnakeCollisionWithRect(data.snake, data.background.getGlobalBounds())
			|| CheckSnakeCollisionWithHimself(data.snake)	
			|| FullCheckCollisions(data.rocks.begin(), data.rocks.end(), *data.snake.head)) 
		{
			if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::SoundEnabled)
				data.gameOverSound.play();


			game.recordsTable[game.playerName] = std::max(game.recordsTable[game.playerName], data.numEatenApples);

			PushGameState(game, GameStateType::GameOver, false);
		}

		data.scoreText.setString("Apples eaten: " + std::to_string(data.numEatenApples));
	}

	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{

		window.draw(data.background);


		DrawSnake(data.snake, window);

		DrawSprite(data.apple, window);

		DrawSprites(data.rocks.begin(), data.rocks.end(), window);

		data.scoreText.setOrigin(GetTextOrigin(data.scoreText, { 0.f, 0.f }));
		data.scoreText.setPosition(10.f, 10.f);
		window.draw(data.scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		data.inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(data.inputHintText);
	}
}
