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

Player* w_choice(Plateau* plate, Vue* vue){
	string uresp; //string contenant la réponse de l'utilisateur
	Player* playerW;
	while(*(uresp.c_str()) != 'h' || *(uresp.c_str()) != 'f'){
		cout << "Joueur Blanc : IA (i) ou Humain (h) ou Fichier (f) ?" << endl;
		getline(cin, uresp);
		if(*(uresp.c_str()) == 'h'){
			HumanPlayer* playerW = new HumanPlayer(plate, vue);
			break;
		}
		else if(*(uresp.c_str()) == 'f'){
			FilePlayer* playerW = new FilePlayer(plate, vue);
			break;
		}
	}
	return (Player*) playerW;
}

Player* b_choice(Plateau* plate, Vue* vue){
	string uresp; //string contenant la réponse de l'utilisateur
	Player* playerB;
	while(*(uresp.c_str()) != 'h' || *(uresp.c_str()) != 'f'){
		cout << "Joueur Noir : IA (i) ou Humain (h) ou Fichier (f) ?" << endl;
		getline(cin, uresp);
		if(*(uresp.c_str()) == 'h'){
			HumanPlayer* playerB = new HumanPlayer(plate, vue);
			break;
		}
		else if(*(uresp.c_str()) == 'f'){
			FilePlayer* playerB = new FilePlayer(plate, vue);
			break;
		}
	}
	return (Player*) playerB;
}

int main(){
    Plateau* plate = new Plateau();
	Vue* vue = new Vue();
	Player* playerW;
	Player* playerB;
	playerW = w_choice(plate, vue);
	playerB = b_choice(plate, vue);
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

