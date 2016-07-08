COMPILER = g++
WARNINGS = -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
COMPILER_OPTS = -c -g -O0 -Wfatal-errors -Werror $(WARNINGS)
LINKER = g++

MAIN_OBJS = main.o
MAIN_DEPS = list.h list.cpp list_given.h list_given.cpp game.h game.cpp main.cpp

CODE_CLN = *.o mp3snake mp3local

all: mp3snake

mp3snake : main.o
	$(LINKER) $(MAIN_OBJS) -o mp3snake -L/class/cs225/software/SFML-2.1-gcc/lib -lsfml-graphics -lsfml-window -lsfml-system 

main.o : $(MAIN_DEPS)
	$(COMPILER) $(COMPILER_OPTS) main.cpp -I/class/cs225/software/SFML-2.1-gcc/include

mp3local : mainlocal.o
	$(LINKER) $(MAIN_OBJS) -o mp3local -lsfml-graphics -lsfml-window -lsfml-system 

mainlocal.o : $(MAIN_DEPS)
	$(COMPILER) $(COMPILER_OPTS) main.cpp

clean:
	-rm -f $(CODE_CLN)
