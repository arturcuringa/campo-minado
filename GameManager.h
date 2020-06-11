#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class GameManager {

private:
	std::unique_ptr<sf::RenderWindow> window;
	sf::Text text;
	sf::Font font;

public:
	enum class GameState {INITIAL_MENU, CONFIG_MENU, DIFICULT_MENU, BOARD, GAME_OVER, VICTORY};
	GameManager() {
		window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "SFML works!");
		font.loadFromFile("arial.ttf");
		// select the font
		text.setFont(font); // font is a sf::Font

		// set the string to display
		text.setString("Hello world");

		// set the character size
		text.setCharacterSize(24); // in pixels, not points!

		// set the color
		text.setFillColor(sf::Color::Red);

		// set the text style
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	}

	void run() {
		while (window->isOpen()) {
			processEvents();
			update();
			render();
		}
	}

	void processEvents() {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();
		}
	}
	
	void update() {
		
	}

	void render() {
		window->clear();
		for (auto i = 0; i < 10; i++) {
			for (auto j = 0; j < 10; j++) {
				sf::RectangleShape shape(sf::Vector2f(50.f, 50.f));
				shape.setPosition(20.0f + i * 55.f, 20.0f + j * 55.f);
				window->draw(shape);
			}
		}
		window->draw(text);
		window->display();
	}

	
};