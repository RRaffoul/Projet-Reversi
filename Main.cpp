/*void Plateau::game(){
	while(!game_over()){
        print_board();
        player_turn();
    }
    print_winner();	
}*/ //Ca je sais pas ou il faudrait le mettre pour que ca soit O.O., peut etre a redefinir

/*bool Plateau::game_over(){
	if (passe == 2)
		return true;
	else if (noirs + blancs == 64)
		return true;
	return false;
}*/

void Plateau::player_turn(){
    turn++;
    string input = "";
    color = (turn + 1)%2 + 1;
    int x;
    int y;
    
    if(color == 1){
        cout << "White player turn (X)" << endl;       
    }    
    
    else{
	    cout << "Black player turn (O)" << endl;       
    }
    
    while(true){
		cout << "Turn " << turn << endl;
		cout << "Number of black pawns (O) : " << noirs << endl;
		cout << "Number of white pawns (X) : " << blancs << endl;
		cout << "enter a position :";
		getline(cin, input);
		if(input.length() == 2){               
                y = input[0] - 'a';
                x = input[1] - '1';
                if(input[0]=='0' && input[1]=='0'){
					if(check_notplay()){			
						passe ++;
						cout << "The player skips he's turn" << endl;
						break;
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
        else
            cout << "Invalid entry" << endl;
	}
}
