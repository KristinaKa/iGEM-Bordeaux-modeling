cc= g++ -std=c++11


interface : main.cpp window.cpp window.hpp run
	$(cc) main.cpp window.cpp -o `pkg-config gtkmm-3.0 --cflags --libs` -o interface


run : square.o bacteria.o lattice.o main.o
	$(cc) Modeling/main.o Modeling/square.o Modeling/bacteria.o Modeling/lattice.o -o run
main.o : Modeling/main.cpp square.o bacteria.o lattice.o
	$(cc) -c Modeling/main.cpp -o Modeling/main.o
square.o: Modeling/square.hpp Modeling/square.cpp Modeling/bacteria.hpp
	$(cc) -c Modeling/square.cpp -o Modeling/square.o
bacteria.o: Modeling/bacteria.hpp Modeling/bacteria.cpp Modeling/lattice.hpp 
	$(cc) -c Modeling/bacteria.cpp -o Modeling/bacteria.o
lattice.o: Modeling/lattice.hpp Modeling/lattice.cpp Modeling/square.hpp Modeling/bacteria.hpp
	$(cc) -c Modeling/lattice.cpp -o Modeling/lattice.o


clean:
	rm -f Modeling/*.o run
