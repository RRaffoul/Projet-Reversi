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

void explore(char * dir_name)
{
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
			cout << "- " << path << '\n' << endl;
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
			explore((char*) pathname.c_str()); //c_str converti un string en char* (type nécessaire à la bonne exécution de la fonction explore()
			cout << "Is it a good directory ? (y/n)" << endl;
			getline(cin, uresponse);
		}
		return pathname;
}


//void read(bool turn){}

int main(){
		string pathname = init();
		ofstream fichier_noir(pathname+"/noir.txt");
		ofstream fichier_blanc(pathname+"/blanc.txt");
		string to_write = "";
		cout << "Que voulez vous écrire dans blanc.txt ?" << endl;
		getline(cin, to_write);
		if(fichier_blanc.is_open()){
			fichier_blanc << to_write;
			fichier_blanc.close();
		}
		else
			cout << "File is not open" << endl;
		cout << "Que voulez vous écrire dans noir.txt ?" << endl;
		getline(cin, to_write);
		if(fichier_noir.is_open()){
			fichier_noir << to_write;
			fichier_noir.close();
		}
		else
			cout << "File is not open" << endl;
			
}
