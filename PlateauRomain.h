#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Plateau {
 private :
	int plateau [8][8]; 
	vector<int> pos_to_eat;
	int turn = 0;
	int color;
 public :
	Plateau ();
	void print_board();
	bool check_input(int x, int y);
	bool check_direction(int x, int y, int direction[2]);
	bool check_eat(int x, int y);
	void eat();
	bool check_notplay();
	void player_turn();
};

