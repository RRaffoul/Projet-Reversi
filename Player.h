#include <iostream>
#include <string>
#include <sstream>
#include "Plateau.h"
#include "Vue.h"


class Player {
 private:
	bool ok;
	Plateau *Plate;
	Vue *Vue;
 public:
	Player(Plateau, Vue);
	~Player();
	void Play();
	void Check_input(string);
};
