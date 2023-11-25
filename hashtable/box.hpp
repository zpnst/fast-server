
# include <cstdint>
# include <iostream>


/* A class that describes a regular dynamic 
   array that is the foundation for a hash table */

# pragma once

template <typename BoxType>
class box final 
{   
    /* Instance formation */
    std::size_t Size = 0;
    BoxType* Box = nullptr;

    public:

        box(void) = delete;

        /* Custom constructor */
        box(std::uint64_t Size) {
            
            Box = static_cast<BoxType*>(new BoxType[Size]);
            if (Box == nullptr) throw std::bad_alloc();
            this -> Size = Size;
        };

        /* Custom destructor */
        ~box(void) {
            delete[] Box;
        };

        /* Operator [] overloading */
        BoxType& operator[] (std::uint64_t index) const {
            if (index >= Size) 
                throw std::out_of_range("ATTENTION -> Box index out of range!");
            return Box[index];
        }
        
        /* Dynamic array Size */
        std::size_t size() const noexcept {
            return Size;
        }
};