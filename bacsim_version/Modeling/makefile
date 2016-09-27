cc= g++ -g

run : main.o square.o bacteria.o lattice.o
	$(cc) main.o square.o bacteria.o lattice.o -o run
square.o: square.hpp square.cpp bacteria.hpp
	$(cc) -c square.cpp
bacteria.o: bacteria.hpp bacteria.cpp lattice.hpp 
	$(cc) -c bacteria.cpp
lattice.o: lattice.hpp lattice.cpp square.hpp bacteria.hpp
	$(cc) -c lattice.cpp

clean:
	rm -f *.o run
