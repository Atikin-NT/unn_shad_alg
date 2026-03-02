#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<int> z_function(const std::string& s) {
    int n = static_cast<int>(s.length());
    std::vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i]++;
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;

    int n = static_cast<int>(s.length());
    int max_k = 1;

    for (int i = 0; i < n; ++i) {
        std::string suffix = s.substr(i);
        std::vector<int> z = z_function(suffix);
        int m = static_cast<int>(suffix.length());

        for (int L = 1; L < m; ++L) {
            int k = z[L] / L + 1;
            if (k > max_k) {
                max_k = k;
            }
        }
    }

    std::cout << max_k << std::endl;

    return 0;
}