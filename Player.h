#include <iostream>
#include <string>
#include <sstream>
#include "Vue.h"

class Player {
 private:
	bool ok;
	Plateau* Plate;
	Vue* vue;
 public:
	Player(Plateau* Plate, Vue* vue);
	~Player();
	void Play();
	void Check_input(string);
};
