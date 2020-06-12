#pragma once
enum class State { BOMB, EMPTY, NEAR };

class Cell {
	public:
		int bombs_near;
		Cell(State _state = State::EMPTY, bool _flag = false) : state(_state), flag(_flag), bombs_near(0), reveal(false) {}
		bool get_flag();
		State get_state();
		bool get_revealed();
		int get_bombs_near();
		void set_flag(bool _flag);
		void set_state(State _state);
		void set_revealed(bool _revel);
	private:
		State state;
		bool flag;
		bool reveal;


};
