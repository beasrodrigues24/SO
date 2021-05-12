CC = gcc
FLAGS = -Wall -Wextra -g -O2

main: main.c mycp.c mycp.h 
	$(CC) $(FLAGS) mycp.c main.c -o mycp

clean:
	rm -rf $(OBJ)/*.o mycp