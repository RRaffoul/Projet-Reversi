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
    if(color == 0){ //Tour du blanc
        vue->White_turn();
		vue->Print_lastMove(last_move);
		if(playerW->confirmation());
			playerB->saveMove(last_move = playerW->Play(turn)); 
			/* 
			 * saveMove permet au programme d'écrire le coup joué
    		 * dans le fichier correspondant (blanc ou noir.txt)
    		 * /!\ c'est playerB(lack) qui a accès en écriture au
    		 * fichier blanc.txt
    		 */ 
	}
    else{ //Tour du noir
	    vue->Black_turn();
		vue->Print_lastMove(last_move);
		if(playerB->confirmation());
			playerW->saveMove(last_move = playerB->Play(turn));
    }
    return last_move;
}

Player* choice(Plateau* plate, Vue* vue, string player_name){
	string uresp; //string contenant la réponse de l'utilisateur
	while(*(uresp.c_str()) != 'h' || *(uresp.c_str()) != 'f' || *(uresp.c_str()) != 'i'){
		// c_str() permettre de convertir le string 'uresp' qui contient un char plus char équiv. à ENTER
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
	string last_move =""; 	// Nécessaire pour afficher la position du 
							// dernier pion placé
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
