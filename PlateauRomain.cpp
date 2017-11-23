#include "PlateauRomain.h"

Plateau::Plateau(){
	for(int i = 0; i<8; i++){
		for (int j = 0; j < 8; j++){			
			if((i == 3 && j == 3) ||(i == 4 && j == 4))
				plateau[i][j] = 2;
			else if ((i == 4 && j == 3) || (i == 3 && j == 4))
				plateau[i][j] = 1;
			else
				plateau[i][j] = 0;
		}
	}
}

void Plateau::print_board(){
	cout << "  a b c d e f g h  " << endl;
    for(int i=0; i<8; i++){
        cout << i + 1;
        cout << " ";
	    for(int j=0; j < 8; j++){
		    if(plateau [i][j] == 0)
		    	cout << ". ";
		    else if(plateau[i][j] == 1)
		    	cout << "X ";
		    else if(plateau[i][j] == 2)
		    	cout << "O ";
	    }
        cout << i+1 << endl;
    }
	cout << "  a b c d e f g h  " << endl;
}

/*construceur du plateau, le 1 c'est les blancs (X) et le 2 c'est les noirs (O)*/


bool Plateau::check_input(int x, int y){
    if(x > 8 || x < 0 || y > 8 || y < 0){
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

bool Plateau::check_direction(int x, int y, int direction[2]){
	
	//int dist = 2; //distance entre les 2 pions enserrant les autres
    int dx = direction[0];
    int dy = direction[1]; //donne la direction en X et en Y dans laquelle on cherche
    color = (turn + 1)%2 + 1; //pour savoir si on est au tour du joueur 1 ou 2 sans avoir modulo d'un nombre paire = 0 mais = 2
    
    for(int dist = 2, dist < 8, dist++){
		if(((x + dist*dx) > 7) || ((x + dist*dx) <0) || ((y + dist*dy) > 7) || ((y + dist*dy) <0) || (plateau[x + dist*dx][y + dist*dy] == 0)) {
			//check si on sort pas du plateau ou si on arrive pas sur une case vide
			return false;
		}
		else if (plateau[x + dist*dx][y + dist*dy] == color){ /*si effectivement il y a des pons a manger,
																on vient ls mettres tous dans le vector d un coup */
			for (i = 1; i < dist; i ++){
				pos_to_eat.push_back (x + i*dx);
				pos_to_eat.push_back (y + i*dy);
			}
			return true;
		}
	} 
	return false;
}


bool Plateau::check_eat(int x, int y){
	color = (turn +1)%2 + 1;
	int count = 0;
	int direction = [2];
	bool eat = false;
	//int direction[8][2]={0};    Devenu useless si on combien les fcts check_eat et check_direction
	for (int i = -1; i <=1; i++){
		for (int j = -1; j <= 1; j++){//je sais que ca checke aussi la position meme du pion mais bon ca evite qlq lignes de codes pour une bete test
			if (plateau[x + i][y + j] != 0 && plateau[x + i][y + j] != color){
				/* alors la soit on bosse avec des vectors --> taille dimensionnable, comme pour checker qu'une direction apres
				 * soit on bosse en tableau toujours avec d'office une taille de 8 fois 2 element pour avoir les 8 directions
				 * avec des 0 quand il ne faut pas checker par la */
				direction = {i, j};
				if (check_direction (x, y, direction)){
					eat = true; //le if c'est pour que si une fois true reste true tout en continuant de cheker les autres directions
				}
				 /*direction[count][0] = i;
				 direction[count][1] = j;  //Devenu useless */
			}
		}
	}
	/*
	if (count == 0){
		direction[0][0] = 5; /*le marqueur en question, on pourrait eventuellement commencer a le deplacer pour faire lire des moities de tableau etc */
	}  // devenu useless */
	return eat;
}/*maintenant encore faire une fonction qui goupille celle ci et check_direction en utilisant cette derniere 
 que si la rangée de la matrice direction est != {0,0}*/
 
void Plateau::eat(){
	color = (turn + 1)%2 + 1;
    for(int i =0; i<(pos_to_eat.size()/2);i += 2){
        plateau[pos_to_eat[i]][pos_to_eat[i + 1]] = color;
    }
}

bool Plateau::check_notplay(int* board, int turn){
/*
 * Vérifie si le joueur peut en effet passer son tour
 */
	bool r = true;
	for(int i=0; i<8; i++){
		for (int j = 0; j< 8; j++){
			if(plateau[i][j] == 0){
				if(check_eat(i, j)){
					cout << "Un mouvement est possible" << endl;
					r = false;
					return r;
				}
			}
		}
	}
	return r;
}
 
void Plateau::player_turn(){
    turn++;
    string input = "";
    color = (turn + 1)%2 + 1;
    
    if(color == 1){
        cout << "White player turn" << endl;       
    }    
    
    else{
	    cout << "Black player turn" << endl;       
    }
    
    while(true){
		cout << "enter a position :";
		getline(cin, input);
		if(input.length() == 2){               
                y = input[0] - 'a';
                x = input[1] - '1';
                if((x +'1')=='0' && (y +'a')=='0'){ //Pq pas mettre input [0] et [1] au lieu des x + 'l' etc ?
					if(check_notplay()){
						cout << "Le joueur passe son tour" << endl;
						break;
					}
				}
                else if(check_input(x,y)){
					pos_to_eat.clear();					
                    if(check_eat(x - 1, y - 1)){
                        eat();
                        break;
					}
                    else
                        cout << "mouvement impossible" << endl;	// ne doit pas s'imprimer lorsque le joueur tente, et échoue, de passer son tour
				}
		}          
        else
            cout << "Entrée invalide" << endl;
	}
}


int main(int argc, char *argv[]){	

    Plateau* Plate() = new Plateau();
	Plate.print_board();
    while(true){
        player_turn();
        Plate.print_board();
    }
	return 0;

}
