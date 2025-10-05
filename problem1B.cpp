#include <iostream>
#include <string>
#include <vector>

struct Queue {
    std::vector<int> data;

    void enqueue(int value) {
        data.push_back(value);
    }

    int dequeue(int value) {
        if (data.size() == 0)
            return 0;

        int val = data.back();

        if (val != value)
        {
            return data.size();
        }

        data.erase(data.end());
        return -1;
    }
};




int main()
{
    std::ios_base::sync_with_stdio(false);
    std::string str;
    getline(std::cin, str);
    // ( - 0, { - 1, [ - 2

    Queue q;
    int res = 0;
    int index = 0;

    for (char c: str) {
        switch (c)
        {
            case '(':
                q.enqueue(0);
                break;
            case ')':
                res = q.dequeue(0);
                if (res != -1) {
                    std::cout << index;
                    return 0;
                }
                break;
            case '{':
                q.enqueue(1);
                break;
            case '}':
                res = q.dequeue(1);
                if (res != -1) {
                    std::cout << index;
                    return 0;
                }
                break;
            case '[':
                q.enqueue(2);
                break;
            case ']':
                res = q.dequeue(2);
                if (res != -1) {
                    std::cout << index;
                    return 0;
                }
                break;
            default:
                break;
        }
        index += 1;
    }
    if (q.data.size() != 0) {
        std::cout << index;
        return 0;
    }
    std::cout << "CORRECT";

    return 0;
}
