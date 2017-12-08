void Player::Turn(){
	ok = false;
	//soit c est ici qu on print le plateau soit dans le main, pareil pour la ligne suivante avec les scores
	view->print_state(Plate);
	while(!ok){
		view->ask_pos(Plate);
		getline(cin, input);
			if(check_input(input)){
				y = input[0] - 'a';
				x = input[1] - '1';
				if(x =='0' && y =='0'){  //On ferait pas une fonction pour ce if ?
					if(Plate->check_notplay()){
						view->Skip_turn();
						ok = true;
					}
					else { 
						view->Cant_skip();
						//ok = false;
					}
				}
				else if(Plate->check_eat(x,y)){
					Plate->eat();
					ok = true;
				}
		}
	}
}


bool Player::check_input(string input){
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



			
			
        else if(check_input(x,y)){
		pos_to_eat.clear();					
			if(check_eat(x,y)){
				passe = 0;
				eat();
				break;
			}
			else
				cout << "Impossible move" << endl;
			}
		}  
