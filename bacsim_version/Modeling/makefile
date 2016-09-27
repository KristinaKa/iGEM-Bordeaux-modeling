cc= g++ -g

run : main.o square.o bacterium.o lattice.o
	$(cc) main.o square.o bacterium.o lattice.o -o run
square.o: square.hpp square.cpp bacterium.hpp
	$(cc) -c square.cpp
bacterium.o: bacterium.hpp bacterium.cpp lattice.hpp 
	$(cc) -c bacterium.cpp
lattice.o: lattice.hpp lattice.cpp square.hpp bacterium.hpp
	$(cc) -c lattice.cpp

clean:
	rm -f *.o run
