CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic

.phony : all
all : automated_parking.exe

automated_parking.exe : main.cpp carsParking.o carsHistory.o
	$(CXX) $(CXXFLAGS) -o automated_parking.exe main.cpp carsParking.o carsHistory.o

carsParking.o : carsParking.cpp carsParking.hpp
	$(CXX) $(CXXFLAGS) -c carsParking.cpp

carsHistory.o : carsHistory.cpp carsHistory.hpp
	$(CXX) $(CXXFLAGS) -c carsHistory.cpp


.phony : clean
clean:
	rm -f *.o
	rm -f *.exe
	rm -f *.txt
