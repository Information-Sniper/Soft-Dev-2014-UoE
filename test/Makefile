CC = pgcc
EXE = test_connect4

MF = Makefile

CFLAGS = -O0 -DUNIT_TEST -I~/local/include

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
