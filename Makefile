
CC=gcc
SOURCE=triton_example.c
OBJ=$(SOURCE:.c=.o)
EXE=triton_example

all: $(EXE) clean execute

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@

.o: .c
	$(CC) -c $< -o $@

clean:
	rm -rf $(OBJ)

execute:
	./$(EXE)

execute_format:
	./$(EXE) | jq