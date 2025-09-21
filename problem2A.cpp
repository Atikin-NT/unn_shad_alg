#include <iostream>

int main(int, char **)
{
    size_t n;
    std::cin >> n;
    int *data = new int[n];
    for (size_t i = 0; i < n; ++i)
    {
        std::cin >> data[i];
    }
    return 0;
}