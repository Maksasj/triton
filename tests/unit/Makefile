
CC=gcc
SOURCE=lexer.test.c
OBJ=$(SOURCE:.c=.o)
EXE=lexer.test

all: $(EXE) clean test

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@

.o: .c
	$(CC) -c $< -o $@

clean:
	rm -rf $(OBJ)

test:
	./$(EXE)
