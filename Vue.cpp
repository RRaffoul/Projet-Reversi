#include "Vue.h"

Vue::Vue(){
}

Vue::~Vue(){}

void Vue::Print_board(int* plate){ //a modif, la vue ne doit recevoir que le plateau a print et c est le controleur qui fait la conversion
	cout << "  a b c d e f g h  " << endl;
    for(int i = 0; i < 8; i++){
        cout << i + 1;
        cout << " ";
	    for(int j = 0; j < 8; j++){
		    if(*(plate + (8*i) + j) == 0)
		    	cout << ". ";
		    else if(*(plate + (8*i) + j) == 1)
		    	cout << "X ";
		    else if(*(plate + (8*i) + j) == 2)
		    	cout << "O ";
	    }
        cout << i+1 << endl;
    }
	cout << "  a b c d e f g h  " << endl;
}

void Vue::Print_winner(int noirs, int blancs){
	/*cout << "\n \n \nFinal plate \n \n \n" << endl;
	print_board(Plate);*/ // A mettre ailleurs, dans le main
	cout << "Number of black pawns (O) : " << noirs << endl;
	cout << "Number of white pawns (X) : " << blancs << endl;
	if(noirs < blancs)
		cout << "White player wins !" << endl;
	else if(blancs < noirs)
		cout << "Black player wins !" << endl;
	else
		cout << "It's a draw." << endl;
}

void Vue::Print_state(int noirs, int blancs, int turn){
	cout << "Turn " << turn << endl;
	cout << "Number of black pawns (O) : " << noirs << endl;
	cout << "Number of white pawns (X) : " << blancs << endl;
}

void Vue::White_turn(){
	cout << "White player turn (X)" << endl;
}

void Vue::Black_turn(){
	cout << "Black player turn (O)" << endl;
}

void Vue::Ask_pos(){
	cout << "enter a position :";
}

void Vue::Skip_turn(){
	cout << "The player skips he's turn" << endl;
}

void Vue::Cant_skip(){
	cout << "A move is possible" << endl;
}

void Vue::Inv_entry_1(){
	cout << "Invalid entry, outside the plate" <<endl;
}

void Vue::Inv_entry_2(){
	cout << "Invalid entry, already played" <<endl;
}

void Vue::Inv_entry_3(){
	cout << "Invalid entry, more than 2 characters" <<endl;
}
void Vue::Inv_entry_4(){
	cout << "Invalid position, no play on this position" <<endl;
}