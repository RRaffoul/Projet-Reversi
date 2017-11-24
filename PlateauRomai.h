#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Plateau {
 private :
	int plateau [8][8]; 
	vector<int> pos_to_eat;
	int turn;
	int color;
	int passe;
	int noirs;
	int blancs;
	bool over;
 public :
	Plateau ();
	int get_noirs();
	int get_blancs();
	void print_board();
	bool check_input(int x, int y);
	bool check_direction(int x, int y, int direction[2]);
	bool check_eat(int x, int y);
	void eat();
	bool check_notplay();
	void print_winner();
	bool player_turn();
	bool game_over();
	void game();
};
