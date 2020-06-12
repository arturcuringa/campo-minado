#include "Board.h"
#include<iostream>
#include "GameManager.h"
#include <SFML/Graphics.hpp>

int main() {

	sf::RenderWindow window(sf::VideoMode(600, 600), "MineSweeper", sf::Style::Titlebar | sf::Style::Close);
	GameManager gm(window);
	gm.run();

}