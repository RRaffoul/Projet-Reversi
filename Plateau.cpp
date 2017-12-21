#include "Plateau.h"

Plateau::Plateau(){
	/*
	 * Initialisation du plateau en plaçant les 4 pions de
	 * départ au centre du plateau
	 */
	int passe = 0;
	noirs = 0;
	blancs = 0;
	for(int i = 0; i<8; i++){
		for (int j = 0; j < 8; j++){
			if((i == 3 && j == 3) ||(i == 4 && j == 4)){
				plateau[i][j] = 1;
				blancs++;
			}
			else if ((i == 4 && j == 3) || (i == 3 && j == 4)){
				plateau[i][j] = 2;
				noirs++;
			}
			else
				plateau[i][j] = 0;
		}
	}
}

Plateau::~Plateau(){}

int* Plateau::Get_Plate(){
    return &(plateau[0][0]);
}

int Plateau::Get_Blancs(){
    return blancs;
}

int Plateau::Get_Noirs(){
    return noirs;
}



bool Plateau::Check_direction(int x, int y, int direction[2]){
	/*
	 * Prends en arguments la position du pion que l'on veut poser 
	 * ainsi qu'une direction, donnée sous la forme d'un tuple (1x,1y) 
	 * Cette méthode vérifie la quantité de pions que l'on peut capturer 
	 * dans la direction donnée, tout en ajoutant ces pions 
	 * à une liste de pions à manger.
	 */
    int dx = direction[0];
    int dy = direction[1]; 	//Donne la direction en X et en Y dans laquelle on cherche.
    color = turn % 2 + 1; 	//Pour savoir si on est au tour du joueur 1 ou 2 sans 
							//avoir modulo d'un nombre paire = 0 mais = 2.
    for(int dist = 2; dist < 8; dist++){
		if(((x + dist*dx) > 7) || ((x + dist*dx) <0) || ((y + dist*dy) > 7) || ((y + dist*dy) <0) || (plateau[x + dist*dx][y + dist*dy] == 0)) {
			//check si on sort pas du plateau ou si on arrive pas sur une case vide
			return false;
		}
		else if (plateau[x + dist*dx][y + dist*dy] == color){ 
			/* Si effectivement il y a des pions a manger,
			 * on vient les mettre tous dans le vector d'un coup
			 * NB : le pion en (x,y) n'est pas ajouté ici */
			for (int i = 1; i < dist; i ++){
				pos_to_eat.push_back (x + i*dx);
				pos_to_eat.push_back (y + i*dy);
			}
			return true;
		}
	}
	return false;
}

bool Plateau::Check_eat(int x, int y){

	color = turn %2 + 1;
	int direction[2];
	bool eat = false;
	pos_to_eat.clear();
	for (int i = -1; i <=1; i++){
		if(x != 0 || i !=-1){ //Pour eviter qu'on ne sorte du plateau en regardant ce qu il y a derriere
			for (int j = -1; j <= 1; j++){//je sais que ca checke aussi la position meme du pion mais bon ca evite qlq lignes de codes pour une bete test
				if(y != 0 || j !=-1){		//RMQ: effacer le comm de la ligne supérieure ?
					if (plateau[x + i][y + j] != 0 && plateau[x + i][y + j] != color){
						direction [0]= i;
						direction [1]= j;
						if (Check_direction (x, y, direction)){
							passe = 0;
							eat = true; //le if c'est pour que si une fois true reste true tout en continuant de checker les autres directions
						}
					}
				}
			}
		}
	}
	if (eat){
		/* Si le pion mange effectivement un autre pion, il peut être placer 
		 * sur le damier, il est donc ajouter à pos_to_eat*/
		pos_to_eat.push_back (x);
		pos_to_eat.push_back (y);
	}
	return eat;
}

void Plateau::Eat(){
	/*
	 * Permet de manger les pions contenus dans le vecteur pos_to_eat.
	 */
	color = turn %2 + 1;
    for(int i =0; i < pos_to_eat.size() - 1;i += 2){
        plateau[pos_to_eat[i]][pos_to_eat[i + 1]] = color;
        if (color == 1){
			blancs++;
			if (i!=0){ 		//Empeche de compter le pions ajouté comme
				noirs--;	//un pion adverse mangé.
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

void Plateau::Set_Turn(int newTurn){
    turn = newTurn;
}

int Plateau::Get_Turn(){
    return turn;
}

bool Plateau::Game_over(){
	/*
	 * Vérifie si les conditions d'arrêt sont satisfaites ou non
	 */
	if (passe == 2) 
		return true; //Si les 2 joueurs ont passés leurs tours consécutivement
	else if (noirs + blancs == 64)
		return true; //Si toutes les cases du plateau sont occupées
	return false;
}

bool Plateau::Check_notplay(){
	/*
	 * Vérifie si le joueur peut en effet passer son tour
	 */
	for(int i=0; i<8; i++){
		for (int j = 0; j< 8; j++){
			if(plateau[i][j] == 0){
				if(Check_eat(i, j)){
					return false;
				}
			}
		}
	}
	passe ++;
	return true;
}

void Plateau::Not_play(){
	/*
	 * Version simplifiée du Check_notplay(), appelée par un IAPlayer 
	 * uniquement car ceux ci ont déjà verifier les coups possibles en
	 * entamant leur tour de jeu
	 */
	passe++;
}

vector<int> Plateau::Pos_Play(){
	/*
	 * Méthode appelée par un IAPlayer pour donner
	 * toutes les positions ou le pion peut se placer
	 */
    vector<int> posPlay;
    posPlay.clear();
	for(int i=0; i<8; i++){
		for (int j = 0; j< 8; j++){
			if(plateau[i][j] == 0){
				if(Check_eat(i, j)){
				    posPlay.push_back(i);
				    posPlay.push_back(j);
				}
			}
		}
	}
    if(posPlay.size() == 0){
        posPlay.push_back(9);
        posPlay.push_back(9);
    }
	return posPlay;
}


//Ca c est la 2e version de Check_eat qui ne fais pas les push backs et autres choses useless pour la mobilité
bool Plateau::Playable(int x, int y){
	color = turn % 2 + 1;
	int direction[2];
	bool eat = false;
	for (int i = -1; i <=1; i++){
		if(x != 0 || i !=-1){ //Pour eviter qu'on ne sorte du plateau en regardant ce qu il y a derriere
			for (int j = -1; j <= 1; j++){
				if(y != 0 || j !=-1){
					if (plateau[x + i][y + j] != 0 && plateau[x + i][y + j] != color){
						direction [0]= i;
						direction [1]= j;
						if (Check_direction2 (x, y, direction)){ 
							return eat = true;
						}
					}
				}
			}
		}
	}
	return eat;
}

//C est la 2e version de Check_direction qui ne fais pas de push back et autres trucs inutiles pour la mobilité
bool Plateau::Check_direction2(int x, int y, int direction[2]){
    int dx = direction[0];
    int dy = direction[1]; //donne la direction en X et en Y dans laquelle on cherche
    color = turn % 2 + 1;
    for(int dist = 2; dist < 8; dist++){
		if(((x + dist*dx) > 7) || ((x + dist*dx) <0) || ((y + dist*dy) > 7) || ((y + dist*dy) <0) || (plateau[x + dist*dx][y + dist*dy] == 0)) {
			//check si on sort pas du plateau ou si on arrive pas sur une case vide
			return false;
		}
		else if (plateau[x + dist*dx][y + dist*dy] == color){
			return true;
		}
	}
	return false;
}

//C est la 3e version de Check_direction qui ne fais pas de push back et autres trucs inutiles pour la mobilité
bool Plateau::Check_Direction3(int x, int y, int dx, int dy){
    color = turn % 2 + 1;
    for(int dist = 1; dist < 8; dist++){
		if((((x + dist*dx) > 7) || ((x + dist*dx) <0) || ((y + dist*dy) > 7) || ((y + dist*dy) <0)) && (plateau[x + dist*dx][y + dist*dy] == color)) {
			//check si on sort pas du plateau ou si on arrive pas sur une case vide
			return true;
		}
		else if (plateau[x + dist*dx][y + dist*dy] != color){
			return false;
		}
	}
	return false;
}

///////////////////////////////Partie sur l'heuristique////////////////////////////////////
/*
 * Dans cette partie sont regroupées toutes les fonctions qui influence le "choix" de l'IA.
 * Plusieurs paramètres sont pris en compte et leur poids dans le choix final est modulée
 * par un coéfficent.
 */

int Plateau::Corner(){ //ATTENTION c est une valeur par defaut a 0, on peut appeler la fonction initialement avec Corner() (= Corner(0))
	int myColor = turn % 2 + 1; 
	int advColor = color % 2 + 1; //couleur de l adversaire, + simple que de la recalculer dans chaque if
	int moi= 0;
	/*
	 * Ici j ai simplifié et on mets tous les pions tout a fait stables dans le meme sac, sans distinction
	 */
	int adv = 0;
	int hauteur = 0; //Pour que si on a les 2 cotés couvers en prolongement du coins s il nous appartient, pour eventuellement reiterer dans le coin interieur a ce coin
	int largeur = 0;
	if(plateau[0][0] != 0){ //meilleur moyen de construire les if en faisant le moins de checks possibles
		if(plateau[0][0] == myColor){
			moi++;
			for(int k = 1; k <= 6; k++){ //la on va regarder si plus loin il y a d'autres pions qui prolongent et sont donc stables
				if(plateau[k][0] == myColor){ //et tant pis pour les repetitions entre coins, si on a des repet c est qu on a joint 2 coins, d autant + stable
					moi++;
					hauteur++;
				} 
				else break;
			}
			for(int k = 1; k <= 6; k++){ //same same dans la 2 e direct
				if(plateau[0][k] == myColor){ 
					moi++;
					largeur++;
				}
				else break;
			}
			if(largeur != 0 && hauteur != 0){
				moi += Corner1(1, largeur, hauteur, myColor);
			}			
			largeur = 0;
			hauteur = 0;
		}
		else{
			adv++;
			for(int k = 1; k <= 6; k++){ 
				if(plateau[k][0] == advColor){ 
					adv++; 
				}
				else break;
			}
			for(int k = 0; k <= 6; k++){ 
				if(plateau[0][k] == advColor){ 
					adv++;
				} 
				else break;
			}
			if(largeur != 0 && hauteur != 0){
				adv += Corner1(1, largeur, hauteur, advColor);
			}
			largeur = 0;
			hauteur = 0;
		}
	}
	if(plateau[0][7] != 0){
		if(plateau[0][7] == myColor){
			moi++;
			for(int k = 1; k <= 6; k++){
				if(plateau[k][7] == myColor){
					moi++;
					hauteur++;
				} 
				else break;
			}
			for(int k = 6; k >= 1; k--){
				if(plateau[0][k] == myColor){ 
					moi++; 
					largeur++;
				}
				else break;
			}
			if(largeur != 0 && hauteur != 0){
				moi += Corner2(1, largeur, hauteur, myColor);	
			}
			largeur = 0;
			hauteur = 0;
		}
		else{
			adv++;
			for(int k = 1; k <= 6; k++){ 
				if(plateau[k][7] == advColor){ 
					adv++; 
					hauteur++;
				}
				else break;
			}
			for(int k = 6; k >= 1; k--){ 
				if(plateau[0][k] == advColor){ 
					adv++;
					largeur++;
				} 
				else break;
			}
			if(largeur != 0 && hauteur != 0){
				adv += Corner2(1, largeur, hauteur, advColor);
			}						
			largeur = 0;
			hauteur = 0;
		}
	}
	if(plateau[7][7] != 0){
		if(plateau[7][7] == myColor){
			moi++;
			for(int k = 6; k >= 1; k--){ 
				if(plateau[k][7] == myColor){
					moi++;
					hauteur++;
				} 
				else break;
			}
			for(int k = 6; k >= 1; k--){ 
				if(plateau[7][k] == myColor){ 
					moi++;
					largeur++; 
				}
				else break;
			}
			if(largeur != 0 && hauteur != 0){
				moi += Corner2(1, largeur, hauteur, myColor);
			}
			largeur = 0;
			hauteur = 0;
		}
		else{
			adv++;
			for(int k = 6; k >= 1; k--){ 
				if(plateau[k][7] == advColor){ 
					adv++; 
					hauteur++;
				}
				else break;
			}
			for(int k = 6; k >= 1; k--){ 
				if(plateau[7][k] == advColor){ 
					adv++;
					largeur++;
				} 
				else break;
			}
			if(largeur != 0 && hauteur != 0){
				adv += Corner2(1, largeur, hauteur, advColor);
			}						
			largeur = 0;
			hauteur = 0;
		}
	}
	if(plateau[7][0] != 0){
		if(plateau[7][0] == myColor){
			moi++;
			for(int k = 6; k >= 1; k--){ 
				if(plateau[k][0] == myColor){ 
					moi++;
					hauteur++;
				} 
				else break;
			}
			for(int k = 1; k <= 6; k++){ 
				if(plateau[7][k] == myColor){ 
					moi++;
					largeur++; 
				}
				else break;
			}
			if(largeur != 0 && hauteur != 0){
				moi += Corner2(1, largeur, hauteur, myColor);
			}
			largeur = 0;
			hauteur = 0;
		}
		else{
			adv++;
			for(int k = 6; k >= 1; k--){ 
				if(plateau[k][0] == advColor){ 
					adv++; 
					hauteur++;
				}
				else break;
			}
			for(int k = 1; k <= 6; k++){ 
				if(plateau[7][k] == advColor){ 
					adv++;
					largeur++;
				} 
				else break;
			}
			if(largeur != 0 && hauteur != 0){
				adv += Corner2(1, largeur, hauteur, advColor);
			}						
			largeur = 0;
			hauteur = 0;
		}
	}
	return 50*(moi - adv); //RMQ : Coef a modif
}

//"it" iteration
//coin haut gauche
int Plateau::Corner1(int it, int larg, int haut, int Color){ //corner1 c est le coté en haut a gauche, 2 cest en haut a droite, 3 en bas a droite et 4 en bas a gauche
	int moi = 0;
	int hauteur = 0; 
	int largeur = 0;
	if(plateau[it][it] != 0){
		if(plateau[it][it] == Color){
			moi++;
			for(int k = it+1; k <= it+haut; k++){ //la on va regarder si plus loin il y a d'autres pions qui prolongent et sont donc stables
				if(plateau[k][it] == Color){ 
					moi++;
					hauteur++;
				} 
				else break;
			}
			for(int k = it+1; k <= it+larg; k++){
				if(plateau[it][k] == Color){ 
					moi++;
					largeur++;
				}
				else break;
			}
			if(largeur != 0 && hauteur != 0){
				int iteration = it + 1;
				moi += Corner1(iteration, largeur, hauteur, Color);
			}
		}
	}
	return moi;
}

//coin haut droit
int Plateau::Corner2(int it, int larg, int haut, int Color){ 
	int moi = 0; 
	int hauteur = 0; 
	int largeur = 0;
	if(plateau[it][7-it] != 0){ 
		if(plateau[it][7-it] == Color){
			moi++;
			for(int k = it+1; k <= it+haut; k++){ 
				if(plateau[k][7-it] == Color){ 
					moi++;
					hauteur++;
				} 
				else break;
			}
			for(int k = 6-it; k >= 6-it-larg; k--){ //on part d en haut a droite et on va regarder sur la meme rangée ce qu il se passe a gauche
				if(plateau[it][k] == Color){ 
					moi++;
					largeur++;
				}
				else break;
			}
			if(largeur != 0 && hauteur != 0){
				int iteration = it + 1;
				moi += Corner2(iteration, largeur, hauteur, Color);
			}
		}
	}
	return moi;
}

//coin bas droit
int Plateau::Corner3(int it, int larg, int haut, int Color){
	int moi = 0;
	int hauteur = 0; 
	int largeur = 0;
	if(plateau[7-it][7-it] != 0){ 
		if(plateau[7-it][7-it] == Color){
			moi++;
			for(int k = 6-it; k >= 6-it-haut; k--){ 
				if(plateau[k][7-it] == Color){ 
					moi++;
					hauteur++;
				} 
				else break;
			}
			for(int k = 6-it; k >= 6-it-larg; k--){
				if(plateau[7-it][k] == Color){ 
					moi++;
					largeur++;
				}
				else break;
			}
			if(largeur != 0 && hauteur != 0){
				int iteration = it + 1;
				moi += Corner3(iteration, largeur, hauteur, Color);
			}
		}
	}
	return moi;
}


//coin bas gauche
int Plateau::Corner4(int it, int larg, int haut, int Color){
	int moi = 0;
	int hauteur = 0; 
	int largeur = 0;
	if(plateau[7-it][it] != 0){ 
		if(plateau[7-it][it] == Color){
			moi++;
			for(int k = 6-it; k >= 6-it-haut; k--){
				if(plateau[k][it] == Color){ 
					moi++;
					hauteur++;
				} 
				else break;
			}
			for(int k = it+1; k <= it+larg; k++){
				if(plateau[it][k] == Color){ 
					moi++;
					largeur++;
				}
				else break;
			}
			if(largeur != 0 && hauteur != 0){
				int iteration = it + 1;
				moi += Corner4(iteration, largeur, hauteur, Color);
			}
		}
	}
	return moi;
}

//Check la mobilité = nombres de choix de cases dans lequelles on peut jouer
int Plateau::Mobility(){
	int mob = 0;
	for(int i=0; i<8; i++){
		for (int j = 0; j< 8; j++){
			if(plateau[i][j] == 0){
				if(Playable(i, j)){
				    mob++;
				}
			}
		}
	}
	return 20*(20-mob);
}

//Check la stabilité = nombres de pions qui ne peuvent plus être mangés
int Plateau::Stability(int color){
    int stab = 0;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(plateau[i][j] == color){
                if(Check_Stability(i,j)){
                    stab++;
                }
            }
        }
    }
    return 30*stab;
}

bool Plateau::Check_Stability(int x, int y){
	color = turn % 2 + 1;
	bool stable = false;
    if(Check_Direction3(x,y,1,-1) || Check_Direction3(x,y,-1,1)){
        stable = true;
    }
    if(Check_Direction3(x,y,1,0) || Check_Direction3(x,y,-1,0)){
        stable = true;
    }
    if(Check_Direction3(x,y,1,1) || Check_Direction3(x,y,-1,-1)){
        stable = true;
    }
    if(Check_Direction3(x,y,0,-1) || Check_Direction3(x,y,0,1)){
        stable = true;
    }
	return stable;
}
