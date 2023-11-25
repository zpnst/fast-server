
# include <memory>
# include <cstdint>
# include <iostream>


/* A class that describes a doubly linked list 
   that helps to get rid of collisions in a hash table */

# pragma once 

template <typename PointerType>
using SP = std::shared_ptr<PointerType>;

template <typename KeyType, typename ValueType>
class list final 
{   
    /* Instance formation */
    struct ListNode
    {   
        KeyType Key;
        ValueType Value;
        SP<ListNode> Next = nullptr;
        SP<ListNode> Previous = nullptr;
    };

    SP<ListNode> Tail = nullptr;
    SP<ListNode> Muzzle = nullptr;

    /* Auxiliary method for the bool 
       method if_value_in_hash(ValueType value) noexcept */
    bool contains(ValueType& CurrentValue, ValueType& Value) noexcept {

        unsigned int jter = 0;
        std::size_t counter = 0;
        for (unsigned int iter = 0; iter < CurrentValue.size(); iter++) 
        {
            while (true) {
                if (jter >=  Value.size()) break;
                if (CurrentValue[iter] == Value[jter]) {
                    counter++;
                    break;
                }
                jter++;
            }
            jter = 0;
        }
        if (counter == Value.size()) return true;
        return false;
    }

    public:
            
        list(void) = default;

        /* Custom destructor that allows you to get rid 
           of looped links without using std::weak_ptr<Type> */
        ~list(void) noexcept {

            SP<ListNode> CurrentNode = Muzzle;

            if (not CurrentNode) return;

            while (CurrentNode -> Next) {
                CurrentNode = CurrentNode -> Next;
                CurrentNode -> Previous.~shared_ptr();
            }
        };

        /* Method for inserting a new node 
           at the end of a doubly linked list */
        void push_entry(const KeyType& key, const ValueType& value) noexcept {

            SP<ListNode> NewNode = std::make_shared<ListNode>();

            NewNode -> Key = key;
            NewNode -> Value = value;
            NewNode -> Next = nullptr;
            NewNode -> Previous = nullptr;

            if (not Muzzle) [[ unlikely ]] {
                Muzzle = NewNode;
                Tail = NewNode;
                return;
            }

            SP<ListNode> CurrentNode = Muzzle;
            while (CurrentNode) {

                if (CurrentNode -> Key == key) [[ unlikely ]] {
                    CurrentNode -> Value = value;
                    return;
                }
                CurrentNode = CurrentNode -> Next;
            }

            if (Tail) {
                Tail -> Next = NewNode;
                NewNode -> Previous = CurrentNode;
                Tail = NewNode;
            }
        }

        /* Method for deleting a node of 
           a doubly linked list by a given key */
        void erase_entry(const KeyType key) {

            if (not Muzzle) 
                throw std::logic_error("ATTENTION -> There are no entries in the table!");

            SP<ListNode> TrashNode = nullptr;
            SP<ListNode> CurrentNode = Muzzle;

            while (CurrentNode) {

                if (CurrentNode -> Key == key) [[ likely ]] {
                    TrashNode = CurrentNode;
                    break;
                }
                CurrentNode = CurrentNode -> Next;
            }
            
            if (TrashNode == Muzzle) [[ likely ]] {
                Muzzle = TrashNode -> Next;
                return;
            }

            if (not TrashNode -> Next) {
                TrashNode -> Previous -> Next = nullptr;
                Tail = TrashNode -> Previous;

                return;
            }

            TrashNode -> Previous -> Next = TrashNode -> Next;
            TrashNode -> Next -> Previous = TrashNode -> Previous;
        }

        /* Method for formatted output of a 
           doubly linked list nodes to a terminal */
        void print_formatted_list() const noexcept {

            SP<ListNode> CurrentNode = Muzzle;
            while (CurrentNode) {

                std::cout << "(" << "NAME: " << CurrentNode -> Key << " | MESSAGES: ";
                for (std::uint64_t iteration = 0; iteration < (CurrentNode -> Value).size(); iteration++) {
                    if (iteration == (CurrentNode -> Value).size() - 1)
                        std::cout << iteration+1 << ")-> " << (CurrentNode -> Value)[iteration] << "";
                    else
                        std::cout << iteration+1 << ")-> " << (CurrentNode -> Value)[iteration] << " ";
                }

                if (CurrentNode -> Next) std::cout << ") --> ";
                else std::cout << ")";
                

                
                CurrentNode = CurrentNode -> Next;
            }
        }

        /* A method that checks whether a given value 
           exists in any of the nodes of a doubly linked list */
        bool if_value_in_hash(ValueType value) noexcept {

            SP<ListNode> CurrentNode = Muzzle;

            while (CurrentNode) {
                if (contains(CurrentNode -> Value, value)) return true;
                CurrentNode = CurrentNode -> Next;
            }
            return false;
        }

        /* A method that checks whether a given key 
           exists in any of the nodes of a doubly linked list */
        bool if_key_in_hash(KeyType key) noexcept {
            
            SP<ListNode> CurrentNode = Muzzle;

            while (CurrentNode) {
                if (CurrentNode -> Key == key) return true;
                CurrentNode = CurrentNode -> Next;
            }
            return false;
        }

        /* Operator [] overloading */
        ValueType& operator [] (const KeyType key) noexcept {
            
            SP<ListNode> CurrentNode = Muzzle;
            while (CurrentNode) {
                if (CurrentNode -> Key == key) return CurrentNode -> Value;
                CurrentNode = CurrentNode -> Next;
            }
            std::cout << "ATTENTION -> There is no such key in the table: " << key << std::endl;

            /* If no value is found, the 
               null std::vector<Type> is returned */
            static ValueType emptyVector;
            return emptyVector;
        }
        
        /* A method that determines whether a doubly linked 
           list exists (whether there is at least one node in it) */
        bool exists() const noexcept {
            return Muzzle != nullptr;
        }
};
