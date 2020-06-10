#pragma once
enum class State { BOMB, EMPTY, NEAR };

class Cell {
	public:
		int bombs_near;
		Cell(State _state = State::EMPTY, bool _flag = false) : state(_state), flag(_flag), bombs_near(0), revel(false){

		}

		bool get_flag() {
			return flag;
		}

		State get_state() {
			return state;
		}

		bool get_revealed() {
			return revel;
		}

		int get_bombs_near() {
			return bombs_near;
		}

		void set_flag(bool _flag) {
			flag = _flag;
		}

		void set_state(State _state) {
			state = _state;
		}

		void set_revealed(bool _revel) {
			revel = _revel;
		}
	private:
		State state;
		bool flag;
		bool revel;


};
