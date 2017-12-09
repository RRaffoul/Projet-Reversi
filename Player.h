#include <iostream>
#include <string>
#include <sstream>

class Player {
 private:
	bool ok;
	Plateau Plate;
	View view;
 public:
	Player(Plateau, View);
	~Player();
	void Play();
	void Check_input(string)
}
