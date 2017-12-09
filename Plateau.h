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
	bool Check_direction(int x, int y, int direction[2]);
	bool Check_eat(int x, int y);
	void Eat();
	bool Check_notplay();
    bool Game_over();
};

