#include "stack.hpp"
#include <iostream>
#include <string.h>
#include <assert.h>
#include<fcntl.h>


int main() {
    //// **** Tests without clients **** ////
    push((char*)"EDEN HAZARD", sizeof ("EDEN HAZARD"));
    push((char*)"LEO MESSI", sizeof ("LEO MESSI"));
    assert(strcmp(top(), "LEO MESSI") == 0);
    printf("TEST PASS\n");
    pop();
    assert(strcmp(top(), "EDEN HAZARD") == 0);
    printf("TEST PASS\n");
    pop();


    if (int first = fork() != 0) {
        system("./server");
    }

    sleep(1);
    if (fork() == 0) {
        push((char*)"SHON BAR SELA", sizeof("SHON BAR SELA"));
        printf("Client no.1 pushed to the stack\n");
        printf("TOP = %s\n", top());
        assert(strcmp(top(), "SHON BAR SELA\n"));
        printf("TEST PASS - TOP\n");
       // exit(0);
    }


    sleep(1);
    if (fork() == 0) {
        push((char*)"SHANI VAHAV", sizeof ("SHANI VAHAV"));
        printf("Client no.2 pushed to the stack\n");
        assert(strcmp(top(), "SHANI VAHAV\n"));
        printf("TEST PASS - TOP\n");
        exit(0);
    }

    sleep(1);

    /// *** Check the stack *** ///
    assert(strcmp(top(), "SHANI VAHAV\n"));
    pop();
    printf("TEST PASS - POP shani\n");

    assert(strcmp(top(), "SHON BAR SELA\n"));
    printf("TEST PASS shon\n");
    pop();

    sleep(1);
    exit(0);
}

