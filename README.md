# Fast Server

## Structure

  This is a client-server application in which the hash table acts as a server buffer.                                                                                                                    
  To deal with collisions inside the hash table, a doubly linked list was chosen.                                                                                                                      
  
## Customers Window

  Here you can see the consistent interaction of clients with the server.                                                                                                                                 
  To finish working with the server, the client must write %stop.                                                                                                                                         
  The client can also end the server session by writing %shutdown.                                                                                                                                      
  ![image](https://github.com/zpnst/fast-server/assets/105946529/6c24232f-2d12-4023-bd0e-b74542e62c80)


  In this example, a client named Incognito ended the server session by writing %shutdown.

## Server Window

  Here we can see the output of the program company.cpp

  ![image](https://github.com/zpnst/fast-server/assets/105946529/e86208ec-a1d2-4895-bc49-db855d0cb4dd)
  ![image](https://github.com/zpnst/fast-server/assets/105946529/78feff72-94aa-4ce2-8da3-803b3c3938c7)

  First, all records of the server buffer (hash table) were shown.                                                                                                                                        
  Next, a search was made for a client who would write these messages in one session: Hello, World, UNIX                                                                                                  
  At the end, the client was searched by name Linus Torvalds.                                                                                                                                           

## Thanks for reading!!!

  
