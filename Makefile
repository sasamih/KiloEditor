kilo: kilo.c terminal.c input.c output.c init.c append_buffer.c
	$(CC) input.c output.c terminal.c init.c append_buffer.c kilo.c -o kilo -Wall -Wextra -pedantic

clean:
	rm kilo.exe