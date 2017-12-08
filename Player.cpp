void Player::Turn(){
	view->print_state(Plate);
	view->ask_pos(Plate);
	getline(cin, input);
		if(check_input(input)){
			y = input[0] - 'a';
			x = input[1] - '1';
			if(check_eat(x,y)){
						passe = 0;
                        eat();
                        break;
					}
                    else
                        cout << "Impossible move" << endl;
				}
		}          
        else
            cout << "Invalid entry" << endl;
	}


bool Player::check_input(string input){
	if(input.length() == 2){               
		y = input[0] - 'a';
        x = input[1] - '1';
        if(input[0]=='0' && input[1]=='0'){
			if(Plate->check_notplay()){			
				passe ++;
				view->Skip_turn();
				return true;
			}
		}
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
