
# include <vector>
# include <cstdint>
# include <hs/connection/usources.hpp>
# include <hs/hashtable/table.hpp>


/* Function describing 
   the operation of the server */

# pragma once

template <typename HashTable>
HashTable& run_server(HashTable& table) {

    /* Variables for working with the return 
       values of wrapper functions of system calls */
    size_t message_size;
    ssize_t read_lenght;

    /* Defining the 
       server buffer */
    char server_buffer[BUFFER_SIZE];

    /* Definition of a standard structure 
       intended for storing a UNIX domain socket */
    struct sockaddr_un server_address;

    /* Other auxiliary objects */
    std::vector<std::string> runtime_buffer;
    std::string cpp_client_name;
    std::size_t messages_number = 0;
    
    # if SYSTEN_INFORMATION
        std::cout << "Server Proccess PID: " << getpid() << "\n";
    # endif

    /* Creating a listening server socket */
    int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) throw std::runtime_error("server_socket");
    
    /* Deleting a socket from the \tmp 
       directory if it was used earlier on this system */
    if (remove(SOCKET_ADDRESS) == - 1 && errno != ENOENT) throw std::runtime_error("remove");

    /* Cleaning and filling the 
       structure that stores the socket */
    memset(&server_address, 0, sizeof(struct sockaddr_un));
    server_address.sun_family = AF_UNIX;
    strncpy(server_address.sun_path, SOCKET_ADDRESS, sizeof(server_address.sun_path) - 1);

    /* Binding a socket 
       to a given address (file path) */
    if (bind(server_fd, (struct sockaddr*) &server_address, sizeof(struct sockaddr_un)) == -1)
        throw std::runtime_error("bind");
    
    /* We make the stream socket pointed to by the server_fd file descriptor passive. 
       Subsequently, this socket will be used to receive connections from other (active) sockets */
    if (listen(server_fd, BACKLOG) == -1) throw std::runtime_error("listen");

    while(true) {
        
        /* Saving data from 
           a specific client */
        if (messages_number != 0) {
            table.push(cpp_client_name, runtime_buffer);
            runtime_buffer.clear();
        }
        
        messages_number = 0;
        memset(server_buffer, 0, BUFFER_SIZE);

        /* Accepts a connection to a listening 
           stream socket pointed to by the client_fd file descriptor */
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd == -1) throw std::runtime_error("accept");

        /* Reading the information 
           received from the client from the socket */
        while ((read_lenght = read(client_fd, server_buffer, BUFFER_SIZE)) > 0) {

            /* A condition that checks whether 
               the client has suspended the server operation */
            if (terminator(server_buffer, KILL_CONNECTION)) {
               table.push(cpp_client_name, runtime_buffer);
               return table;

            }
            else {

                /* A condition that checks whether 
                   the client has finished working with the service */
                if (!terminator(server_buffer, TERMINATOR)) {
                    if (messages_number == 0) {
                        
                        /* Buffering the client name */
                        message_size = buffer_size(server_buffer);
                        cpp_client_name = std::string(server_buffer, message_size);
                        memset(server_buffer, 0, BUFFER_SIZE);

                    }
                    if (messages_number++ >= 1) {

                        /* Adding a client message to runtime_buffer */
                        message_size = buffer_size(server_buffer);
                        std::string cpp_message = std::string(server_buffer, message_size);
                        runtime_buffer.push_back(cpp_message);
                        memset(server_buffer, 0, BUFFER_SIZE);
                    }
                }
            }  
        }
    }
}