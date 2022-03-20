all:
	gcc -Wall -Wextra -Werror -ansi -pedantic project.c
	./a.out
clean:
	rm a.out
