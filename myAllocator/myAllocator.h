#ifndef _myAllocator_
#define _myAllocator_
#include <iostream>
#include <stdlib.h>

class myAllocator {
public:
    static myAllocator* getAllocator() {
        if(NULL == alloc) {
            // TODO::unsafe for multi-thread
            alloc = new myAllocator;
        }
        return alloc;
    }
    void* allocate(size_t n) {
        obj** i_free_list;
        obj* result;
        if(n > 128) {
            // TODO::use another way to do
            return NULL;
        }
    reAllocate:
        i_free_list = free_list + ((n + 7) / 8 - 1);
        result = *i_free_list;
        if(NULL == result) {
            // TODO:: if has no enough memory
            refill(n);
            goto reAllocate;
        }
        *i_free_list = result->next;
        std::cout << "allocate " << n << " bytes" << std:: endl;
        return result;
    }
    void deallocate(void* p, size_t n) {
        obj** i_free_list;
        obj* q = (obj*) p;

        if(n > 128) {
            // TODO::use another way to do
            return;
        }

        i_free_list = free_list + ((n + 7) / 8 - 1);
        q->next = *i_free_list;
        *i_free_list = q;
        std::cout << "deallocate " << n << " bytes" << std:: endl;
    }
private:
    myAllocator() {
        for(int i = 0; i < 16; i++) {
            free_list[i] = NULL;
        }
    }
    myAllocator(const myAllocator&);
    myAllocator& operator=(const myAllocator&);
private:
    void refill(size_t n) {
        obj **i_free_list;
        obj *temp;
        char* ifill;
        int objs = 8 + 8 * ((n + 7) / 8 - 1);
        char* fill = (char*) malloc(20 * objs);
        if(NULL == fill) {
            // TODO::
            return;
        }

        ifill = fill;
        for(int i = 0; i < 20; i++) {
            temp = (obj*) ifill;
            ifill += objs;
            (*temp).next = (obj*) ifill;
        }
        (*temp).next = NULL; 

        i_free_list = free_list + ((n + 7) / 8 - 1);
        *i_free_list = (obj*) fill;
        std::cout << "refill free_list[" << ((n + 7) / 8 - 1) << "]" << std:: endl;
    }
private:
    union obj {
        union obj* next;
        char data[1];
    };
private:
    static myAllocator* alloc;
    obj* free_list[16];
};

myAllocator* myAllocator::alloc = NULL;

#endif //_myAllocator_