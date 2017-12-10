#include <iostream>
#include <string>
#include <sstream>
#include "Vue.h"

<<<<<<< HEAD
class Player {
 private:
	bool ok;
	Plateau* Plate;
	Vue* vue;
 public:
	Player(Plateau* Plate, Vue* vue);
=======
using namespace std;

#ifndef PLAYER_H
#define PLAYER_H


class Player
{
 private:
	bool ok;
	Plateau* plate;
	Vue* vue;
 public:
	Player(Plateau*, Vue*);
>>>>>>> fcd09c107745d1440c495ca0ad8ad4acf0286fb7
	~Player();
	void Play(int);
	bool Check_input(string);
};

#endif // PLAYER_H

