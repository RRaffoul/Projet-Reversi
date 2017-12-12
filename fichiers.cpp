#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <chrono>
#include <thread>
#include <unistd.h> // nécessaire pour l'utilisation de la fct access()
using std::ifstream;
using std::ofstream;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using namespace std;

/*
 * Dans ce programme, le joueur de type fichier sera le joueur noir.
 * Donc le programme doit ECRIRE dans un fichier blanc.txt les mvts
 * du joueur blanc et doit LIRE dans un fichier noir.txt, ou le joueur 
 * noir écrira (via un autre terminal) ses mouvements.
 */

void explore(char * dir_name){
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
			string path = string(dir_name) + '/' + string(entry->d_name);
			cout << "- " << path << endl;
			stat(path.c_str(), &info);
		}
	}
	
	//3close
	closedir(dir);
}
string init(){
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


//void read(bool turn){}

int main(){
		string pathname = init();
		string nom_fichier_noir = pathname+"/noir.txt";
		string nom_fichier_blanc = pathname+"/blanc.txt";
		ifstream fichier_noir(nom_fichier_noir);
		ofstream fichier_blanc(nom_fichier_blanc);
		while (!fichier_noir.is_open()){
			cout << "Attente du joueur noir (fichier noir indisponible)" << endl;
			// Ajout d'une temporisation avant de réessayer
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			fichier_noir.open(nom_fichier_noir);
		}
		string last_move;
		bool joueur_courant = true; // false = 0 = "blanc"; true = 1 = "noir"
		/* Premier tour : on attend que le joueur noir commence en 
		 * indiquant le placement de son pion dans fichier_noir
		 */
		while (!(getline(fichier_noir, last_move)))
		{
			// Echec de la lecture - Effacement des flags d'erreur
			fichier_noir.clear();
			// Ajout d'une temporisation avant de réessayer
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
		
		// On passe au joueur suivant
		joueur_courant = !joueur_courant;
		// Le dialogue s'arrête lorsqu'une réplique est "[THE END]"
		bool fini = ( last_move == "[THE END]" );
		
		while (!fini){
			// Affichage du dernier move
			cout << "White player plays : " << last_move << endl;
			// Ajout d'une temporisation
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			
			// Si cette dernière réplique était "[THE END]", on sort de la boucle
			if  ( fini = ( last_move == "[THE END]" ) )
				break;
			
			if (joueur_courant)
			{
				// Le joueur courant est le noir, le programme lui indique la dernière réplique du joueur blanc dans fichier_blanc.txt
				fichier_blanc << last_move << endl;
				// Le programme attend que le joueur noir indique sa réplique dans fichier_noir.txt
				while ( !(getline(fichier_noir, last_move)) )
				{
					// Echec de la lecture - Effacement des flags d'erreur
					fichier_noir.clear();
					// Ajout d'une temporisation avant de réessayer
					std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				}
			}
			else
			{
				// Le joueur courant est le blanc, lecture de la nouvelle réplique
				cout << "White player's turn  : ";
				getline(cin, last_move);
			}

			// On passe au joueur suivant
			joueur_courant = !joueur_courant;
		}
}
