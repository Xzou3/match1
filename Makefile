all:        main

match:
        gcc -Wall -std=c99 -o match match.c

cuda:
        nvcc -arch=sm_20 -o cuda match.cu


clean:
        rm match
