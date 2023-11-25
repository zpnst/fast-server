
# include <errno.h>
# include <string.h>
# include <sys/un.h>
# include <string.h>
# include <unistd.h>
# include <iostream>
# include <sys/socket.h>

# define BACKLOG 10
# define BUFFER_SIZE 100
# define TERMINATOR "%stop"
# define SYSTEN_INFORMATION 0
# define KILL_CONNECTION "%shutdown"
# define SOCKET_ADDRESS "/tmp/sockex"

# pragma once

/* Function for checking 
   connection interruption */
bool terminator(char* buffer, const char* string) {
    bool argument = true;
    for (unsigned int iter = 0; iter < strlen(string); iter++) {
        if (buffer[iter] == string[iter]) argument = argument & true;
        else argument = argument & false;
    }
    return argument;
}

/* Function for 
   determining the filled buffer size */
size_t buffer_size(char* buffer) {
    size_t size = 0;
    for (unsigned int iter = 0; iter < BUFFER_SIZE; iter++) {
        if (buffer[iter] != '\0') size++;
        else return size - 1;
    }
    return size;
}