#include "Cell.h"

bool Cell::get_flag() {
	return flag;
}

State Cell::get_state() {
	return state;
}

bool Cell::get_revealed() {
	return revel;
}

int Cell::get_bombs_near() {
	return bombs_near;
}

void Cell::set_flag(bool _flag) {
	flag = _flag;
}

void Cell::set_state(State _state) {
	state = _state;
}

void Cell::set_revealed(bool _revel) {
	revel = _revel;
}