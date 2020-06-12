#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Board.h"
#include "Cell.h"
#include <string>

/**
 * \brief Enumera��o dos estados poss�veis no jogo
 */
enum class GameState { INITIAL_MENU, BOARD, GAME_OVER, VICTORY };


/**
 * \brief Classe respons�vel pelo game loop, renderiza��o e player input, recomenda��o do framework SFML
 */
class GameManager {

private:
	//Estruturas necess�rias para o SFML
	sf::RenderWindow& window;
	sf::Font font;
	sf::Texture bomb;
	sf::Texture flag;
	//Smart pointer para armazenar o tabuleiro e l�gica do jogo
	std::unique_ptr<Board> board;
	//Booleanos para auxiliar a comunica��o do input handler com o update
	bool square_reveal;
	bool place_flag;
	bool play_again;
	bool start_custom_size;
	//Configura��o visual do tabuleiro 
	float x_padding;
	float y_padding;
	float cell_size;
	//Vari�veis para auxiliar a detec��o da c�lula escolhida no tabuleiro
	int col_pos;
	int row_pos;
	GameState game_state;
public:
	//Construtor que recebe a refer�ncia da janela do SFML a carrega os assets usados no jogo
	GameManager(sf::RenderWindow& win);
	//Game Loop
	void run();

private:
	//Input Handler
	void processEvents();
	// L�gica do jogo
	void update();
	// Fun��o auxiliar para o render, desenhando o grid 
	void draw_board();
	//Renderiza��o
	void render();
};