#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

#ifndef PLATEAU_H
#define PLATEAU_H


class Plateau
{
 private :
	int plateau [8][8];
	vector<int> pos_to_eat;
	int turn;
	int color;
	int passe;
	int noirs;
	int blancs;
	int valeurs [8][8];
 public :
	Plateau ();
	~Plateau();
	bool Check_direction(int, int, int direction[2]);
	bool Check_direction2(int, int, int direction[2]);
	bool Check_Direction3(int, int, int, int);
	bool Check_eat(int, int);
	bool Playable(int, int);
	int* Get_Plate();
    int Get_Blancs();
    int Get_Noirs();
    void Set_Turn(int);
    int Get_Turn();
	void Eat();
	bool Check_notplay();
	void Not_play();
    vector<int> Pos_Play();
    bool Game_over();
    void Corner();
    void Corner_It(int, int, int, int,int,int);
    int Heurist(int);
};

#endif // PLATEAU_H

