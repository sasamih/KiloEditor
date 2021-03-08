kilo: kilo.c terminal.c input.c output.c
	$(CC) input.c output.c terminal.c kilo.c -o kilo -Wall -Wextra -pedantic

clean:
	rm kilo.exe