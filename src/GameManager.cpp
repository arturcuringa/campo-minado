#include "GameManager.h"

GameManager::GameManager(sf::RenderWindow& win) : window(win) {
	game_state = GameState::INITIAL_MENU;
	board = std::make_unique<Board>(10, 10, 20);
	font.loadFromFile("arial.ttf");
	bomb.loadFromFile("bomb.png");
	flag.loadFromFile("flag.png");
	cell_size = 51.f;
	x_padding = 45.f;
	y_padding = 50.f;

}

void GameManager::run() {
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}


void GameManager::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		//Tela inicial
		if (game_state == GameState::INITIAL_MENU && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			game_state = GameState::BOARD;
			continue;
		}
		//Localiza~ção do mouse
		sf::Vector2i localPosition = sf::Mouse::getPosition(window);
		//Retângulos de colisão para detecção da célula escolhida ou botão de jogar novamente
		sf::Rect<int> grid_rect(x_padding, y_padding, board->get_rows_number() * cell_size + x_padding, board->get_rows_number() * cell_size + y_padding);
		sf::Rect<int> back_button(x_padding, board->get_rows_number() * cell_size + y_padding, 200.f, 200.f);
		//Calcula se o mouse está dentro do grid e qual célula foi selecionada
		if (grid_rect.contains(localPosition)) {
			col_pos = (localPosition.x - x_padding) / cell_size;
			row_pos = (localPosition.y - y_padding) / cell_size;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				square_reveal = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				place_flag = true;
		}

		if (game_state == GameState::GAME_OVER || game_state == GameState::VICTORY) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && back_button.contains(localPosition)) {
				play_again = true;
			}
		}

		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void GameManager::update() {
	if (game_state == GameState::BOARD) {
		if (square_reveal) {
			if (board->is_generated()) {
				bool not_game_over = board->play_pos(row_pos, col_pos);
				if (!not_game_over) {
					board->reveal_all();
					game_state = GameState::GAME_OVER;
				}
			}
			else 
				board->start(row_pos, col_pos);
			square_reveal = false;
		}
		if (place_flag) {
			board->place_flag(row_pos, col_pos);
			place_flag = false;
		}
		bool victory = board->check_victory();
		if (victory) 
			game_state = GameState::VICTORY;
	}
	if ((game_state == GameState::GAME_OVER || game_state == GameState::VICTORY) && play_again) {
		play_again = false;
		board->clear();
		game_state = GameState::BOARD;
		square_reveal = false;
		place_flag = false;
	}
}

void GameManager::draw_board() {
	for (auto i = 0; i < 10; i++) {
		for (auto j = 0; j < 10; j++) {
			sf::RectangleShape shape(sf::Vector2f(cell_size - 1, cell_size - 1));
			auto& cell = board->at(j, i);
			shape.setPosition(x_padding + i * cell_size, y_padding + j * cell_size);

			if (!cell.get_flag() && cell.get_revealed() && cell.get_state() == State::EMPTY)
				shape.setFillColor(sf::Color::Green);

			window.draw(shape);
			if (cell.get_flag()) {
				auto scale_x = 1 / (flag.getSize().x / cell_size);
				auto scale_y = 1 / (flag.getSize().y / cell_size);
				sf::Sprite flag_sprite;
				flag_sprite.setTexture(flag);
				flag_sprite.setScale(scale_x, scale_y);
				flag_sprite.setPosition(x_padding + i * cell_size, y_padding + j * cell_size);
				window.draw(flag_sprite);
			}

			if (!cell.get_flag() && cell.get_revealed() && cell.get_state() == State::NEAR) {

				sf::Text text;
				text.setFont(font);
				text.setString(std::to_string(cell.get_bombs_near()));
				text.setCharacterSize(24);
				text.setPosition(x_padding + i * cell_size, y_padding + j * cell_size);
				text.setFillColor(sf::Color::Red);
				text.setStyle(sf::Text::Bold);
				window.draw(text);
			}

			if (!cell.get_flag() && cell.get_revealed() && cell.get_state() == State::BOMB) {
				auto scale_x = 1 / (bomb.getSize().x / cell_size);
				auto scale_y = 1 / (bomb.getSize().y / cell_size);
				sf::Sprite bomb_sprite;
				bomb_sprite.setTexture(bomb);
				bomb_sprite.setScale(scale_x, scale_y);
				bomb_sprite.setPosition(x_padding + i * cell_size, y_padding + j * cell_size);
				window.draw(bomb_sprite);
			}
		}
	}
}

void GameManager::render() {
	window.clear(sf::Color::Color(143, 137, 120, 255));
	if (game_state == GameState::BOARD) {

		draw_board();
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(20);
		text.setFillColor(sf::Color::Red);
		text.setString("Bandeiras: " + std::to_string(board->get_flag_number()));
		text.setPosition(x_padding, 20.f);
		window.draw(text);
	}
	if (game_state == GameState::GAME_OVER) {
		draw_board();
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(30);
		text.setFillColor(sf::Color::Red);
		text.setString("Acabou, uma bomba estourou");
		text.setPosition(x_padding, 20.f);
		window.draw(text);
		
		text.setString("Jogar de novo");
		text.setPosition(x_padding, board->get_rows_number() * cell_size + y_padding);
		window.draw(text);

	}
	if (game_state == GameState::VICTORY) {
		draw_board();
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(30);
		text.setFillColor(sf::Color::Red);
		text.setString("VITÓRIA");
		text.setPosition(x_padding, 20.f);
		window.draw(text);

		text.setString("Jogar de novo");
		text.setPosition(x_padding, board->get_rows_number() * cell_size + y_padding);
		window.draw(text);

	}

	if (game_state == GameState::INITIAL_MENU) {
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(50);
		text.setFillColor(sf::Color::Red);
		text.setString("Campo Minado");
		text.setPosition(50.f, 40.f);
		window.draw(text);

		text.setString("Controles:\nBotão esquerdo do mouse revela a celula selecionada\nBotão direito adiciona/remove bandeira\nClique com o botão esquerdo do mouse para começar\nQuadrados brancos são células não reveladas\nQuadrados verdes são células vazias");
		text.setCharacterSize(20);
		text.setPosition(50.f, 150.f);
		window.draw(text);
	}


	window.display();
}