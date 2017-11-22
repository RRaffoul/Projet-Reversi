#include "Case.h"
#include <array>

class Plateau {
	private:
		array<Case, 64> plateau;
	public:
		Plateau();
		~Plateau();
		int imprimePlateau();
		int joueBlanc();
		int joueNoir();
		int valideTour();
};
