#include <iostream>
#include <string>
#include <sstream>
#include <vector>

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

 public :
	Plateau ();
	~Plateau();
	bool Check_direction(int x, int y, int direction[2]);
	bool Check_direction2(int x, int y, int direction[2]);
	bool Check_Direction3(int x, int y, int, int);
	bool Check_eat(int x, int y);
	bool Playable(int x, int y);
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
    float Corner();
    int Mobility();
    int Stability(int);
    bool Check_Stability(int,int);
};

#endif // PLATEAU_H

