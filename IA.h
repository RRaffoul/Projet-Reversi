#include <vector>

class IA{
 private:
	Plateau original;
	Plateau imaginaire;
	vector<int> pos_to_check;
	int count;
 public:
	int Search_func(Plateau board);
	int A(Plateau board);
}
