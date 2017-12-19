#include "Player.h"


Player::Player(Plateau* platee, Vue* vuee){
		plate = platee;
		vue = vuee;
}

Player::~Player(){
	cout << "Destruction d'un Player" << endl;
}

void Player::Play(int turn){
	//Voir ce qui est commun au 2(3) types de player
}

bool Player::Check_input(string input){
	//Voir ce qui est commun au 2(3) types de player
}

HumanPlayer::HumanPlayer(Plateau* platee, Vue* vuee) : Player(platee, vuee){
	cout << "Creation d'un HumanPlayer" << endl;
}

HumanPlayer::~HumanPlayer(){
	cout << "Destruction d'un HumanPlayer" << endl;
}

void HumanPlayer::Play(int turn){
	//Player::Play(turn);
	ok = false;
	//soit c est ici qu on print le plateau soit dans le main, pareil pour la ligne suivante avec les scores
	vue->Print_state(plate->Get_Noirs(), plate->Get_Blancs(), turn);
	string input = "";
	while(!ok){
		vue->Ask_pos();
		getline(cin, input);
			if(Check_input(input)){
				int y = input[0] - 'a';
				int x = input[1] - '1';
                plate->Set_Turn(turn);
				if(x ==('0'-'1') && y ==('0'-'a')){  //On ferait pas une fonction pour ce if ?
					if(plate->Check_notplay()){
						vue->Skip_turn();
						ok = true;
					}
					else {
						vue->Cant_skip();
						//ok = false;
					}
				}
				else if(plate->Check_eat(x,y)){
					plate->Eat();
					ok = true;
				}
                else
                    vue->Inv_entry_4();
		}
	}
}


bool HumanPlayer::Check_input(string input){
	Player::Check_input(input);
	if(input.length() == 2){
		int y = input[0] - 'a';
        int x = input[1] - '1';
        if(x ==('0'-'1') && y ==('0'-'a')){
			return true;
		}
        else if(x > 8 || x < 0 || y > 8 || y < 0){ //check si dans le plateau
		    vue->Inv_entry_1();
			return false;
		}
		else if(*(plate->Get_Plate() + 8 * x + y) != 0){ //check si deja un pion a cet endroit là
			vue->Inv_entry_2();
			return false;
		}
		else
			return true;
    }
	else {
		vue->Inv_entry_3();
		return false;
	}
}

IAPlayer::IAPlayer(Plateau* platee, Vue* vuee) : Player(platee, vuee){
	cout << "Creation d'un IAPlayer" << endl;
}

IAPlayer::~IAPlayer(){
	cout << "Destruction d'un IAPlayer" << endl;
}

void IAPlayer::Play(int turn){
	vue->Print_state(plate->Get_Noirs(), plate->Get_Blancs(), turn);
	plate->Set_Turn(turn);
    int count = 1;
    float value = 0;
    float temp = 0;
    int pos[2] ={};
    vector<int> pos_to_check = plate->Pos_Play(); 	// pos_to_check, contient toutes les positions ou le pion peut se placer
    for(int i = 0; i < pos_to_check.size(); i+=2){ 	// pos_to_check, de la forme (ax, ay, bx, by) on prend donc coord 2 par 2
        imaginaire = *plate; 						// copie du plateau que l'on va manipuler
        if(imaginaire.Check_eat(pos_to_check[i], pos_to_check[i+1])){
            imaginaire.Eat();
            imaginaire.Set_Turn(imaginaire.Get_Turn() + 1); // on rajoute un tour de jeu --> chgt de joueur
            cout << count << endl;
            temp = Heuristic(imaginaire ,plate->Get_Turn(),plate->Get_Turn()%2) +  A(imaginaire,count,plate->Get_Turn()%2);
            if( temp > value){
                value =temp;					// Cette condition permet de garder en mémoire le meilleur scénario
                pos[0] = pos_to_check[i];		// et a l'IA de jouer ce coup là
                pos[1] = pos_to_check[i+1];
            }
        }
    }
    if(pos_to_check[0] == 9 && pos_to_check[1] == 9){	// Dans ans le cas ou le vecteur pos_to_check est de taille nulle,
		vue->Skip_turn();								// la fonction Pos_Play() initialise ses 2 premières valeurs à 9
		plate->Not_play();								// ce qui est scénario ou l'IA doit passer son tour car rien à manger
	}
	else if(plate->Check_eat(pos[0],pos[1])){
			plate->Eat();
	}
}


float IAPlayer::A(Plateau board, int count, int realColor){	// Reprends le meme fonctionnement que la fonction Play
    float value = 0;										// on va partir du plateau imaginaire pour imaginer plusieurs
    float temp = 0;											// tours à l'avance, mais on est limité par count
    if(count <= 15){										// car l'IA ne peut répondre en plus de 20 secondes
        vector<int> pos_to_check = board.Pos_Play();
        for(int i = 0; i < pos_to_check.size(); i+=2){
            imaginaire = board;
            if(imaginaire.Check_eat(pos_to_check[i], pos_to_check[i+1])){
                imaginaire.Eat();
                imaginaire.Set_Turn(imaginaire.Get_Turn() + 1); //A chaque appel de A(...) on simule un tour de plus
                count++;
                temp = Heuristic(imaginaire, (count+realColor)-1, realColor) + A(imaginaire,count,realColor);
                if(temp>value){
                    value = temp; 	// Parmis les différentes pos à jouer pour les tours [count], on vérifie que
                }					// cela va nous rapporter. De cette manière on sait si la pos examinée dans Play()
            }						// place bien l'IA pour la suite
        }
    return value;
	}
}


float IAPlayer::Heuristic(Plateau board, int color, int realColor){ // realColor est la couleur du pion que l'IA incarne,
    float score; 													// color est la couleur de l'adversaire
    if(realColor == 0){ //blancs
        if(color%2 == 0){	//blancs		// Ces lignes permettent de prendre en compte,
            score = board.Get_Blancs();		// dans le choix de l'IA, le nombre de pions mangés.
        }
    
        else{ // noirs
            score = -board.Get_Noirs();
        }   
    }
    else{ // noirs
        if(color%2 == 0){ //blancs
            score = -board.Get_Blancs();
        }
    
        else{ //noirs
            score = board.Get_Noirs();
        } 
    }
    return score;
}

FilePlayer::FilePlayer(Plateau* platee, Vue* vuee) : Player(platee, vuee){
	cout << "Creation d'un FilePlayer" << endl;
}

FilePlayer::~FilePlayer(){
	cout << "Destruction d'un FilePlayer" << endl;
}
bool FilePlayer::Check_input(string input){
	Player::Check_input(input);
	cout << "ceci est la fct check_input de Fileplayer" << endl;
}

void FilePlayer::Play(int turn){
	Player::Play(turn);
	cout << "ceci est la fct play de Fileplayer" << endl;
}
