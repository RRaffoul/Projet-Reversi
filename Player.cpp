#include "Player.h"


Player::Player(Plateau* platee, Vue* vuee){
		plate = platee;
		vue = vuee;
}

Player::~Player(){
	cout << "Destruction d'un Player" << endl; //RMQ: Ca devrait théoriquement être dans la vue, est-ce vrmt mieux ?
}

string Player::Play(int turn){
	//Voir ce qui est commun aux 2(3) types de player
}

bool Player::Check_input(string input){ //méthode commune aux 3 types d'objets enfants
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

void Player::saveMove(string last_move){
}

bool Player::confirmation(){
	return true;
}

///////////////////////// HUMANPLAYER ///////////////////////////////

HumanPlayer::HumanPlayer(Plateau* platee, Vue* vuee) : Player(platee, vuee){
	cout << "Creation d'un HumanPlayer" << endl; //RMQ: Ca devrait théoriquement être dans la vue, est-ce vrmt mieux ?
}

HumanPlayer::~HumanPlayer(){
	cout << "Destruction d'un HumanPlayer" << endl; //RMQ: Ca devrait théoriquement être dans la vue, est-ce vrmt mieux ?
}

string HumanPlayer::Play(int turn){
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

///////////////////////// FILEPLAYER ///////////////////////////////

FilePlayer::FilePlayer(Plateau* platee, Vue* vuee, string player_name): Player(platee, vuee){
	name = player_name; //Get and Set name à faire ?
	string dir_name = init();
	string names[2];
	if(player_name == "blanc"){ // Permet de désigner le fichier qui sera ouvert en lecture ou
		names[0] = "noir";		// en écriture
		names[1] = "blanc"; 	// voir Precision_Joueur_Fichier.md si incompréhension
	}
	else{
		names[0] = "blanc";
		names[1] = "noir";
	}
	string nom_fichier_ecr = dir_name+names[0]+".txt";
	string nom_fichier_lect = dir_name+names[1]+".txt";
	fichier_ecr.open(nom_fichier_ecr, fstream::in | fstream::out | fstream::trunc);
	fichier_lect.open(nom_fichier_lect, fstream::in); 											
	while (!fichier_lect.is_open()){ //RMQ: close les fichiers dans le destructeur
			cout << "Attente du joueur "<< names[1] <<" (fichier "<< names[1] <<".txt indisponible)" << endl; //RMQ: Ca devrait théoriquement être dans la vue, est-ce vrmt mieux ? (on pourrait choper le nom du player avec un getteur
			// Ajout d'une temporisation avant de réessayer
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			fichier_lect.open(nom_fichier_lect);
	}
}

FilePlayer::~FilePlayer(){
	fichier_ecr.close();
	fichier_lect.close();
	cout << "Destruction d'un FilePlayer" << endl;//RMQ: Ca devrait théoriquement être dans la vue, est-ce vrmt mieux ?
}
void FilePlayer::explore(char * dir_name){
/*
 * Méthode permettant d'indiquer le contenu du répertoire pris en param.
 * Permet au joueur console de vérifier ou placer les fichiers.
 * Programme rédigé par SolidusCode dans un tutoriel disponible sur :
 * https://www.youtube.com/watch?v=w9l8kLPQ39c
 */ 
	DIR *dir; //pointer to open directory
	struct dirent *entry; //stuff inside the direct

 
	//1 open
	dir = opendir(dir_name);
	if (!dir) {
		cout << "Directory was not found \n";//RMQ: Ca devrait théoriquement être dans la vue, est-ce vrmt mieux ?
		return;
	}

	//2read
	cout << "\nThis directory contains : \n" << endl;//RMQ: Ca devrait théoriquement être dans la vue, est-ce vrmt mieux ?
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.'){
			string path = string(entry->d_name);
			cout << "- " << path << endl;//RMQ: Ca devrait théoriquement être dans la vue, est-ce vrmt mieux ?
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
		cout << "Where would you save the files ?" << endl; //RMQ: Ca devrait théoriquement être dans la vue, est-ce vrmt mieux ?
		getline(cin, pathname);
		// EXAMPLE : /mnt/c/Users/Louis Vande Perre/Documents/Polytech/BA3(Biomed)/Informatique/Projet/test/
		explore((char*) pathname.c_str()); /* c_str converti un string 
											* en char* (type nécessaire
											*  à la bonne exécution de 
											* la fonction explore())
											*/
		cout << "Is it a good directory ? (y/n)" << endl; //RMQ: Ca devrait théoriquement être dans la vue, est-ce vrmt mieux ?
		getline(cin, uresponse);
	}
	return pathname;
}

string FilePlayer::Play(int turn){
	//Player::Play(turn);
	ok = false;
	//RMQ: soit c est ici qu on print le plateau soit dans le main, pareil pour la ligne suivante avec les scores
	vue->Print_state(plate->Get_Noirs(), plate->Get_Blancs(), turn);
	string input = "";
	while(!ok){
		vue->Ask_pos(name);
		input = getMove();
		if(Check_input(input)){
			int y = input[0] - 'a';
			int x = input[1] - '1';
			plate->Set_Turn(turn);
			if(x ==('0'-'1') && y ==('0'-'a')){  //RMQ: On ferait pas une fonction pour ce if ?
				if(plate->Check_notplay()){
					vue->Skip_turn();
					ok = true;
				}
				else {
					vue->Cant_skip();
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

void FilePlayer::saveMove(string move){
	if(fichier_ecr.is_open()){
		fichier_ecr << move << endl;
	}
	else
		cout << "problem" <<endl;
}

bool FilePlayer::confirmation(){
	char uresp;
	if(uresp != '\n'){
		vue->Ask_confirmation();
		cin.get(uresp);
	}
}

string FilePlayer::getMove(){
	string move;
	while (!(getline(fichier_lect, move))){
		// Echec de la lecture - Effacement des flags d'erreur
		fichier_lect.clear();
		// Ajout d'une temporisation avant de réessayer
		//cout << "En attente du joueur fichier" <<endl; //impression non nécessaire, mais aide
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	return move;
}


///////////////////////// IAPLAYER //////////////////////////////////

IAPlayer::IAPlayer(Plateau* platee, Vue* vuee) : Player(platee, vuee){
	cout << "Creation d'un IAPlayer" << endl;
}

IAPlayer::~IAPlayer(){
	cout << "Destruction d'un IAPlayer" << endl;
}

string IAPlayer::Play(int turn){
	vue->Print_state(plate->Get_Noirs(), plate->Get_Blancs(), turn);
	plate->Set_Turn(turn);
    int count = 1;
    float value = -1000000;
    float temp = 0;
    int pos[2] ={};
    vector<int> pos_to_check = plate->Pos_Play(); 	// pos_to_check, contient toutes les positions ou le pion peut se placer
    for(int i = 0; i < pos_to_check.size(); i+=2){ 	// pos_to_check, de la forme (ax, ay, bx, by) on prend donc coord 2 par 2
        imaginaire = *plate; 						// copie du plateau que l'on va manipuler
        if(imaginaire.Check_eat(pos_to_check[i], pos_to_check[i+1])){
            imaginaire.Eat();
            imaginaire.Set_Turn(imaginaire.Get_Turn() + 1); // on rajoute un tour de jeu --> chgt de joueur
            temp = Heuristic(imaginaire ,plate->Get_Turn(),plate->Get_Turn()%2) +  A(imaginaire,count,plate->Get_Turn()%2);
            if( temp > value){
                value =temp;				// Cette condition permet de garder en mémoire le meilleur scénario
                pos[0] = pos_to_check[i];		// et a l'IA de jouer ce coup là
                pos[1] = pos_to_check[i+1];
            }
        }
    }
    if(pos_to_check[0] == 9 && pos_to_check[1] == 9){	// Dans le cas ou le vecteur pos_to_check est de taille nulle,
		vue->Skip_turn();								// la fonction Pos_Play() initialise ses 2 premières valeurs à 9
		plate->Not_play();								// ce qui est scénario ou l'IA doit passer son tour car rien à manger
		return "00";
	}
	else if(plate->Check_eat(pos[0],pos[1])){
		plate->Eat();
		char xc = (pos[1]+'a');
		char yc = (pos[0]+'1');
		char end = ('\0');
		char char_move[3] = {xc,yc,end};
		string string_move = char_move;
		return string_move;
	}
	
}


float IAPlayer::A(Plateau board, int count, int realColor){	// Reprends le meme fonctionnement que la fonction Play
    float value = 0;										// on va partir du plateau imaginaire pour imaginer plusieurs
    float temp = 0;											// tours à l'avance, mais on est limité par count
    if(count <= 11){										// car l'IA ne peut répondre en plus de 20 secondes
        vector<int> pos_to_check = board.Pos_Play();
        for(int i = 0; i < pos_to_check.size(); i+=2){
            imaginaire = board;
            if(imaginaire.Check_eat(pos_to_check[i], pos_to_check[i+1])){
                imaginaire.Eat();
                imaginaire.Set_Turn(imaginaire.Get_Turn() + 1); //A chaque appel de A(...) on simule un tour de plus
                count++;
                temp = Heuristic(imaginaire, (count+realColor)-1, realColor) + A(imaginaire,count,realColor);
                if(abs(temp) > abs(value)){
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
        if(color%2 == 0){	//blancs							// Ces lignes permettent de prendre en compte,
            score = /*board.Get_Blancs()*/ + board.Corner() + board.Mobility() + board.Stability(realColor+1);		// dans le choix de l'IA, le nombre de pions mangés.
        }														//RMQ: ça ne sert à rien de prendre en compte le nombre de pions mangés...
																// éventuellement dans les derniers tours mais pas avant
        else{ // noirs
            score = /*-(board.Get_Noirs() +*/ -(board.Corner() + board.Mobility() + board.Stability(realColor+1));
        }   
    }
    else{ // noirs
        if(color%2 == 0){ //blancs
            score = /*-(board.Get_Blancs() +*/ -(board.Corner() + board.Mobility() + board.Stability(realColor+1));
        }
    
        else{ //noirs
            score = /*board.Get_Noirs()*/ + board.Corner() + board.Mobility() + board.Stability(realColor+1);
        } 
    }
    return score;
}
