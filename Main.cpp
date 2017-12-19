#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

#include "Vue.h"
#include "Plateau.h"
#include "Player.h"


string Turn(int turn, Vue* vue, Player* playerW, Player* playerB, string last_move){
    int color = turn %2;
    /*int x;
    int y;*/
    if(color == 0){
        vue->White_turn();
        last_move = playerW->Play(turn, last_move);
    }

    else{
	    vue->Black_turn();
        last_move = playerB->Play(turn, last_move);
    }
    return last_move;
}

Player* choice(Plateau* plate, Vue* vue, string player_name){
	string uresp; //string contenant la réponse de l'utilisateur
	while(*(uresp.c_str()) != 'h' || *(uresp.c_str()) != 'f'){
		cout << "Joueur " << player_name << " : IA (i) ou Humain (h) ou Fichier (f) ?" << endl;
		getline(cin, uresp);
		if(*(uresp.c_str()) == 'h'){
			HumanPlayer* player = new HumanPlayer(plate, vue);
	        return player;
		}
		else if(*(uresp.c_str()) == 'f'){
			FilePlayer* player = new FilePlayer(plate, vue, player_name);
	        return player;
		}
		else if(*(uresp.c_str()) == 'i'){
			IAPlayer* player = new IAPlayer(plate, vue);
	        return player;
		}
	}

}


int main(){
    Plateau* plate = new Plateau();
	Vue* vue = new Vue();
	Player* playerW;
	Player* playerB;
	playerW = choice(plate, vue, "blanc");
	playerB = choice(plate, vue, "noir");
	int turn = 0;
	string last_move = "";
	cout << "Début de la partie" << endl;
	while(!plate->Game_over()){
		turn++;
	    vue->Print_board(plate->Get_Plate());
		last_move = Turn(turn, vue, playerW, playerB, last_move);
	}
	vue->Print_board(plate->Get_Plate());
	vue->Print_winner(plate->Get_Noirs(), plate->Get_Blancs());
	delete playerW;
	delete playerB;
	delete vue;
	delete plate;
	return 0;
}

