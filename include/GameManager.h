#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Board.h"
#include "Cell.h"
#include <string>

/**
 * \brief Enumeração dos estados possíveis no jogo
 */
enum class GameState { INITIAL_MENU, BOARD, GAME_OVER, VICTORY };


/**
 * \brief Classe responsável pelo game loop, renderização e player input, recomendação do framework SFML
 */
class GameManager {

private:
	//Estruturas necessárias para o SFML
	sf::RenderWindow& window;
	sf::Font font;
	sf::Texture bomb;
	sf::Texture flag;
	//Smart pointer para armazenar o tabuleiro e lógica do jogo
	std::unique_ptr<Board> board;
	//Booleanos para auxiliar a comunicação do input handler com o update
	bool square_reveal;
	bool place_flag;
	bool play_again;
	bool start_custom_size;
	//Configuração visual do tabuleiro 
	float x_padding;
	float y_padding;
	float cell_size;
	//Variáveis para auxiliar a detecção da célula escolhida no tabuleiro
	int col_pos;
	int row_pos;
	GameState game_state;
public:
	//Construtor que recebe a referência da janela do SFML a carrega os assets usados no jogo
	GameManager(sf::RenderWindow& win);
	//Game Loop
	void run();

private:
	//Input Handler
	void processEvents();
	// Lógica do jogo
	void update();
	// Função auxiliar para o render, desenhando o grid 
	void draw_board();
	//Renderização
	void render();
};