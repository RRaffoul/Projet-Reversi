#include "Player.h"


Player::Player(Plateau* platee, Vue* vuee){
	plate = platee;
	vue = vuee;
}

Player::~Player(){
}

void Player::Play(int turn){
	ok = false;
	//soit c est ici qu on print le plateau soit dans le main, pareil pour la ligne suivante avec les scores
	vue->Print_state(plate->Get_Noirs(), plate->Get_Blancs(), turn);
	string input = "";
	while(!ok){
		vue->Ask_pos();
		getline(cin, input);
			if(Check_input(input)){
				int y = input[0] - 'a';
				int x = input[1] - '1';
                plate->Set_Turn(turn);
				if(x ==('0'-'1') && y ==('0'-'a')){  //On ferait pas une fonction pour ce if ?
					if(plate->Check_notplay()){
						vue->Skip_turn();
						ok = true;
					}
					else {
						vue->Cant_skip();
						//ok = false;
					}
				}
				else if(plate->Check_eat(x,y)){
					plate->Eat();
					ok = true;
				}
                else
                    vue->Inv_entry_4();
		}
	}
}


bool Player::Check_input(string input){
	if(input.length() == 2){
		int y = input[0] - 'a';
        int x = input[1] - '1';
        if(x ==('0'-'1') && y ==('0'-'a')){
			cout<< "lol" << endl;
			return true;
		}
        else if(x > 8 || x < 0 || y > 8 || y < 0){ //check si dans le plateau
		    vue->Inv_entry_1();
			return false;
		}
		else if(*(plate->Get_Plate() + 8 * x + y) != 0){ //check si deja un pion a cet endroit là
			vue->Inv_entry_2();
			return false;
		}
		else
			return true;
    }
	else {
		vue->Inv_entry_3();
		return false;
	}
}
