void View::print_board(Plateau& Plate) const{ //a modif, la vue ne doit recevoir que le plateau a print et c est le controleur qui fait la conversion
	cout << "  a b c d e f g h  " << endl;
    for(int i = 0; i < 8; i++){
        cout << i + 1;
        cout << " ";
	    for(int j = 0; j < 8; j++){
		    if(Plate [i][j] == 0)
		    	cout << ". ";
		    else if(Plate[i][j] == 1)
		    	cout << "X ";
		    else if(Plate[i][j] == 2)
		    	cout << "O ";
	    }
        cout << i+1 << endl;
    }
	cout << "  a b c d e f g h  " << endl;
}

void View::print_winner(Plateau& Plate) const{
	/*cout << "\n \n \nFinal plate \n \n \n" << endl;
	print_board(Plate);*/ // A mettre ailleurs, dans le main
	int noirs = Plate->get_noirs();
	int blancs = Plate->get_blancs();
	cout << "Number of black pawns (O) : " << noirs << endl;
	cout << "Number of white pawns (X) : " << blancs << endl;
	if(noirs < blancs)
		cout << "White player wins !" << endl;
	else if(blancs < noirs)
		cout << "Black player wins !" << endl;
	else
		cout << "It's a draw." << endl;
}

void View::print_state(Plateau& Plate) const{
	int noirs = Plate->get_noirs();
	int blancs = Plate->get_blancs();
	cout << "Turn " << turn << endl;
	cout << "Number of black pawns (O) : " << noirs << endl;
	cout << "Number of white pawns (X) : " << blancs << endl;
}

void View::ask_pos(){
	cout << "enter a position :";
}

void View::Skip_turn(){
	cout << "The player skips he's turn" << endl;
}

void View::Cant_skip(){
	cout << "A move is possible" << endl;
}

void View::Inv_entry_1(){
	cout << "Invalid entry, outside the plate" <<endl;
}

void View::Inv_entry_2(){
	cout << "Invalid entry, already played" <<endl;
}

void View::Inv_entry_1(){
	cout << "Invalid entry, more than 2 characters" <<endl;
}
