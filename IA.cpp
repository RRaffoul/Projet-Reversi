


int IA::A(Plateau board){
	int best[3] = {0};
	if(count <= 5){ //si on s arrete a 4 (pair) ca n a pas de sens, on s arreterait sur un coup d un adversaire, pas sur un a toi
		if (count % 2 == 0){ //donc c est au tour de l adversaire, ca compte pas ses point mais on pourrait proceder par malus exactement de la meme facon en negatif
			original = board;
			imaginaire = board;
			pos_to_check = imaginaire.Pos_play(); //jsp si ca s ecrti vector1 = vector2 
			int a = pos_to_check.size(); //pas mieux de faire ca plutot que de le mettre dans le if comme dans plateau ? Doit compter moins de fois tout non ?
			for (i = 0; i < a; i+=2){
				imaginaire = original;
				if(imaginaire->Check_eat(pos_to_check(i), pos_to_check(i+1))){//a regler ca hein
					imaginaire.Eat();
				}
			}
		}
		else{ //donc c est a nous
			original = board;
			imaginaire = board;
			pos_to_check = imaginaire.Pos_play(); //jsp si ca s ecrti vector1 = vector2 
			int a = pos_to_check.size(); //pas mieux de faire ca plutot que de le mettre dans le if comme dans plateau ? Doit compter moins de fois tout non ?
			for (i = 0; i < a; i+=2){
				imaginaire = original;
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
