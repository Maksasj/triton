
CC=gcc
SOURCE=parser.c
OBJ=$(SOURCE:.c=.o)
EXE=parser

all: $(EXE) clean

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@

.o: .c
	$(CC) -c $< -o $@

clean:
	rm -rf $(OBJ)