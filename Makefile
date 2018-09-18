CC=D:/Projects/Programming/mingw64/bin/g++
sfml_include=D:\Projects\Programming\Praktica\SFML-2.4.2\include
sfml_lib=-L D:\Projects\Programming\Praktica\SFML-2.4.2\lib -lsfml-graphics -lsfml-window -lsfml-system
Lab04: main.o map.o enemy.o cache.o LeePathfinder.o 
	$(CC) main.o map.o enemy.o cache.o LeePathfinder.o -o Lab04 $(sfml_lib)
main.o: main.cpp map.o enemy.o
	$(CC) -o main.o -c main.cpp -I $(sfml_include)
map.o: map.cpp map.h
	$(CC) -o map.o -c map.cpp -I $(sfml_include)
enemy.o: enemy.cpp enemy.h map.h
	$(CC) -o enemy.o -c enemy.cpp -I $(sfml_include)
cache.o: cache.cpp cache.h
	$(CC) -o cache.o -c cache.cpp -I $(sfml_include)
LeePathfinder.o: LeePathfinder.cpp
	$(CC) -o LeePathfinder.o -c LeePathfinder.cpp -I $(sfml_include)
clean:
	del *.o *.exe 