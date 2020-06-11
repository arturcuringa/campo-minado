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
		bool generated;
		const std::vector<int> y_axis_iterator{ -1, -1, -1,  1, 1, 1,  0, 0 };
		const std::vector<int> x_axis_iterator{ -1,  0,  1, -1, 0, 1, -1, 1 };
	public:
		std::mt19937 generator;
		std::uniform_int_distribution<int> distr_rows;
		std::uniform_int_distribution<int> distr_cols;

		Board(std::size_t _rows, std::size_t _collumns) {
			rows = _rows;
			collumns = _collumns;

			board = std::make_unique<Cell[]>(rows * collumns);
			for (auto i = 0; i < rows * collumns; i++) {
				board[i] = Cell();
			}
			generator = std::mt19937(std::random_device()());
			distr_rows = std::uniform_int_distribution<int>(0, rows - 1 );
			distr_cols = std::uniform_int_distribution<int>(0, collumns - 1);
		}

		int get_flat(int i, int j) const {
			if (i < 0 || i >= rows) {
				throw std::out_of_range("Row index out of range");
			}
			if (j < 0 || j >= collumns) {
				throw std::out_of_range("Coulumn index out of range");
			}
			return i * collumns + j;
		}

		// Instead of create a friend class, use at to access the cell
		Cell& at(std::size_t row, std::size_t col) {
			return board[get_flat(row, col)];
		}

		std::vector<std::pair<int, int>> generate_bomb_places(int bombs_nb, int row, int col) {
			if (bombs_nb >= rows * collumns)
				throw std::runtime_error("Too mutch bombs");
			std::set<std::pair<int, int>> bombs_positions;
			std::set<std::pair<int, int>> inital_space_area;
			auto inital_pos = std::make_pair(row, col);

			inital_space_area.insert(inital_pos);
			for (auto i = 0; i < 8; i++) {
				auto y_pos = row + y_axis_iterator[i];
				auto x_pos = col + x_axis_iterator[i];
				inital_space_area.insert(std::make_pair(y_pos, x_pos));
			}
				
			for (auto bomb = 0; bomb < bombs_nb; bomb++) {
				std::pair<int, int> position;
				do {
					auto _row = distr_rows(generator);
					auto _col = distr_cols(generator);
					position = std::make_pair(_row, _col);
				} while (bombs_positions.find(position) != bombs_positions.end() || inital_space_area.find(position) != inital_space_area.end());

				bombs_positions.insert(position);			
			}
			std::vector<std::pair<int, int>> output(bombs_positions.begin(), bombs_positions.end());
			return output;
		}

		void clear() {
			for (auto row = 0; row < rows; row++) {
				for (auto col = 0; col < col; col++) {
					Cell& cell = this->at(row, col);
					cell.set_state(State::EMPTY);
					cell.set_flag(false);
					cell.set_revealed(false);
					cell.bombs_near = 0;
				}
			}
		}

		bool in_board(int row, int col) {
			if (row < 0 || row >= rows || col < 0 || col >= collumns)
				return false;
			return true;
		}

		void add_nearby_count(int row, int col) {


			for (auto i = 0; i < 8; i++) {
				auto y_pos = row + y_axis_iterator[i];
				auto x_pos = col + x_axis_iterator[i];
				if (in_board(y_pos, x_pos)) {
					Cell& cell = at(y_pos, x_pos);
					if (cell.get_state() == State::EMPTY)
						cell.set_state(State::NEAR);
					cell.bombs_near += 1;
				}
			}

		}

		void reveal_bfs(int row, int col) {
			std::queue<std::pair<int,int>> q;
			q.push(std::make_pair(row, col));
			while (!q.empty()) {
				auto pos = q.front();
				Cell& cell = at(pos.first, pos.second);
				cell.set_revealed(true);
				q.pop();
				for (auto i = 0; i < 8; i++) {
					auto new_pos = std::make_pair(pos.first + y_axis_iterator[i], pos.second + x_axis_iterator[i]);
					if (in_board(new_pos.first, new_pos.second)) {
						auto& tmp_cell = at(new_pos.first, new_pos.second);
						if (!tmp_cell.get_revealed()) {
							tmp_cell.set_revealed(true);
							if (tmp_cell.get_state() == State::EMPTY)
								q.push(new_pos);
						}

					}
						
				}
			}
		}

		bool play_pos(int row, int col) {
			if (in_board(row, col)) {
				auto& cell = at(row, col);
				if (cell.get_state() == State::EMPTY) {
					reveal_bfs(row, col);
				}
				else if (cell.get_state() == State::NEAR) {
					cell.set_revealed(true);
				}
				else {
					//Game over
					cell.set_revealed(true);
					return false;
				}
			}
			return true;
		}

		void unreveal() {
			for (auto row = 0; row < rows; row++) {
				for (auto col = 0; col < col; col++) {
					Cell& cell = at(row, col);
					cell.set_revealed(false);
					cell.set_flag(false);
				}
			}
		}

		void start(int bombs_nb, int row, int col) {
			if (!generated) {
				auto bombs = generate_bomb_places(bombs_nb, row, col);
				for (auto bomb : bombs) {
					Cell& cell = at(bomb.first, bomb.second);
					cell.set_state(State::BOMB);
					add_nearby_count(bomb.first, bomb.second);
				}
				play_pos(row, col);

			}
			else {
				unreveal();
				play_pos(row, col);

			}
		}

		friend std::ostream& operator<<(std::ostream& os, const Board& _board) {
			for (auto row = 0; row < _board.rows; row++) {
				for (auto col = 0; col< _board.collumns; col++) {
					auto cell = _board.board[_board.get_flat(row, col)];
					if (cell.get_revealed()) {
						if (cell.get_state() == State::BOMB)
							os << 'X';
						if (cell.get_state() == State::EMPTY)
							os << '_';
						if (cell.get_state() == State::NEAR)
							os << cell.bombs_near;

					}else
						os << '?';
					if (col != _board.collumns - 1)
						os << " ";
				}
				if (row != _board.rows - 1)
					os << "\n";
			}
			return os;
		}
};