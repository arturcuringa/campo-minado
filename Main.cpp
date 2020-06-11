//#include <SFML/Graphics.hpp>
#include "Board.h"
#include<iostream>

int main() { 
	/*
	sf::RenderWindow window(sf::VideoMode(800, 600), "Title");
	sf::Event event;

	while (window.isOpen()){
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}
	*/
	Board board(10, 10);
	int row, col, op;
	std::cout << board << "\n" << std::endl;
	std::cout << "Choose the position to start the game:\n row collumn\n";
	std::cin >> row;
	std::cin >> col;
	board.start(1, row, col);
	while (true) {
		std::cout << board << "\n" << std::endl;
		std::cout << "Chose operation:\n1: Reveal cell\n2: Place Flag\n";
		std::cin >> op;
		std::cout << "Choose the position row collumn\n";
		std::cin >> row;
		std::cin >> col;
		if (op == 1) {
			if (!board.play_pos(row, col)) {
				for (auto i = 0; i < 10; i++) {
					for (auto j = 0; j < 10; j++) {
						board.play_pos(i, j);
					}
				}
				std::cout << board << std::endl;
				std::cout << "GAME OVER";
				break;
			}
		}
		else {
			board.place_flag(row, col);
		}
		if (board.check_victory()) {
			std::cout << "VICTORY!!!!!!" << std::endl;
			board.reveal_all();
			std::cout << board << std::endl;
			break;
		}
	}

	std::cout << "\n";
	std::cin.get();
	std::cin.get();
	std::cin.get();
	return 0;
}