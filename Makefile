STD = -std=c++11

all : Plateau.o Player.o Main.o Vue.o
	g++ Plateau.o Player.o Main.o Vue.o -o projet
Plateau.o : Plateau.h Plateau.cpp
	g++ $(STD) -c Plateau.cpp
Player.o : Player.h Player.cpp
	g++ $(STD) -c Player.cpp
Main.o : Main.cpp
	g++ $(STD) -c Main.cpp
Vue.o : Vue.h Vue.cpp
	g++ -c Vue.cpp
projet.o : projet.cpp
	g++ -c projet.cpp

clean:
	rm -f *.o projet *.txt
