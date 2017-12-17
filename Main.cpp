#include <iostream>
#include <string>
#include <sstream>


using namespace std;

#include "Vue.h"
#include "Plateau.h"
#include "Player.h"

void Turn(int turn, Vue* vue, Player* playerW, Player* playerB){
    int color = (turn + 1)%2 + 1;
    /*int x;
    int y;*/
    if(color == 1){
        vue->White_turn();
        playerW->Play(turn);
    }

    else{
	    vue->Black_turn();
        playerB->Play(turn);
    }
}

Player* choice(Plateau* plate, Vue* vue){
	string uresp; //string contenant la réponse de l'utilisateur
	while(*(uresp.c_str()) != 'h' || *(uresp.c_str()) != 'f'){
		cout << "Joueur Blanc : IA (i) ou Humain (h) ou Fichier (f) ?" << endl;
		getline(cin, uresp);
		if(*(uresp.c_str()) == 'h'){
			HumanPlayer* player = new HumanPlayer(plate, vue);
	        return player;
		}
		else if(*(uresp.c_str()) == 'f'){
			FilePlayer* player = new FilePlayer(plate, vue);
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
	playerW = choice(plate, vue);
	playerB = choice(plate, vue);
	int turn = 0;
	while(!plate->Game_over()){
		turn++;
	    vue->Print_board(plate->Get_Plate());
		Turn(turn, vue, playerW, playerB);
	}
	vue->Print_board(plate->Get_Plate());
	vue->Print_winner(plate->Get_Noirs(), plate->Get_Blancs());
	delete playerW;
	delete playerB;
	delete vue;
	delete plate;
	return 0;
}

