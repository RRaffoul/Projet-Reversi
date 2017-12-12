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

int main(){
    Plateau* plate = new Plateau();
	Vue* vue = new Vue();
	Player* playerW = new Player(plate, vue);
	Player* playerB = new Player(plate, vue);
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

