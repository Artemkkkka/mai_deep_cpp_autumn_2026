#include <cstddef>
#include <iostream>

class Allocator {
public:
    Allocator()
    {
        this->memory = nullptr;
        this->offset = 0;
        this->capacity = 0;

   
    }

    ~Allocator()
    {
        delete[] this->memory;   
    }

    Allocator(const Allocator&) = delete;
    Allocator& operator=(const Allocator&) = delete;

    void makeAllocator(std::size_t maxSize) {
        delete[] this->memory;              
        this->memory = new char[maxSize];   
        this->capacity = maxSize;           
        this->offset = 0;                   
    }

    char* alloc(std::size_t size) {
        if (this->memory == nullptr) {
            return nullptr;            
        }
        if (this->offset + size > this->capacity) {
            return nullptr;           
        }

        char* result = this->memory + this->offset;   
        this->offset += size;                    
        return result;                      
    }

    void reset() {
        this->offset = 0;
    }

private:
    char* memory; 
    std::size_t offset;               
    std::size_t capacity;    
};