
# include <hs/connection/usources.hpp>


/* A function 
   describing \the client's work */

# pragma once

void run_client() {

    ssize_t read_lenght;

    /* Defining the 
       client buffer */
    char client_buffer[BUFFER_SIZE];

    /* Definition of a standard structure 
       intended for storing a UNIX domain socket */
    struct sockaddr_un client_address;

    std::size_t messages_number = 0;
    
    # if SYSTEN_INFORMATION
        std::cout << "Client Proccess PID: " << getpid() << "\n";
    # endif

    /* Creating a client socket */
    int client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd == -1) throw std::runtime_error("client_socket");

    /* Cleaning and filling the 
       structure that stores the socket */
    memset(&client_address, 0, sizeof(struct sockaddr_un));
    client_address.sun_family = AF_UNIX;
    strncpy(client_address.sun_path, SOCKET_ADDRESS, sizeof(client_address.sun_path) - 1);

    /* Connecting the active socket to 
       the listening server socket at the specified address */
    if (connect(client_fd, (struct sockaddr*) &client_address, sizeof(struct sockaddr_un)) == -1)
        throw std::runtime_error("connect");

    while (true) {

        /* A condition that checks whether 
           the client has finished working with the service */
        if (terminator(client_buffer, TERMINATOR) || terminator(client_buffer, KILL_CONNECTION)) {
            if (close(client_fd) == -1) throw std::runtime_error("closing client_fd");
            std::cout << "\nClient session was terminated...";
            return ;
        }
        else {

            /* Writing the information received from the client to the client 
               socket so that the server connected to it can receive and process this information */
            if (messages_number == 0) std::cout << "Client, please, enter your name: \n";
            read_lenght = read(STDIN_FILENO, client_buffer, BUFFER_SIZE);
            write(client_fd, client_buffer, read_lenght);
            if (messages_number++ == 0) std::cout << "\n";
        }
    }
}