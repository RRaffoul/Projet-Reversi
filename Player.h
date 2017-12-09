#include <iostream>
#include <string>
#include <sstream>
#include "Plateau.h"
#include "Vue.h"

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
	~Player();
	void Play(int);
	bool Check_input(string);
};

#endif // PLAYER_H

