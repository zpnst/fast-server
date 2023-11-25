# Hashing Sockets

## Structure

    This is a client-server application in which the hash table acts as a server buffer.                                                                                                                  
    To deal with collisions inside the hash table, a doubly linked list was chosen.
    
## Customers Window

    Here you can see the consistent interaction of clients with the server.                                                                                                                               
    To finish working with the server, the client must write %stop.                                                                                                                                       
    The client can also end the server session by writing %shutdown.                                                                                                                                      
  
  ![image](https://github.com/zpnst/hashing-sockets/assets/105946529/6a136c20-53f1-431d-925a-cf11032d267e)

    In this example, a client named Incognito ended the server session by writing %shutdown.

## Server Window

  Here we can see the output of the program company.cpp
  
  ![image](https://github.com/zpnst/hashing-sockets/assets/105946529/42b8bc5b-5347-4490-8ec9-b790e3141047)

    First, all records of the server buffer (hash table) were shown.                                                                                                                                      
    Next, a search was made for a client who would write these messages in one session: Hello, World, UNIX                                                                                                
    At the end, the client was searched by name Linus Torvalds.                                                                                                                                           

## Thanks for reading!!!

  
