

IA::IA(Plateau* platee, Vue* vuee){
	plate = platee;
	vue = vuee;
}

IA::~IA(){
	cout << "Destruction d'une IA" << endl;
}

void IA::Play(int turn){
	vue->Print_state(plate->Get_Noirs(), plate->Get_Blancs(), turn);
	plate->Set_Turn(turn);
	pos = Search_func(&plate);
	if(pos[0] == 0 && pos [1] == 0){
		vue->Skip_turn();
	}
	else if(plate->Check_eat(pos[0],pos[1])){
		plate->Eat();
	}
}




int IA::A(Plateau board){
	int best[3] = {0};	
	if(count <= 5){ //si on s arrete a 4 (pair) ca n a pas de sens, on s arreterait sur un coup d un adversaire, pas sur un a toi
		if (count % 2 == 0){ /*donc c est au tour de l adversaire, ca compte pas ses point mais on pourrait proceder par malus 
			exactement de la meme facon en negatif ou des bonus si l adversaire passe son tour ahah !*/
			imaginaire = board;
			pos_to_check = imaginaire.Pos_play(); //jsp si ca s ecrti vector1 = vector2 
			int a = pos_to_check.size(); //pas mieux de faire ca plutot que de le mettre dans le if comme dans plateau ? Doit compter moins de fois tout non ?
			for (i = 0; i < a; i+=2){  //on remarque que si a = 0 on a un retour de 00 pour le choix de position
				imaginaire = board;
				if(imaginaire->Check_eat(pos_to_check(i), pos_to_check(i+1))){//a regler ca hein
					imaginaire.Eat();
				}
				futur [3] = A(imaginaire)
				best[0] = futur[0];  //ici on devrait remettre valeur etc pour rajouter des points negatifs
			}
		}
		else{ //donc c est a nous
			imaginaire = board;
			pos_to_check = imaginaire.Pos_play(); //jsp si ca s ecrti vector1 = vector2 
			int a = pos_to_check.size(); //pas mieux de faire ca plutot que de le mettre dans le if comme dans plateau ? Doit compter moins de fois tout non ?
			for (i = 0; i < a; i+=2){
				imaginaire = board;
				if(imaginaire->Check_eat(pos_to_check(i), pos_to_check(i+1))){//a regler ca hein
					imaginaire.Eat();
				}
				int futur [3] = A(imaginaire);
				valeur = imaginaire.Get_Blancs() + futur[0]; //on doit optimiser le premier membre de cette somme
				if (best[0] < valeur){
					best[0] = valeur;
					best[1] = pos_to_check(i);
					best[2] = pos_to_check(i+1);
				}
			}
		}
		count++;
	}
	return best;
}

int IA::Search_func(Plateau board){
	count = 1; //si on veut mettre = 0, modifier dans l autre fonction dans le if <= devient < 
	int direction[3] = A(board);
	int objectif [2]={0};
	objectif [0] = direction [1];
	objectif [1] = direction [2];
	return objectif;
}
