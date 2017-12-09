#include "Player.h"

Player::Player(Plateau plate, Vue vue){
	Plate = plate;
	Vue = vue;
}

void Player::Play(){
	ok = false;
	//soit c est ici qu on print le plateau soit dans le main, pareil pour la ligne suivante avec les scores
	*Vue.Print_state();
	string input = "";
	while(!ok){
		Vue->Ask_pos();
		getline(cin, input);
			if(Check_input(input)){
				int y = input[0] - 'a';
				int x = input[1] - '1';
				if(x =='0' && y =='0'){  //On ferait pas une fonction pour ce if ?
					if(Plate->Check_notplay()){
						Vue->Skip_turn();
						ok = true;
					}
					else { 
						Vue->Cant_skip();
						//ok = false;
					}
				}
				else if(Plate->Check_eat(x,y)){
					Plate->Eat();
					ok = true;
				}
		}
	}
}


bool Player::Check_input(string input){
	if(input.length() == 2){               
		int y = input[0] - 'a';
        int x = input[1] - '1';
		else if(x > 8 || x < 0 || y > 8 || y < 0){ //check si dans le plateau
		Vue->Inv_entry_1();
			return false;
		}
		else if(Plate[x][y] != 0){ //check si deja un pion a cet endroit là
			Vue->Inv_entry_2();
			return false;
		}
		else
			return true;
			        
	else {
		Vue->Inv_entry_3();
		return false;
	}
}
