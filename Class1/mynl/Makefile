CC = gcc
FLAGS = -Wall -Wextra -g -O2

main: main.c readln.c readln.h mynl.c mynl.h 
	$(CC) $(FLAGS) readln.c mynl.c main.c -o mynl

clean:
	rm -rf $(OBJ)/*.o mynl