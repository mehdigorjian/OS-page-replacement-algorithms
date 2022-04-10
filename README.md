# OS-page-replacement-algorithms
Page replacement algorithms simulation in operating system

This program simulates a paging system. At the start of the program the user will be prompted to choose a page replacement algorithm choosing from FIFO, LRU or second chance. On each cycle, the code reads the number of the referenced page from a file. The output showing: reference string, the 4 pages of memory each displaying the page number loaded in memory and the 4 pages most recently removed from memory and whether a page fault has occurred.

Under the reference string, the program displays 25 columns of 8 items each. The first column is empty, reflecting the memory state before execution begins. As each page in the reference string is loaded into memory, the state of memory as each page is loaded and removed is displayed.

The reference string consist of 24 page numbers space delimited as follows: 0 2 1 3 5 4 6 3 7 4 7 3 3 5 5 3 1 1 1 7 2 3 4 1


COMPILATION: gcc page_replace_algo.cpp -o page_replace_algo -lstdc++
        RUN: ./page_replace_algo
