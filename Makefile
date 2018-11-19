CXXFLAGS = -DNDEBUG

main: main.o voce.o
	g++ main.o voce.o -o main

main.o: main.cpp
	g++ $(CXXFLAGS) -c main.cpp -o main.o

voce.o: voce.cpp
	g++ $(CXXFLAGS) -c voce.cpp -o voce.o

.PHONY: clean

clean:
	rm *.exe *.o
