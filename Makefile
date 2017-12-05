all : Plateau.o
	g++ Plateau.o projet.cpp -o projet
Plateau.o : Plateau.cpp
	g++ -c Plateau.cpp
clean:
	rm *.o
