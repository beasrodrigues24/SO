/**
 @file mynl.h
 \brief Contains function that separates line by line
*/

#ifndef MYNL
#define MYNL

/**
 * @brief Separates text line by line
 * @param fd File descriptor
 * @return 0 if successful, -1 if unsuccessful
*/
int mynl(int fd);

#endif