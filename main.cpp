#include <iostream>

// UNCOMMENT!
//to run one of the tasks

#define RUN_TRIANGLE
//#define RUN_SQUARE
//#define RUN_TASK2_PART1
//#define RUN_TASK2_PART2

#ifdef RUN_TRIANGLE
int triangle_main();
int main() { return triangle_main(); }
#endif

#ifdef RUN_SQUARE
int square_main();
int main() { return square_main(); }
#endif

#ifdef RUN_TASK2_PART1
int part1_main();
int main() { return part1_main(); }
#endif

#ifdef RUN_TASK2_PART2
int part2_main();
int main() { return part2_main(); }
#endif

// If no task is selected:
#if !defined(RUN_TRIANGLE) && !defined(RUN_SQUARE) && !defined(RUN_TASK2_PART1) && !defined(RUN_TASK2_PART2)
int main() {
    std::cout << "Please uncomment a task in main.cpp!" << std::endl;
    std::cout << "Available options:" << std::endl;
    std::cout << "  #define RUN_TRIANGLE     - red triangle" << std::endl;
    std::cout << "  #define RUN_SQUARE       - blue square" << std::endl;
    std::cout << "  #define RUN_TASK2_PART1  - four shapes" << std::endl;
    std::cout << "  #define RUN_TASK2_PART2  - creative shapes" << std::endl;
    return 0;
}
#endif