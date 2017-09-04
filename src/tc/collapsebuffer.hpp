#ifndef COLLAPSEBUFFER
#define COLLAPSEBUFFER

#include "gamedefs.h"

#include <stdint.h>

namespace tc {
    struct CollapseBuffer {
    public:
        // Typedefs
        typedef int8_t value_type;
        typedef uint8_t _size_t;
        typedef value_type const& const_reference;
        typedef value_type* iterator;
        typedef value_type const* const_iterator;

    private:
        // Constants
        static _size_t const CAPACITY = GameDefs::MAX_COLLAPSE;
        static_assert(CAPACITY < 256, "Max block count is larger than vector counter max");

        // Members
        value_type data[CAPACITY];
        _size_t num_elements;

    public:
        // Constructors
        CollapseBuffer() : num_elements(0) {}

        // Methods
        bool empty() const { return this->num_elements == 0; }
        void push_back(const_reference new_element) {
            *(this->end()) = new_element;
            this->num_elements++;
        }

        // Operators
        const_reference operator[](_size_t const i) { return this->data[i]; }

        // Ranged-for
        iterator begin() { return static_cast<iterator>(this->data); }
        iterator end()   { return this->begin() + this->num_elements; }

        const_iterator begin() const { return static_cast<const_iterator>(this->data); }
        const_iterator end()   const { return this->begin() + this->num_elements; }
    };
}

#endif
