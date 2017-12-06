#include <iostream>
#include <string>
#include <fstream>
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

string init(){
		string pathname = "";
		cout << "Where would you save the files ?" << endl;
		getline(cin, pathname);
		/*int a = access(pathname, F_OK);
		while(a == -1){
				cout << "This repository doesn't exist. Try another address" << endl;
				getline(cin, pathname);
				a = access(pathname, F_OK);
		}*/
		return pathname;
}


//void read(bool turn){}

int main(){
		string pathname = init();
		ofstream fichier_noir(pathname+"/noir.txt");
		ofstream fichier_blanc(pathname+"/blanc.txt");
		string to_write = "";
		cout << "Que voulez vous écrire dans blanc.txt ?" << endl;	// ATTENTION, POUR LE MOMENT NE MARCHE QU'AVEC "." POUR SAUVER DANS LE DOSSIER DANS LEQUEL ON SE TROUVE 
		getline(cin, to_write);
		if(fichier_blanc.is_open()){
			fichier_blanc << to_write;
			fichier_blanc.close();
		}
		cout << "Que voulez vous écrire dans noir.txt ?" << endl;
		getline(cin, to_write);
		if(fichier_noir.is_open()){
			fichier_noir << to_write;
			fichier_noir.close();
		}
}
