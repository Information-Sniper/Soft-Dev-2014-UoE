CC = pgcc
EXE = test_connect4

MF = Makefile

# Change the include path (-I) to point 
# to the CUnit include files
CFLAGS = -O0 -DUNIT_TEST -I~/local/include

# Change the library path (-L) to point 
# to the CUnit include files
LFLAGS = -L~/local/lib -lcunit

SRC = \
	test_board.c \
	test_move.c \
	test_game.c \
	test_main.c

INC = \
	../defines.h \
	../board.h \
	../move.h \
	../game.h \
	../connect4.h
	
#
# No need to edit below this line
#

.SUFFIXES:
.SUFFIXES: .c .o

OBJ= 	$(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $<

all:    $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LFLAGS)

$(OBJ): $(INC)

$(OBJ): $(MF)

clean:
	rm -f $(OBJ) $(EXE) core
