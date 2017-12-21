#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <chrono>
#include <thread>
#include "Vue.h"
#include "cmath"

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
	virtual string Play(int)=0;
	bool Check_input(string);
	virtual void saveMove(string);
	virtual bool confirmation();
};

class HumanPlayer : public Player{
public:	
	HumanPlayer(Plateau*, Vue*);
	~HumanPlayer();
	string Play(int);
};

class IAPlayer : public Player{
private:
	Plateau imaginaire;
public:	
	IAPlayer(Plateau*, Vue*);
	~IAPlayer();
    string Play(int);
    float Heuristic(Plateau,int,int);
	float A(Plateau,int,int);
};

class FilePlayer : public Player{
private:
	fstream fichier_ecr;
	fstream fichier_lect;
	string name;
public:
	FilePlayer(Plateau*, Vue*, string);
	~FilePlayer();
	void explore(char *);
	string init();
	string Play(int);
	void saveMove(string);
	string getMove();
	bool confirmation();
};

#endif // PLAYER_H

