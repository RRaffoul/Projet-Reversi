#include "Player.h"

<<<<<<< HEAD
Player::Player(Plateau* plate, Vue* vue){
	Plate = plate;
	vue = vue;
	ok = false;
=======
Player::Player(Plateau* platee, Vue* vuee){
	plate = platee;
	vue = vuee;
>>>>>>> fcd09c107745d1440c495ca0ad8ad4acf0286fb7
}

Player::~Player(){
}

void Player::Play(int turn){
	ok = false;
	//soit c est ici qu on print le plateau soit dans le main, pareil pour la ligne suivante avec les scores
<<<<<<< HEAD
	vue->Print_state();
=======
	vue->Print_state(plate->Get_Noirs(), plate->Get_Blancs(), turn);
>>>>>>> fcd09c107745d1440c495ca0ad8ad4acf0286fb7
	string input = "";
	while(!ok){
		vue->Ask_pos();
		getline(cin, input);
			if(Check_input(input)){
				int y = input[0] - 'a';
				int x = input[1] - '1';
<<<<<<< HEAD
				if(x =='0' && y =='0'){  //On ferait pas une fonction pour ce if ?
					if(Plate->Check_notplay()){
						vue->Skip_turn();
						ok = true;
					}
					else { 
=======
                plate->Set_Turn(turn);
				if(x ==('0'-'1') && y ==('0'-'a')){  //On ferait pas une fonction pour ce if ?
					if(plate->Check_notplay()){
						vue->Skip_turn();
						ok = true;
					}
					else {
>>>>>>> fcd09c107745d1440c495ca0ad8ad4acf0286fb7
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
<<<<<<< HEAD
		else if(x > 8 || x < 0 || y > 8 || y < 0){ //check si dans le plateau
		vue->Inv_entry_1();
			return false;
		}
		else if(Plate[x][y] != 0){ //check si deja un pion a cet endroit là
=======
        if(x ==('0'-'1') && y ==('0'-'a')){
			cout<< "lol" << endl;
			return true;
		}
        else if(x > 8 || x < 0 || y > 8 || y < 0){ //check si dans le plateau
		    vue->Inv_entry_1();
			return false;
		}
		else if(*(plate->Get_Plate() + 8 * x + y) != 0){ //check si deja un pion a cet endroit là
>>>>>>> fcd09c107745d1440c495ca0ad8ad4acf0286fb7
			vue->Inv_entry_2();
			return false;
		}
		else
			return true;
<<<<<<< HEAD
	}
			        
=======
    }
>>>>>>> fcd09c107745d1440c495ca0ad8ad4acf0286fb7
	else {
		vue->Inv_entry_3();
		return false;
	}
}
