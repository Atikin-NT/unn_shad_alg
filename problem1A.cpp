#include <iostream>

int main()
{
    size_t n;
    std::cin >> n;
    int *data = new int[n];
    for (size_t i = 0; i < n; ++i)
    {
        std::cin >> data[i];
    }
    std::cout << data[n] << "\n";
    delete[] data;
    return 0;
}
