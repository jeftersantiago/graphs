MAIN=problem01.cpp
BINARY=main.exe

all:
	g++ -Wall -g $(UTIL) $(MAIN) -o $(BINARY)

run:
	./$(BINARY)

debug:
	gcc -DDEBUG -Wall $(MAIN) $(UTIL) -o $(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

zip:
	zip arvoreAVL.zip Makefile main.c AVLTree.h Game.h AVLTree.c Game.c
clean:
	@rm *.exe
