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

bool check_direction(int x, int y, int direction[2]){

    //if(position + direction >= 0 && position + direction < 63){
    //int dist = 2; //distance entre les 2 pions enserrant les autres
    int dx = direction[0];
    int dy = direction[1]; //donne la direction en X et en Y dans laquelle on cherche
    int color = (turn + 1)%2 + 1; //pour savoir si on est au tour du joueur 1 ou 2 sans avoir modulo d'un nombre paire = 0 mais = 2
		for(int dist = 2, dist < 8, dist++){
			if(((x + dist*dx) > 7) || ((x + dist*dx) <0) || ((y + dist*dy) > 7) || ((y + dist*dy) <0) || (plateau[x + dist*dx][y + dist*dy] == 0)) {
				//check si on sort pas du plateau ou si on arrive pas sur une case vide
				return false;
			}
			else if (plateau[x + dist*dx][y + dist*dy] = color){
				return true;
			}
		} 
	return false; //idée : retourner direct le nombre dist pour connaitre le nombre de pions a changer et leurs positions
}

int Plateau::check_eat(int x, int y){
	int color = (turn +1)%2 + 1;
	int count = 0;
	int direction[8][2]={0};
	for (int i = -1, i <=1, i++){
		for (int j = -1, j <= 1, j++){//je sais que ca checke aussi la position meme du pion mais bon ca evite qlq lignes de codes pour une bete test
			if (plateau[x + i][y + j] != 0 && plateau[x + i][y + j] != color){
				/* alors la soit on bosse avec des vectors --> taille dimensionnable, comme pour checker qu'une direction apres
				 * soit on bosse en tableau toujours avec d'office une taille de 8 fois 2 element pour avoir les 8 directions
				 * avec des 0 quand il ne faut pas checker par la */
				 direction[count][0] = i;
				 direction[count][1] = j;
			}
			count++;
		}
	}
	return direction;
}/*maintenant encore faire une fonction qui goupille celle ci et check_direction en utilisant cette derniere que si la rangée de la matrice direction est != {0,0}
