#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void Plateau::print_board(int board[8][8]){
	cout << "  a b c d e f g h  " << endl;
    for(int i=0; i<8; i++){
        cout << i + 1;
        cout << " ";
	    for(int j=0; j<8; j++){
		    if(board [i][j]==0)
		    	cout << ". ";
		    else if(board[i][j]==1)
		    	cout << "X ";
		    else if(board[i][j]==2)
		    	cout << "O ";
	    }
        cout << i+1 << endl;
    }
	cout << "  a b c d e f g h  " << endl;
}

/*construceur du plateau, le 1 c'est les blancs (X) et le 2 c'est les noirs (O)*/

Plateau::Plateau(){
	for(int i = 0; i<8; i++){
		for (int j = 0, j < 8, j++){			
			if((i = 3 && j = 3) ||(i = 4 && j = 4))
				plateau[i][j] = 2;
			else if ((i = 4 && j = 3) || (i = 3 && j = 4))
				plateau[i][j] = 1;
			else
				plateau[i][j] = 0;
	}
}

bool Plateau::check_input(int x, int y){
    if(x>8 || x<0 || y>8 || y < 0){
        cout << "invalid position" <<endl;
        return false;
    }
    else if(plateau[x][y] != 0){
        cout << "invalid position" <<endl;
        return false;
    }
    else
        return true;
}

/*check si il y a un pion de la meme couleur plus loin dans cette direction, le 2e check pour manger quoi*/

bool check_direction(int x, int y, int direction[2], int turn){

    //if(position + direction >= 0 && position + direction < 63){
    //int dist = 2; //distance entre les 2 pions enserrant les autres
    int dx = direction[0];
    int dy = direction[1]; //donne la direction en X et en Y dans laquelle on cherche
		for(int dist = 2, dist < 8, dist++){
			if(((x + dist*dx) > 7) || ((x + dist*dx) <0) || ((y + dist*dy) > 7) || ((y + dist*dy) <0) || (plateau[x + dist*dx][y + dist*dy] == 0)) {
				//check si on sort pas du plateau ou si on arrive pas sur une case vide
				return false;
			}
			else if (plateau[x + dist*dx][y + dist*dy] = turn){
				return true;
			}
		} 
	return false; //idée : retourner direct le nombre dist pour connaitre le nombre de pions a changer et leur positions
}
