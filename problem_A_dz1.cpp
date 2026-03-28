#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> z_function(const std::string& s) {
    int n = s.length();
    std::vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string p, t;
    std::cin >> p >> t;

    int n = p.length();
    int m = t.length();

    if (n > m) {
        std::cout << 0 << "\n\n";
        return 0;
    }

    std::vector<int> z1 = z_function(p + "#" + t);
    std::reverse(p.begin(), p.end());
    std::reverse(t.begin(), t.end());
    std::vector<int> z2 = z_function(p + "#" + t);

    std::vector<int> result;
    for (int i = 0; i <= m - n; ++i) {
        int prefix_match = z1[n + 1 + i];
        int suffix_match = z2[n + 1 + (m - n - i)];
        
        if (prefix_match + suffix_match >= n - 1) {
            result.push_back(i + 1);
        }
    }

    std::cout << result.size() << "\n";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << result[i] << (i == result.size() - 1 ? "" : " ");
    }
    std::cout << "\n";

    return 0;
}