all : Plateau.o Player.o Main.o Vue.o
	g++ Plateau.o Player.o Main.o Vue.o -o projet
Plateau.o : Plateau.h Plateau.cpp
	g++ -c Plateau.cpp
Player.o : Player.h Player.cpp
	g++ -c Player.cpp
Main.o : Main.cpp
	g++ -c Main.cpp
Vue.o : Vue.h Vue.cpp
	g++ -c Vue.cpp
projet.o : projet.cpp
	g++ -c projet.cpp

clean:
	rm *.o projet
