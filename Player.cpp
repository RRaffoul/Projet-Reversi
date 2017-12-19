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
    vector<int> pos_to_check = plate->Pos_Play();
    for(int i = 0; i < pos_to_check.size(); i+=2){
        imaginaire = *plate;
        if(imaginaire.Check_eat(pos_to_check[i], pos_to_check[i+1])){
            imaginaire.Eat();
            imaginaire.Set_Turn(imaginaire.Get_Turn() + 1);
            temp = Heuristic(imaginaire ,plate->Get_Turn(),plate->Get_Turn()%2) +  A(imaginaire,count,plate->Get_Turn()%2);
            if( temp > value){
                value =temp;
                pos[0] = pos_to_check[i];
                pos[1] = pos_to_check[i+1];
            }
        }
    }
    if(pos_to_check[0] == 9 && pos_to_check[1] == 9){
		vue->Skip_turn();
		plate->Not_play();
	}
	else if(plate->Check_eat(pos[0],pos[1])){
			plate->Eat();
	}
}


float IAPlayer::A(Plateau board, int count, int realColor){
    float value = 0;
    float temp = 0;
    if(count <= 15){
        vector<int> pos_to_check = board.Pos_Play();
        for(int i = 0; i < pos_to_check.size(); i+=2){
            imaginaire = board;
            if(imaginaire.Check_eat(pos_to_check[i], pos_to_check[i+1])){
                imaginaire.Eat();
                imaginaire.Set_Turn(imaginaire.Get_Turn() + 1);
                count++;
                temp = Heuristic(imaginaire, (count+realColor)-1, realColor) + A(imaginaire,count,realColor);
                if(temp>value){
                    value = temp;
                }
            }
        }
    return value;
	}
}

float IAPlayer::Heuristic(Plateau board, int color, int realColor){
    float score; 
    if(realColor == 0){
        if(color%2 == 0){
            score = board.Get_Blancs();
        }
    
        else{
            score = -board.Get_Noirs();
        }   
    }
    else{
        if(color%2 == 0){
            score = -board.Get_Blancs();
        }
    
        else{
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
