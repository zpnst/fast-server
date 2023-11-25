
# include <iostream>
# include "tools/server.hpp"


int main(int argc, char** argv) {

    /* Enabling a listening server 
       that is waiting for a connection */
    server serv;

    /* Printing all records 
       from the server buffer */
    serv.records();
    std::cout << std::endl;

    /* Printing records from the 
       server buffer that contain certain messages */
    serv.serach_by_messages("Hello", "World", "UNIX");
    std::cout << std::endl;
    
    /* Printing a record from the buffer 
       from a specific client, received by name */
    serv.serach_by_name("Linus Torvalds");

    return 0;
}
