#include <iostream>
#include <vector>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;

    size_t n = s.length();
    std::vector<int> pi(n, 0);

    for (size_t i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        pi[i] = j;
    }

    int last_pi = pi[n - 1];
    int period_len = static_cast<int>(n) - last_pi;

    if (n % period_len == 0) {
        std::cout << n / period_len << '\n';
    } else {
        std::cout << 1 << '\n';
    }

    return 0;
}