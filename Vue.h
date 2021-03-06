#include <iostream> //tous utiles ?
#include <string>
#include <sstream>
#include "Plateau.h"

using namespace std;

#ifndef VUE_H
#define VUE_H


class Vue
{
    public :
	Vue();
	~Vue();
	void Print_board(int*);
	void Print_winner(int, int);
    void Print_state(int, int, int);
    void Print_lastMove(string);
    void Game_start();
	void White_turn();
	void Black_turn();
	void Ask_pos();
	void Ask_pos(string);
	void Ask_confirmation();
	void Skip_turn();
	void Cant_skip();
	void Inv_entry_1();
	void Inv_entry_2();
	void Inv_entry_3();
	void Inv_entry_4();
};

#endif // VUE_H

