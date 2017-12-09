all : Plateau.o Player.o Main.o View.o
	g++ Plateau.o Player.o Main.o View.o projet.o -o projet
Plateau.o : Plateau.h Plateau.cpp
	g++ -c Plateau.cpp
Player.o : Player.h Player.cpp
	g++ -c Player.cpp
Main.o : Main.h Main.cpp
	g++ -c Main.cpp
View.o : View.h View.cpp
	g++ -c View.cpp
projet.o : projet.cpp
	g++ -c projet.cpp

clean:
	rm *.o projet
