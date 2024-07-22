!#/bin/bash
g++ -DNDEBUG -std=c++17 -Wall -pedantic-errors -Werror -o HW3  main.cpp Person.cpp Task.cpp TaskManager.cpp
valgrind --leak-check=full  --show-leak-kinds=all -s ./HW3 1 >./tests/test1.out
valgrind --leak-check=full  --show-leak-kinds=all -s ./HW3 2 >./tests/test2.out
valgrind --leak-check=full  --show-leak-kinds=all -s ./HW3 3 >./tests/test3.out
valgrind --leak-check=full  --show-leak-kinds=all -s ./HW3 4 >./tests/test4.out
valgrind --leak-check=full  --show-leak-kinds=all -s ./HW3 5 >./tests/test5.out
valgrind --leak-check=full  --show-leak-kinds=all -s ./HW3 6 >./tests/test6.out
cd ./tests
diff --strip-trailing-cr -B -Z test1.out test1.expected
diff --strip-trailing-cr -B -Z test2.out test2.expected
diff --strip-trailing-cr -B -Z test3.out test3.expected
diff --strip-trailing-cr -B -Z test4.out test4.expected
diff --strip-trailing-cr -B -Z test5.out test5.expected
diff --strip-trailing-cr -B -Z test6.out test6.expected
