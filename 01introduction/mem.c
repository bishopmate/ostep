#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h> // explicit for assert() prototype; avoids implicit declaration
#include "common.h"

/*
1. The Expectation (The Book)
In Operating Systems: Three Easy Pieces, the author (Remzi) disables a specific security feature to demonstrate the concept of Virtual Memory.
The Concept: The OS tricks every process into thinking it starts at the same virtual memory address (e.g., 0x200000). This is the "illusion" of virtualization.
The Book's Output: In the book example, Process A and Process B both print the same address (e.g., 0x200000).
2. The Reality (our Docker Container)
Our Docker container is running a modern version of Ubuntu with a security feature called ASLR (Address Space Layout Randomization) enabled by default.
The Feature: ASLR randomizes the starting memory location of the heap and stack every time you run a program.
This prevents hackers from guessing memory addresses to exploit our system.
Our Output: When you run ./mem & ./mem, Process A gets address 0x...A and Process B gets address 0x...B. They are different.

Why is this happening?
The book intentionally turns off ASLR to make the point that logically processes are isolated copies of each other.
Our Docker container has ASLR turned on for security.

How to reproduce the Book's output?
You can disable ASLR for a specific command without changing your global Docker settings (which often requires privileged access).
Use the setarch command with the -R flag (disable randomization):
setarch $(uname -m) -R ./mem & setarch $(uname -m) -R ./mem
What this command does:
uname -m: Gets your machine architecture (e.g., x86_64).
-R: Disables address randomization (ASLR) for this command.
./mem: Runs your program.

*/

int main(int argc, char *argv[])
{
    int *p = malloc(sizeof(int));                               // stdlib.h
    assert(p != NULL);                                          // assert.h
    printf("(%d) address pointed to by p: %p \n", getpid(), p); // stdio.h + unistd.h
    *p = 0;
    while (1)
    {
        Spin(1); // common.h
        *p = *p + 1;
        printf("(%d) p: %d\n", getpid(), *p); // stdio.h + unistd.h
    }

    return 0;
}