Player::Player(Plateau* plate, View* vue){
	Plate = plate;
	view = vue;
}



void Player::Play(){
	ok = false;
	//soit c est ici qu on print le plateau soit dans le main, pareil pour la ligne suivante avec les scores
	view->Print_state();
	string input = "";
	while(!ok){
		view->Ask_pos();
		getline(cin, input);
			if(Check_input(input)){
				y = input[0] - 'a';
				x = input[1] - '1';
				if(x =='0' && y =='0'){  //On ferait pas une fonction pour ce if ?
					if(Plate->Check_notplay()){
						view->Skip_turn();
						ok = true;
					}
					else { 
						view->Cant_skip();
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
		y = input[0] - 'a';
        x = input[1] - '1';
		else if(x > 8 || x < 0 || y > 8 || y < 0){ //check si dans le plateau
		view->Inv_entry_1();
			return false;
		}
		else if(Plate[x][y] != 0){ //check si deja un pion a cet endroit là
			view->Inv_entry_2();
			return false;
		}
		else
			return true;
			        
	else {
		view->Inv_entry_3();
		return false;
	}
}
