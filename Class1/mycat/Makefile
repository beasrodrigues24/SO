CC = gcc
FLAGS = -Wall -Wextra -g -O2

main: main.c mycat.c mycat.h 
	$(CC) $(FLAGS) mycat.c main.c -o mycp

clean:
	rm -rf $(OBJ)/*.o mycat