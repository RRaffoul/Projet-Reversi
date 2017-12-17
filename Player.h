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

class IAPlayer : public Player{
private:
	Plateau imaginaire;
	vector<int> pos_to_check;
	int count;
	int* pos; 
public:	
	IAPlayer(Plateau*, Vue*);
	~IAPlayer();
    void Play(int);
	int* Search_func(Plateau board);
	int* A(Plateau board);
};

class FilePlayer : public Player{
public:
	FilePlayer(Plateau*, Vue*);
	~FilePlayer();
	void Play(int);
	bool Check_input(string);
};

#endif // PLAYER_H

