#include <string.h>
#include "stack.hpp"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#define THOUSEND 1000

//the malloc inspired by https://danluu.com/malloc-tutorial/

node* common= (node *)mmap ( NULL, sizeof(THOUSEND*sizeof(node)),
                                 PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0 );

int * dex= (int*)mmap ( NULL, sizeof(int),
                             PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0 );

struct dataBlock* head = NULL;
struct dataBlock *serchBlock(struct dataBlock **last, size_t size) {
    struct dataBlock *current = head;
    while (current && (current->free == 0  || current->size < size)) {
        *last = current;
        current = current->next;
    }
    return current;    //// last ends pointing to the 'block meta' of the last memory allocation if cuurent is null
}

struct dataBlock *createMemory(struct dataBlock* last, size_t size) {
    struct dataBlock *block;
    block = (dataBlock*)mmap( NULL, size,
                              PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 ); // points to current creak adress and later points to the start of the new allocated memory , beacuse of the // casting block points to tnly the sizeof(block meta) first bytes of the memory allocated
    if (last!=NULL) { // NULL on first request.
        last->next = block;   /// next points to the start of the memory block
        block->size = size;
        block->next = NULL;
        block->free = 0;
    }
    if(block == MAP_FAILED){
        printf("Mapping Failed\n");
    }
    return block;
}


void *malloc(size_t size) {
    struct dataBlock *block;
    if (size <= 0) {
        return NULL;
    }
    else {
        struct dataBlock *lastElement = head;
        block = serchBlock(&lastElement, size);  // noticed we change where lastElement points to beacuse we past &lastElement and not lastElement
        if (!block) { // Failed to find free block - block poins to Null and lastElement points to the lastElement block meta of the lastElement allocation
            block = createMemory(lastElement, size); // pointer to the new memory block
            if (!block) {
                return NULL;
            }
        } else {      // Found free block
            block->free = 0;
        }
    }
    if (!head) { // there is noting insdie the linkidlist
        block = createMemory(NULL, size);
        if (!block) {
            return NULL;
        }
        head = block;
    }
    block++;
    return(block);  // we want to skip the 'sizeof(block meta) first bytes' and return the adress of the begining of the allocated memory
}

// explenation : ask the mount of bytes we need for dynemick aloocation and after we get get that memory by the malloc function , bzero all the bytes
void *calloc(size_t blocksNumber, size_t bytesEachBlock) {
    size_t size = blocksNumber * bytesEachBlock;
    void *ptr = malloc(size);
    bzero(ptr,size);
    return ptr;
}

void free(void *ptr) {
    if (!ptr) {
        return;
    }
    struct dataBlock* block_ptr = (struct dataBlock*)ptr;  /// go to the block meta - the data of the memory aloocated that we want to free
    block_ptr--;
    block_ptr->free = 1;// decleare the memory allocated is free to use for other works.
}






//##############
    void push(char *str_input,int len){
        strncpy(common[*dex].str, str_input,len);
        common[*dex].str[len] = '\0';
        fflush(stdout);
        (*dex)++;
}
    void pop() {
        if ( *dex == 0 )
            return;
        else {
            memset(common[*dex].str,'\0',1024);
            (*dex)-- ;
        }
    }
    char *top() {
        if ( *dex == 0 )
            return NULL;
        int last = *dex -1 ;
        return common[last].str;
    }

