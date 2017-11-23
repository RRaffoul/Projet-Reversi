#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
int j = 0;
vector<int> pos_to_eat;
int end = 0; 

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
		    else if(board[(8*i)+j]==1)	//Le joueur blanc est caractérisé par l'entier 1 et les "X"
		    	cout << "X ";
		    else if(board[(8*i)+j]==2)	//Le joueur noir est caractérisé par l'entier 2 et les "O"
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
        else if (*(board + position + direction) == 0){
            return false;
        }
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
        int pos_eat[64] = {0};
        j = 0;
        if(position + direction[i] >= 0 && position + direction[i] < 63){
            if((direction[i] == 7 || direction[i] == -9 || direction[i] == -1) && (position % 8 == 0)){	// ne sert à rien dans la matrice
                cout << "denied" << endl;
            }
            else if((direction[i] == -7 || direction[i] == 9 || direction[i] == 1) && ((position + 1) % 8 == 0)){
                cout << "nope" << endl;
            }
            else if(*(board + position + direction[i]) != turn && *(board + position + direction[i]) != 0){
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
	for(int i=0; i<63; i++){
		if(*(board+i) == 0){
			if(check_eat(i, board, turn)){
				cout << "Un mouvement est possible" << endl;
				return false;
			}
		}
	}
	return true;
}

void count(int *board,int* total){
    for (int i = 0; i <64; i++){
        if(*(board + i) == 1)
            *(total) = *(total) + 1;
        else if(*(board + i) == 2)
            *(total+1) = *(total+1) + 1;
    }
}

void end_game(int *board){
	int total[2] = {0};
    count(board,&total[0]);
    if (total[0] > total[1] )
        cout << "white player wins" << endl;
    else if (total[0] < total[1])
        cout << "black player wins" << endl;
    else
        cout << "draw" << endl;
}

void player_turn(int* turn, int* board){
    
    string input = "";
    int x =0;
    int y =0;
    if(*turn == 2){
        cout << "White player turn (X)" << endl;
        *turn = 1;        
    }    
    else{
	    cout << "Black player turn (O)" << endl;
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
                        end++;
						break;
					}
				}
                else if(check_input(board,x,y)){
					pos_to_eat.clear();
                    if(check_eat(((8*(x))+(y)),board, *turn)){
                        *(board + ((8*(x))+(y))) = *turn;
                        eat( board, *turn);
                        end = 0;
                        break;
					}
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
    while(end != 2){
        player_turn(&turn, &board[0]);
        print_board(board);
    }
    end_game(&board[0]);
	return 0;

}


