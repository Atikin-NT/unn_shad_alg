#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<int> buildSA(const std::string& s) {
    int n = s.length();
    std::vector<int> sa(n), r(n), tmp(n);
    for (int i = 0; i < n; i++) sa[i] = i, r[i] = s[i];
    
    for (int k = 1; k < n; k <<= 1) {
        auto cmp = [&](int i, int j) {
            if (r[i] != r[j]) return r[i] < r[j];
            int ri = i + k < n ? r[i + k] : -1;
            int rj = j + k < n ? r[j + k] : -1;
            return ri < rj;
        };
        std::sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i-1]] + cmp(sa[i-1], sa[i]);
        r = tmp;
    }
    return sa;
}

std::vector<int> buildLCP(const std::string& s, const std::vector<int>& sa) {
    int n = s.length();
    std::vector<int> rank(n), lcp(n, 0);
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) { k = 0; continue; }
        int j = sa[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[rank[i]] = k;
        if (k) k--;
    }
    return lcp;
}

std::string solve() {
    std::string s;
    std::cin >> s;
    int n = s.length();
    auto sa = buildSA(s);
    auto lcp = buildLCP(s, sa);

    std::string best_s = "";
    
    int low = 1, high = n / 3;
    while (low <= high) {
        int L = low + (high - low) / 2;
        bool found = false;
        std::string current_candidate = "";

        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n - 1 && lcp[j] >= L) j++;
            
            if (j > i) {
                std::vector<int> positions;
                for (int k = i; k <= j; k++) positions.push_back(sa[k]);
                std::sort(positions.begin(), positions.end());

                int count = 1;
                int last = positions[0];
                for (size_t k = 1; k < positions.size(); k++) {
                    if (positions[k] >= last + L) {
                        count++;
                        last = positions[k];
                    }
                }
                if (count >= 3) {
                    found = true;
                    current_candidate = s.substr(positions[0], L);
                    break;
                }
            }
            i = j + 1;
        }

        if (found) {
            best_s = current_candidate;
            low = L + 1;
        } else {
            high = L - 1;
        }
    }
    return best_s;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << solve() << std::endl;
    return 0;
}