
# include <vector>
# include <iostream>
# include <tools/hashtable/table.hpp>
# include <tools/connection/userver.hpp>


/* A class describing the server 
   and interaction with the data it receives */

class server final {

    /* Instance formation */
    std::vector<std::string> searcher;
    HashTable<std::string, std::vector<std::string>> table;

    public:

        /* The server starts waiting for a 
           connection immediately in the class constructor */
        server(void) noexcept {
            table = run_server(table);
        }
        ~server(void) = default;

        /* Method for searching for a 
           record in the server buffer by client name */
        server& serach_by_name(std::string name) noexcept {
            
            table.get_entries_by_key(name);
            return *this;
        }
        
        /* A method for searching for 
           a record in the server buffer based on client messages */
        template<typename... Args>
        server& serach_by_messages(Args... args) noexcept {
            
            (searcher.push_back(args), ...);
            table.get_entries_by_values(searcher);
            return *this;
        }

        /* Method for outputting 
           all records from the server buffer */
        server& records() noexcept {

            table.print_formatted_table();
            return *this;
        }
};