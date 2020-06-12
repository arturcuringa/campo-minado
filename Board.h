#pragma once
#include <memory>
#include <stdexcept>
#include "Cell.h"
#include <utility>
#include <vector>
#include <random>
#include <set>
#include <queue>
#include <iostream>

/**
 * \brief Classe respns�vel pela l�gica do jogo
 */
class Board {

	protected:
		std::size_t rows;
		std::size_t collumns;
		std::unique_ptr<Cell[]> board;
		//Vetor de posi��es das bombas
		std::vector<std::pair<int, int>> bombs;
		//Vari�vel para detectar se as posi��es ds bombas j� foram geradas
		bool generated;
		int revealed;
		int bombs_nb;
		int flags_nb;
		//Iteradores para facilitar a pesquisa ao redor de uma c�lula
		const std::vector<int> y_axis_iterator{ -1, -1, -1,  1, 1, 1,  0, 0 };
		const std::vector<int> x_axis_iterator{ -1,  0,  1, -1, 0, 1, -1, 1 };
	public:
		//Vari�veis necess�rias para gerar um n�mero aleat�rio a partir de uma distribui��o uniforme
		std::mt19937 generator;
		std::uniform_int_distribution<int> distr_rows;
		std::uniform_int_distribution<int> distr_cols;
		Board(std::size_t _rows, std::size_t _collumns, int _bombs_nb);
		Board() {}
		// Fun��o de acesso 
		Cell& at(std::size_t row, std::size_t col);
		void clear();
		bool in_board(int row, int col);
		bool play_pos(int row, int col);
		void place_flag(int row, int col);
		bool check_victory();
		void unreveal();
		void reveal_all();
		//Func��o que d� inic�o ao jogo, recebendo a primeira c�lula selecionada e
		//	garantido que ela seja vazia, evitando que o jogador possa come�ar perdendo
		void start(int row, int col);
		//Sobrecarga de operador para vers�o de terminal
		friend std::ostream& operator<<(std::ostream& os, const Board& _board);
		std::size_t get_rows_number();
		std::size_t get_collumns_number();
		bool is_generated();
		int get_bombs_number();
		int get_flag_number();

	private:
		int get_flat(int i, int j) const;
		//Fun��o geradora de bombas
		void generate_bomb_places(int bombs_nb, int row, int col);
		void add_nearby_count(int row, int col);
		//Busca em largura para expandir espa�os vazios
		void reveal_bfs(int row, int col);

};