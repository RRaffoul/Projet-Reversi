#include "Case.h"
#include <iostream>
#include <string>
#include <array>
using std::cout;
using std::endl;

Case::Case (int valInit = 0) : pion(valInit){
	cout << "Construction d'un pion de valeur " << valInit << endl;
	}
	
int Case::getPion() const {
	return pion;}
void Case::setPion(int val){
	pion = val;} /*attention il faut que dans le truc qui utilise ce setPion il y ai un test pour 
		que la valeur ne puisse etre que 0, 1 ou 2 avant hein ! le test ne se fait pas ici*/
		
/*int main(){
	Case case1 = Case(1);
	Case case2 = Case();
	return 1;
}*/

