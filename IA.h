#include <vector>

class IA{
 private:
	Plateau* plate;
	Vue* vue;
	Plateau imaginaire;
	vector<int> pos_to_check;
	int count;
	int pos[2]; 
 public:
	IA();
	~IA();
	int Search_func(Plateau board);
	int A(Plateau board);
}
