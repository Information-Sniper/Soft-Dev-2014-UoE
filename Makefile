CC = pgcc
EXE = connect4

MF= Makefile

CFLAGS= -fastsse

LFLAGS= -lm

SRC= \
	main.c \
	point.c \
	board.c \
	move.c \
	game.c

INC= \
	defines.h \
	point.h \
	board.h \
	move.h \
	game.h \
	connect4.h


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
