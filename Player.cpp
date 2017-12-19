#include "Player.h"


Player::Player(Plateau* platee, Vue* vuee){
		plate = platee;
		vue = vuee;
}

Player::~Player(){
	cout << "Destruction d'un Player" << endl;
}

string Player::Play(int turn, string last_move){
	//Voir ce qui est commun aux 2(3) types de player
}

bool Player::Check_input(string input){
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

///////////////////////// HUMANPLAYER ///////////////////////////////

HumanPlayer::HumanPlayer(Plateau* platee, Vue* vuee) : Player(platee, vuee){
	cout << "Creation d'un HumanPlayer" << endl;
}

HumanPlayer::~HumanPlayer(){
	cout << "Destruction d'un HumanPlayer" << endl;
}

string HumanPlayer::Play(int turn, string last_move){
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
	return input;
}

/*
bool HumanPlayer::Check_input(string input){
	//Player::Check_input(input);
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
}*/

///////////////////////// FILEPLAYER ///////////////////////////////
/*
 * Pour le moment le joueur de type fichier sera le joueur noir.
 * Donc le programme doit ECRIRE dans un fichier blanc.txt les mvts
 * du joueur blanc et doit LIRE dans un fichier noir.txt, ou le joueur 
 * noir écrira (via un autre terminal) ses mouvements.
 */

FilePlayer::FilePlayer(Plateau* platee, Vue* vuee, string player_name): Player(platee, vuee){
	name = player_name; //Get and Set name à faire ?
	string dir_name = init();
	string names[2];
	if(player_name == "blanc"){ // voir Precision_Joueur_Fichier.md si incompréhension
		names[0] = "noir";
		names[1] = "blanc";
	}
	else{
		names[0] = "blanc";
		names[1] = "noir";
	}
	string nom_fichier_ecr = dir_name+names[0]+".txt";
	string nom_fichier_lect = dir_name+names[1]+".txt";
	fichier_ecr.open(nom_fichier_ecr, fstream::in | fstream::out | fstream::trunc);
	fichier_lect.open(nom_fichier_lect, fstream::in | fstream::out | fstream::trunc); 	/* 	idéalement ce fichier devrait être ouvert en
																						*	écriture uniquement mais pour cela il faut
																						* 	que le fichie blanc/noir.txt existe déjà
																						* 	dans le bon répertoire
																						*/
										
	while (!fichier_lect.is_open()){
			cout << "Attente du joueur "<< names[1] <<" (fichier "<< names[1] <<".txt indisponible)" << endl;
			// Ajout d'une temporisation avant de réessayer
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			fichier_lect.open(nom_fichier_lect);
	}
}

FilePlayer::~FilePlayer(){
	cout << "Destruction d'un FilePlayer" << endl;
}
void FilePlayer::explore(char * dir_name){
/*
 * Méthode permettant d'indiquer le contenu du répertoire pris en param.
 * Permet au joueur console de vérifier ou placer les fichiers.
 */ 
	DIR *dir; //pointer to open directory
	struct dirent *entry; //stuff inside the direct
	struct stat info; //information about each entry

 
	//1 open
	dir = opendir(dir_name);
	if (!dir) {
		cout << "Directory was not found \n";
		return;
	}

	//2read
	cout << "\nThis folder contains : \n" << endl;
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.'){
			string path = /*string(dir_name) +*/ string(entry->d_name);
			cout << "- " << path << endl;
			stat(path.c_str(), &info);
		}
	}
	
	//3close
	closedir(dir);
}

string FilePlayer::init(){
	//Permet à l'utilisateur de choisir ou placer les fichiers
	string pathname = "";
	string uresponse = "";
	string y = "y";
	while(uresponse != y){
		cout << "Where would you save the files ?" << endl;
		getline(cin, pathname);
		// EXAMPLE : /mnt/c/Users/Louis Vande Perre/Documents/Polytech/BA3(Biomed)/Informatique/Projet/test/
		explore((char*) pathname.c_str()); /* c_str converti un string 
											* en char* (type nécessaire
											*  à la bonne exécution de 
											* la fonction explore())
											*/
		cout << "Is it a good directory ? (y/n)" << endl;
		getline(cin, uresponse);
	}
	return pathname;
}

string FilePlayer::Play(int turn, string last_move){
	//Player::Play(turn);
	ok = false;
	//soit c est ici qu on print le plateau soit dans le main, pareil pour la ligne suivante avec les scores
	vue->Print_state(plate->Get_Noirs(), plate->Get_Blancs(), turn);
	saveLastMove(last_move);
	string input = "";
	while(!ok){
		vue->Ask_pos(name);
		input = getMove();
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
	return input;
	
	
}
/*
bool FilePlayer::Check_input(string input){
	Player::Check_input(input);
}*/


void FilePlayer::saveLastMove(string last_move){
	if( fichier_ecr.is_open()){
		fichier_ecr << last_move << endl;
		cout << "L'adversaire a joué : "<< last_move << endl;
	}
	else
		cout << "problem" <<endl;
}

string FilePlayer::getMove(){
	string move;
	while (!(getline(fichier_lect, move))){
		// Echec de la lecture - Effacement des flags d'erreur
		fichier_lect.clear();
		// Ajout d'une temporisation avant de réessayer
		//cout << "En attente du joueur fichier" <<endl; //impression non nécessaire, mais aide
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	return move;
}
