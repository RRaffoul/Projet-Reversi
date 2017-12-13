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

///////////////////////// HUMANPLAYER ///////////////////////////////

HumanPlayer::HumanPlayer(Plateau* platee, Vue* vuee) : Player(platee, vuee){
	cout << "Creation d'un HumanPlayer" << endl;
}

HumanPlayer::~HumanPlayer(){
	cout << "Destruction d'un HumanPlayer" << endl;
}

void HumanPlayer::Play(int turn){
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

///////////////////////// FILEPLAYER ///////////////////////////////
/*
 * Pour le moment le joueur de type fichier sera le joueur noir.
 * Donc le programme doit ECRIRE dans un fichier blanc.txt les mvts
 * du joueur blanc et doit LIRE dans un fichier noir.txt, ou le joueur 
 * noir écrira (via un autre terminal) ses mouvements.
 */

FilePlayer::FilePlayer(Plateau* platee, Vue* vuee): Player(platee, vuee){
	string dir_name = init();
	cout << "emplacement des fichiers : " << dir_name << endl;
	string nom_fichier_noir = dir_name+"noir.txt";
	string nom_fichier_blanc = dir_name+"blanc.txt";
	fichier_ecr.open(nom_fichier_noir);
	fichier_lect.open(nom_fichier_blanc);
	if(fichier_ecr.is_open())
		cout << "c'est la teuf en ecriture" << endl;
	if(fichier_lect.is_open())
		cout << "c'est la teuf en lecture" << endl;
	cout << "Creation d'un FilePlayer" << endl;
}

FilePlayer::~FilePlayer(){
	cout << "Destruction d'un FilePlayer" << endl;
}
/*
void FilePlayer::set_ofstream(ofstream fichier_noir){
	fichier_ecr = &fichier_noir;
}

void FilePlayer::set_ifstream(ifstream fichier_blanc){
	fichier_lect = &fichier_blanc;
}

ofstream FilePlayer::get_ofstream() const{
	return &fichier_ecr;
}

ifstream FilePlayer::get_ifstream() const{
	return &fichier_lect;
}
*/
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
			string path = string(dir_name) + string(entry->d_name);
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

void FilePlayer::Play(int turn){
	//Player::Play(turn);
	
	
}

bool FilePlayer::Check_input(string input){
	//Player::Check_input(input);
	cout << "ceci est la fct check_input de Fileplayer" << endl;
}
