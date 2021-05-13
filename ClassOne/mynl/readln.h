/**
 @file readln.h
 \brief Contains function that reads one line
*/

#ifndef READLN
#define READLN

#include <sys/types.h>

/**
 * @brief Function that separates one line from a file
 * @param fd
 * @param line
 * @param
 * @return 
*/
ssize_t readln(int fd, char * line, size_t size);

#endif