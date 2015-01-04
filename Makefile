#
# Specifiy the target
all:	war.exe

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
war.exe:	CardDriver.o PlayingCard.o Deck.o Player.o War.o
	g++ -o war.exe CardDriver.o PlayingCard.o Deck.o Player.o War.o

# Specify how the object files should be created from source files
CardDriver.o:	CardDriver.cpp
	g++ -std=c++11 -c -g CardDriver.cpp

# Specify how the object files should be created from source files
PlayingCard.o:	PlayingCard.cpp
	g++ -std=c++11 -c -g PlayingCard.cpp

# Specify how the object files should be created from source files
Deck.o:	Deck.cpp
	g++ -std=c++11 -c -g Deck.cpp

# Specify how the object files should be created from source files
Player.o:	Player.cpp
	g++ -std=c++11 -c -g Player.cpp

# Specify how the object files should be created from source files
War.o:	War.cpp
	g++ -std=c++11 -c -g War.cpp


# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o *~ *.exe Lab5