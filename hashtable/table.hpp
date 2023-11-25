
# include "box.hpp"
# include <cstdint>
# include "list.hpp"
# include <iostream>

# define TABLE_SIZE 10000000


/* A class that describes a hash 
   table that accepts data from the server */

# pragma once

template <typename KeyType, typename ValueType>
class HashTable final 
{   

    /* Instance formation */
    std::size_t Fullness = 0;
    std::hash<KeyType> hasher;

    /* Creating a hash table skeleton using the Box class */
    box<list<KeyType, ValueType>> Entries = box<list<KeyType, ValueType>>(TABLE_SIZE);
    
    public: 

        HashTable(void) = default;
        ~HashTable(void) = default;

        /* Method for adding 
           a new entry to a hash table */
        HashTable& push(KeyType key, ValueType value) noexcept {

            std::size_t hash = hasher(key) % TABLE_SIZE;
            Entries[hash].push_entry(key, value);
            Fullness += 1;

            return *this;
        }
        
        /* Method for deleting 
           an entry from a hash table */
        HashTable& erase(KeyType key) noexcept {

            std::size_t hash = hasher(key) % TABLE_SIZE;
            Entries[hash].erase_entry(key);
            Fullness -= 1;
            
            return *this;
        }

        /* Method for formatted output of 
           all hash table entries to the terminal */
        HashTable& print_formatted_table() noexcept {

            for (std::uint64_t iteration = 0; iteration < TABLE_SIZE; iteration++) {

                if (Entries[iteration].exists()) {
                    std::cout << "hash [" << iteration << "] nodes: --> ";
                    Entries[iteration].print_formatted_list();
                    std::cout << std::endl; 
                }
            }
            return *this;
        }
        
        /* Method for searching entries by values */
        HashTable& get_entries_by_values(ValueType value) noexcept {
            
            bool flag = false;
            for (std::uint64_t iteration = 0; iteration < TABLE_SIZE; iteration++) {
                if (Entries[iteration].exists() && Entries[iteration].if_value_in_hash(value)) {

                        std::cout << "hash [" << iteration << "] nodes: --> ";
                        Entries[iteration].print_formatted_list();
                        std::cout << std::endl; 
                        flag = flag || true;
                }
            }
            if (!flag) {
                std::cout << "ATTENTION -> There is no such values in the table: ";
                for (std::uint64_t iteration = 0; iteration < value.size(); iteration++) {
                    if (iteration < value.size() - 1) std::cout << value[iteration] << ", ";
                    else std::cout << value[iteration];
                }
                std::cout << std::endl;
            }
            return *this;
        }

        /* Method for searching entries by keys */
        HashTable& get_entries_by_key(KeyType key) noexcept {
            
            bool flag = false;
            for (std::uint64_t iteration = 0; iteration < TABLE_SIZE; iteration++) {
                if (Entries[iteration].exists() && Entries[iteration].if_key_in_hash(key)) {

                        std::cout << "hash [" << iteration << "] nodes: --> ";
                        Entries[iteration].print_formatted_list();
                        std::cout << std::endl; 
                        flag = flag || true;
                }
            }
    
            if (!flag)
                std::cout << "ATTENTION -> There is no such key in the table: " << key << std::endl;
            return *this;
        }

        /* Operator [] overloading */
        [[nodiscard]] ValueType operator [] (KeyType key) {

            std::size_t hash = hasher(key)  % TABLE_SIZE;
            return Entries[hash][key];
        }

        /* Hash table size */
        std::size_t size() const noexcept {
            return TABLE_SIZE; 
        }

        /* The fullness of the hash table */
        std::size_t fullness() const noexcept {
            return Fullness;
        }
};