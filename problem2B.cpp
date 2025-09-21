#include <iostream>

int main(int argc, char **argv)
{
    int a = std::stoi(argv[1]),
        b = std::stoi(argv[2]);

    std::cout << "Number of input args: " << argc << "\n";
    std::cout << "a is : " << a << "\n"
              << "b is : " << b << "\n"
              << "(a + b) is : " << a + b << std::endl;
    return 0;
}