#ifndef BLOCKVECTOR
#define BLOCKVECTOR

#include "gamedefs.h"
#include "block.hpp"
#include "collapsebuffer.hpp"

#include <stdint.h> // avr-gcc can't into cstdint

namespace tc {
    struct BlockVector {
    public:
        // Typedef
        typedef Block value_type;
        typedef uint16_t _size_t;
        typedef value_type& reference;
        typedef value_type const& const_reference;
        typedef value_type* iterator;
        typedef value_type const* const_iterator;

    private:
        // Constants
        static _size_t const CAPACITY = (GameDefs::WIDTH * GameDefs::HEIGHT)/2;
        static_assert(CAPACITY <= 65536, "Max block count is larger than BlockVector::_size_t");

        // Members
        value_type data[CAPACITY];
        _size_t num_elements;
        
        // Methods
        void shrink();

    public:
        // Constructors
        BlockVector() : num_elements(0) {}
        
        // Methods
        _size_t size() const { return this->num_elements; }
        
        void push_back(const_reference new_block) {
            *(this->end()) = new_block;
            this->num_elements++;
        }
        void collapse(CollapseBuffer const&);
        
        // Operators
        reference operator[](_size_t const i) { return this->data[i]; }
        const_reference operator[](_size_t const i) const { return this->data[i]; }

        // Ranged-for interface
        iterator begin() { return static_cast<iterator>(this->data); }
        iterator end()   { return this->begin() + this->num_elements; }

        const_iterator begin() const { return static_cast<const_iterator>(this->data); }
        const_iterator end()   const { return this->begin() + this->num_elements; }
    };
}

#endif
