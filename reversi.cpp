#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
int j = 0;
vector<int> pos_to_eat;

void print_board(int board[64]){
/*
 * Imprime le plateau et son contenu 
 */
	cout << "  a b c d e f g h  " << endl;
    for(int i=0; i<8; i++){
        cout << i + 1;
        cout << " ";
	    for(int j=0; j<8; j++){
		    if(board[(8*i)+j]==0)
		    	cout << ". ";
		    else if(board[(8*i)+j]==1)	//Le joueur noir est caractérisé par l'entier 1 et les "X"
		    	cout << "X ";
		    else if(board[(8*i)+j]==2)	//Le joueur blanc est caractérisé par l'entier 2 et les "O"
		    	cout << "O ";
	    }
        cout << i+1 << endl;
    }
	cout << "  a b c d e f g h  " << endl;
}

void init_board(int* board){
	
	for(int i = 0; i<64; i++){
		if( i == 27 || i == 36)
			*(board + i) = 2;
		else if (i == 28 || i == 35)
			*(board + i) = 1;
		else
			*(board + i) = 0;
	}
}

bool check_input(int* board, int x, int y){
    if(x>8 || x<0 || y>8 || y < 0){
        cout << "invalid position" <<endl;
        return false;
    }
    
    else if(*(board + ((8*(x))+(y))) != 0){
        cout << "invalid position" <<endl;
        return false;
    }
    else
        return true;

}

void eat(int* board, int turn){
    for(int i =0; i<pos_to_eat.size();i++)
        *(board + pos_to_eat[i]) = turn;
}

bool check_direction(int position, int* board, int direction, int turn,int* pos_eat){

    if(position + direction >= 0 && position + direction < 63){
        if(*(board + position + direction) == turn){
            *(pos_eat + j) = position;
            for(int i = 0; i <= j;i++)
                pos_to_eat.push_back (*(pos_eat +i));
            return true;
        }
        else if (*(board + position + direction) == 0)
            return false;
        else{ 
            *(pos_eat + j) = position;
            j++;
            return check_direction(position + direction, board, direction,turn, pos_eat);  
        }
    }
}

bool check_eat(int position, int* board, int turn){
    int direction[8] = {1,-1,7,-7,8,-8,9,-9};
    bool eat = false;
    for(int i = 0; i<8; i++){
        int pos_eat[6] = {0};
        j = 0;
        if(position + direction[i] >= 0 && position + direction[i] < 63){
            if(*(board + position + direction[i]) != turn && *(board + position + direction[i]) != 0){
                if(check_direction(position + direction[i], board, direction[i],turn, &pos_eat[0]))
                    eat = true;     
             }
        }
    }
    return eat;
}

bool check_notplay(int* board, int turn){
/*
 * Vérifie si le joueur peut en effet passer son tour
 */
	bool r = true;
	for(int i=0; i<64; i++){
		if(*(board+i) == 0){
			if(check_eat(i, board, turn)){
				cout << "Un mouvement est possible" << endl;
				r = false;
				break;
			}
			else
				r = true;
		}
	}
	return r;
}

void player_turn(int* turn, int* board){
    
    string input = "";
    int x =0;
    int y =0;
    pos_to_eat.clear();
    if(*turn == 2){
        cout << "White player turn" << endl;
        *turn = 1;        
    }    
    else{
	    cout << "Black player turn" << endl;
        *turn = 2;        
    }
    while(true){
		cout << "enter a position :";
		getline(cin, input);
		if(input.length() == 2){ 
                y = input[0] - 'a';
                x = input[1] - '1';
                if((x+'1')=='0' && (y+'a')=='0'){
					if(check_notplay(board, *turn)){
						cout << "Le joueur passe son tour" << endl;
						break;
					}
				}
                else if(check_input(board,x,y)){
                    if(check_eat(((8*(x))+(y)),board, *turn)){
                        *(board + ((8*(x))+(y))) = *turn;
                        eat( board, *turn);
                        break;
					}
                    else
                        cout << "mouvement impossible" << endl;	// ne doit pas s'imprimer lorsque le joueur tente, et échoue, de passer son tour
				}
		}          
        else
            cout << "Entrée invalide" << endl;
	}
}


int main(int argc, char *argv[]){	

    int board[64] = {0};
    int turn = 2;
    init_board(&board[0]);
	print_board(board);
    while(true){
        player_turn(&turn, &board[0]);
        print_board(board);
    }
	return 0;

}


