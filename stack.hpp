//
// Created by barsela on 4/19/22.
//
#include <unistd.h>
#include <sys/mman.h>

#ifndef EX4_STACK_HPP
#define EX4_STACK_HPP

struct dataBlock {
    struct dataBlock *next;
    int free;
    size_t size;
};
typedef struct Node {
    char str[1024];
}node;

void push(char* str_input,int len);
void pop();
char* top();




#endif //EX4_STACK_HPP