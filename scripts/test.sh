!#/bin/bash
g++ -DNDEBUG -std=c++17 -Wall -pedantic-errors -Werror -o HW3 ourTest.cpp
valgrind --leak-check=full -s ./HW3
