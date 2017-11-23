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
};

