#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <chrono>
#include <thread>
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
	virtual string Play(int, string);
	bool Check_input(string);
};

class HumanPlayer : public Player{
public:	
	HumanPlayer(Plateau*, Vue*);
	~HumanPlayer();
	string Play(int, string);
	//bool Check_input(string);
};

class FilePlayer : public Player{
private:
	fstream fichier_ecr;
	fstream fichier_lect;
public:
	FilePlayer(Plateau*, Vue*, string);
	~FilePlayer();
	void explore(char *);
	string init();
	string Play(int, string);
	//bool Check_input(string);
	string getLastMove();
	string getMove();
};

#endif // PLAYER_H

