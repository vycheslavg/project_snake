#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Snake.h"


namespace SnakeGame
{
	struct Game;

	struct GameStatePlayingData
	{
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::Font font;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;
		Snake snake;
		sf::Sprite apple;
		std::vector<sf::Sprite> rocks;
		int numEatenApples = 0;
		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;
		sf::Sound eatAppleSound;
		sf::Sound gameOverSound;
	};

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game);
	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game);
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event);
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float timeDelta);
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window);
}
