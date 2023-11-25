
# include <iostream>
# include <hs/connection/uclient.hpp>


/* The simplest class 
   describing the client */

class client final {

    public: 

        /* The client starts the transfer 
           immediately in the class constructor */
        client(void) {
            run_client();
        }
        ~client(void) = default;
};