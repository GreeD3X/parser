CC = g++
LCOV_DIR = lcov/bin
CFLAGS = -Iinc -Wall -Werror -pedantic-errors -Wextra -std=c++14 -ftrapv -O2
OBJECTS = obj/lexer.o obj/main.o obj/parser.o
EXEC = project4.out 
LEXER = lexer.out

all : $(EXEC)

$(EXEC) : $(OBJECTS)
	$(CC) $^ -o $@

#include $(OBJECTS:.o=.d)

obj/%.o : src/%.cpp
	$(CC) $< $(CFLAGS) -c -o obj/$*.o
	$(CC) $< $(CFLAGS) -MM > obj/$*.d

run : $(EXEC)
	./$(EXEC)

clean :
	rm -f *.out *.s obj/*.o obj/*.d src/*.cpp~
	rm -rf *.dSYM
