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
 public :
	Plateau ();
	~Plateau();
	int get_noirs();
	int get_blancs();
	bool check_direction(int x, int y, int direction[2]);
	bool check_eat(int x, int y);
	void eat();
	bool check_notplay();
};

