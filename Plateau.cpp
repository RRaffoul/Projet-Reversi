#include "Plateau.h"

Plateau::Plateau(View view){
	vue = view;
	int turn = 0;
	int passe = 0;
	noirs = 0;
	blancs = 0;
	for(int i = 0; i<8; i++){
		for (int j = 0; j < 8; j++){	
			if((i == 3 && j == 3) ||(i == 4 && j == 4)){
				plateau[i][j] = 2;
				noirs++;
			}
			else if ((i == 4 && j == 3) || (i == 3 && j == 4)){
				plateau[i][j] = 1;
				blancs++;
			}
			else
				plateau[i][j] = 0;
		}
	}
}

Plateau::~Plateau(){}
	

int Plateau::Get_noirs(){
	return noirs;
}

int Plateau::Get_blancs(){
	return blancs;
}


/*check si il y a un pion de la meme couleur plus loin dans cette direction, le 2e check pour manger quoi*/

bool Plateau::Check_direction(int x, int y, int direction[2]){
    int dx = direction[0];
    int dy = direction[1]; //donne la direction en X et en Y dans laquelle on cherche
    color = (turn + 1)%2 + 1; //pour savoir si on est au tour du joueur 1 ou 2 sans avoir modulo d'un nombre paire = 0 mais = 2
    
    for(int dist = 2; dist < 8; dist++){
		if(((x + dist*dx) > 7) || ((x + dist*dx) <0) || ((y + dist*dy) > 7) || ((y + dist*dy) <0) || (plateau[x + dist*dx][y + dist*dy] == 0)) {
			//check si on sort pas du plateau ou si on arrive pas sur une case vide
			return false;
		}
		else if (plateau[x + dist*dx][y + dist*dy] == color){ /*si effectivement il y a des pions a manger,
																on vient les mettre tous dans le vector d un coup */
			for (int i = 1; i < dist; i ++){
				pos_to_eat.push_back (x + i*dx);
				pos_to_eat.push_back (y + i*dy);
			}
			return true;
		}
	} 
	return false;
}

bool Plateau::Check_eat(int x, int y){//corriger cette fct sinon il y aura une erreur dans les coins et sur les bords quand x + 1 <0 par ex
	color = (turn +1)%2 + 1;
	int count = 0;
	int direction[2];
	bool eat = false;
	pos_to_eat.clear();
	//int direction[8][2]={0};    Devenu useless si on combien les fcts check_eat et check_direction
	for (int i = -1; i <=1; i++){
		if(x != 0 || i !=-1){ //Pour eviter qu'on ne sorte du plateau en regardant ce qu il y a derriere
			for (int j = -1; j <= 1; j++){//je sais que ca checke aussi la position meme du pion mais bon ca evite qlq lignes de codes pour une bete test
				if(y != 0 || j !=-1){
					if (plateau[x + i][y + j] != 0 && plateau[x + i][y + j] != color){
						/* alors la soit on bosse avec des vectors --> taille dimensionnable, comme pour checker qu'une direction apres
						* soit on bosse en tableau toujours avec d'office une taille de 8 fois 2 element pour avoir les 8 directions
						* avec des 0 quand il ne faut pas checker par la */
						direction [0]= i;
						direction [1]= j; //trouver un moyen d ecrire " direction = {i, j}; "
						if (Check_direction (x, y, direction)){
							passe = 0;
							eat = true; //le if c'est pour que si une fois true reste true tout en continuant de cheker les autres directions
						}
						/*direction[count][0] = i;
						direction[count][1] = j;  //Devenu useless */
					}
				}
			}
		}
	}
	if (eat){
		pos_to_eat.push_back (x);
		pos_to_eat.push_back (y);
	}
	/*
	if (count == 0){
		direction[0][0] = 5; /*le marqueur en question, on pourrait eventuellement commencer a le deplacer pour faire lire des moities de tableau etc
	}  // devenu useless */
	return eat;
}/*maintenant encore faire une fonction qui goupille celle ci et check_direction en utilisant cette derniere 
 que si la rangée de la matrice direction est != {0,0}*/
 
void Plateau::Eat(){
	color = (turn + 1)%2 + 1;
    for(int i =0; i < pos_to_eat.size() - 1;i += 2){
        plateau[pos_to_eat[i]][pos_to_eat[i + 1]] = color;
        if (color == 1){
			blancs++;
			if (i!=0){ //sinon va compter qu on mange un de trop chaque fois vu qu'ajoute aussi le pion qu'on a ajouté
				noirs--;
			}
		}
		else if (color == 2){
			noirs++;
			if (i!=0){
				blancs--;
			}
		}
    }
}

bool Plateau::game_over(){
	if (passe == 2)
		return true;
	else if (noirs + blancs == 64)
		return true;
	return false;
}

bool Plateau::Check_notplay(){
/*
 * Vérifie si le joueur peut en effet passer son tour
 */
	bool r = true;
	for(int i=0; i<8; i++){
		for (int j = 0; j< 8; j++){
			if(plateau[i][j] == 0){
				if(check_eat(i, j)){
					r = false;
					return r;
				}
			}
		}
	}
	passe ++;
	return r;
}
