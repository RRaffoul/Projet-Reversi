#include <iostream> //tous utiles ?
#include <string>
#include <sstream>

class Vue {
 public :
	Vue();
	~Vue();
	void Print_board();
	void Print_winner();
    void Print_state(){
	void White_turn();
	void Black_turn();
	void Ask_pos();
	void Skip_turn();
	void Cant_skip();
	void Inv_entry_1();
	void Inv_entry_2();
	void Inv_entry_3();
};
