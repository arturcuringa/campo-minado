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
	board.start(20);
	int row, col;
	while (true) {
		std::cout << board << "\n" << std::endl;
		std::cin >> row;
		std::cin >> col;
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

	std::cout << "\n";
	std::cin.get();
	std::cin.get();
	std::cin.get();
	return 0;
}