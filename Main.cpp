

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

void Game(){
	Plateau* plate = new Plateau();
	View* view = new View(plate);
	Player* playerW = new Player(plate, view);
	Player* playerB = new Player(plate, view);
	int turn = 0;
	while(!plate->Game_over()){
		turn++;
		Turn();
	}
	view->Print_board();
	view->Print_winner();
	delete playerW;
	delete playerB;
	delete view;
	delete plate;
}
