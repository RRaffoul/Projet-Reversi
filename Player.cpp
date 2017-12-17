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
			cout<< "lol" << endl;
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
	pos = Search_func(*plate);
	if(pos[0] == 0 && pos [1] == 0){
		vue->Skip_turn();
	}
	else if(plate->Check_eat(pos[0],pos[1])){
		plate->Eat();
	}
}




int* IAPlayer::A(Plateau board){
	int* best;
    int* futur;	
	if(count <= 5){ //si on s arrete a 4 (pair) ca n a pas de sens, on s arreterait sur un coup d un adversaire, pas sur un a toi
		if (count % 2 == 0){ /*donc c est au tour de l adversaire, ca compte pas ses point mais on pourrait proceder par malus 
			exactement de la meme facon en negatif ou des bonus si l adversaire passe son tour ahah !*/
			imaginaire = board;
			pos_to_check = imaginaire.Pos_Play(); //jsp si ca s ecrti vector1 = vector2 
			int a = pos_to_check.size(); //pas mieux de faire ca plutot que de le mettre dans le if comme dans plateau ? Doit compter moins de fois tout non ?
			for (int i = 0; i < a; i+=2){  //on remarque que si a = 0 on a un retour de 00 pour le choix de position
				imaginaire = board;
				if(imaginaire.Check_eat(pos_to_check[i], pos_to_check[i+1])){//a regler ca hein
					imaginaire.Eat();
				}
				futur = A(imaginaire);
				best[0] = futur[0];  //ici on devrait remettre valeur etc pour rajouter des points negatifs
			}
		}
		else{ //donc c est a nous
			imaginaire = board;
			pos_to_check = imaginaire.Pos_Play(); //jsp si ca s ecrti vector1 = vector2 
			int a = pos_to_check.size(); //pas mieux de faire ca plutot que de le mettre dans le if comme dans plateau ? Doit compter moins de fois tout non ?
			for (int i = 0; i < a; i+=2){
				imaginaire = board;
				if(imaginaire.Check_eat(pos_to_check[i], pos_to_check[i+1])){//a regler ca hein
					imaginaire.Eat();
				}
				futur = A(imaginaire);
				int valeur = imaginaire.Get_Blancs() + futur[0]; //on doit optimiser le premier membre de cette somme
				if (best[0] < valeur){
					best[0] = valeur;
					best[1] = pos_to_check[i];
					best[2] = pos_to_check[i+1];
				}
			}
		}
		count++;
	}
	return best;
}

int* IAPlayer::Search_func(Plateau board){
	count = 1; //si on veut mettre = 0, modifier dans l autre fonction dans le if <= devient < 
	int* direction = A(board);
	int* objectif;
	objectif [0] = direction [1];
	objectif [1] = direction [2];
	return objectif;
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
