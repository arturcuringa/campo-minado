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

class Board {

	protected:
		std::size_t rows;
		std::size_t collumns;
		std::unique_ptr<Cell[]> board;
		std::vector<std::pair<int, int>> bombs;
		bool generated;
		int revealed = 0;
		int bombs_nb = 0;
		int flags_nb = 0;
		const std::vector<int> y_axis_iterator{ -1, -1, -1,  1, 1, 1,  0, 0 };
		const std::vector<int> x_axis_iterator{ -1,  0,  1, -1, 0, 1, -1, 1 };
	public:
		std::mt19937 generator;
		std::uniform_int_distribution<int> distr_rows;
		std::uniform_int_distribution<int> distr_cols;

		Board(std::size_t _rows, std::size_t _collumns);
		// Instead of create a friend class, use at to access the cell
		Cell& at(std::size_t row, std::size_t col);
		void clear();
		bool in_board(int row, int col);
		bool play_pos(int row, int col);
		void place_flag(int row, int col);
		bool check_victory();
		void unreveal();
		void reveal_all();
		void start(int bombs_nb, int row, int col);
		friend std::ostream& operator<<(std::ostream& os, const Board& _board);

	private:
		int get_flat(int i, int j) const;
		void generate_bomb_places(int bombs_nb, int row, int col);
		void add_nearby_count(int row, int col);
		void reveal_bfs(int row, int col);

};