/*void Plateau::game(){
	while(!game_over()){
        print_board();
        player_turn();
    }
    print_winner();	
}*/ //Ca je sais pas ou il faudrait le mettre pour que ca soit O.O., peut etre a redefinir

/*bool Plateau::game_over(){
	if (passe == 2)
		return true;
	else if (noirs + blancs == 64)
		return true;
	return false;
}*/

Player* playerW = new Player();
Player* playerB = new Player();



void Turn(){
    turn++;
    color = (turn + 1)%2 + 1;
    /*int x;
    int y;*/
    if(color == 1){
        view->White_turn();
        playerW->Play();       
    }    
    
    else{
	    view->Black_turn();
        playerB->Play();              
    }
}
