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
	virtual string Play(int);
	bool Check_input(string);
	virtual void saveMove(string);
};

class HumanPlayer : public Player{
public:	
	HumanPlayer(Plateau*, Vue*);
	~HumanPlayer();
	string Play(int);
	//bool Check_input(string);
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
	//bool Check_input(string);
	void saveMove(string);
	string getMove();
};

#endif // PLAYER_H

