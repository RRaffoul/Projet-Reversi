#include <iostream>
#include <string>
#include <sstream>
#include "Vue.h"

using namespace std;

#ifndef PLAYER_H
#define PLAYER_H


class Player
{
 protected: //Nécessaire pour que les classes enfants puissent y accéder
	bool ok;
	Plateau* plate;
	Vue* vue;
 public:
	Player(Plateau*, Vue*);
	virtual ~Player();
	virtual void Play(int);
	virtual bool Check_input(string);
};

class HumanPlayer : public Player{
public:	
	HumanPlayer(Plateau*, Vue*);
	~HumanPlayer();
	void Play(int);
	bool Check_input(string);
};

class FilePlayer : public Player{
public:
	FilePlayer(Plateau*, Vue*);
	~FilePlayer();
	void Play(int);
	bool Check_input(string);
};

#endif // PLAYER_H

