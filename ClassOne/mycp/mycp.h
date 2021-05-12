/**
 @file mycp.h
 \brief Contains function that mimic cp command
*/

#ifndef MYCP
#define MYCP

/**
 * @brief Is able to mimic the command cp
 * @param fd_r File descriptor from source file
 * @param fd_w File descriptor from destine file
 * @return 0 if sucessful, -1 if not successful
*/
int mycp(int fd_r, int fd_w);

#endif