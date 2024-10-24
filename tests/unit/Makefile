CC=gcc
SOURCES=lexer.test.c parser.test.c
EXES=$(SOURCES:.c=)

all: $(EXES) clean test

lexer.test: lexer.test.o
	$(CC) lexer.test.o -o lexer.test

parser.test: parser.test.o
	$(CC) parser.test.o -o parser.test

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -rf *.o

test: $(EXES)
	@for exe in $(EXES); do ./$$exe; done
