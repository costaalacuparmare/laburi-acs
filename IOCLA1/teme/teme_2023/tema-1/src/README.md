CONSTANTINESCU Vlad 314CB

This is a short explanation of the content of the archive and my implementation

1. CONTENTS:


    - main.c : Initializations and calls of functions
    - functions.c : Implementation functions, commands functions and auxiliary functions
    - functions.h : MACROS, used libraries, headers for functions in function.c and for one
    given function in the next file
    - operations.c : operations functions (given) and the functions to create an array of 
    function pointers
    - structs.h : the structures used for the sensors and the array of sensors

2. IMPLEMENTATION:


    - I preferred to use separate functions for initialization, reading from 
    the input binary file, reading commands from keyboard and freeing the memory
    because of good practises and clarity.
    - For the commands I used basic conditional blocks and loop blocks, in order to keep the
    implementation as simple as possible