UTIL=Graph.cpp
MAIN=main.cpp
BINARY=main.exe

all:
	g++ -Wall -g $(UTIL) $(MAIN) -o $(BINARY) -lm

run:
	./$(BINARY)

debug:
	gcc -DDEBUG -Wall $(MAIN) $(UTIL) -o $(BINARY)

zip:
	zip project.zip Makefile main.c HashTable.h HashTable.c Student.c Student.h LinkedList.h LinkedList.c Util.h

valgrind:
	valgrind -s --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

clean:
	@rm *.o
