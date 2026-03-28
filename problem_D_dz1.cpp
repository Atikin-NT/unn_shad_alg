#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void build_sa(const std::string& s, std::vector<int>& sa, std::vector<int>& lcp) {
    int n = s.length();
    int alphabet = 256;
    std::vector<int> c(n), cnt(std::max(alphabet, n), 0);
    sa.resize(n);

    for (int i = 0; i < n; i++) cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) sa[--cnt[s[i]]] = i;

    c[sa[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[sa[i]] != s[sa[i - 1]]) classes++;
        c[sa[i]] = classes - 1;
    }

    std::vector<int> p_new(n), c_new(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            p_new[i] = sa[i] - (1 << h);
            if (p_new[i] < 0) p_new[i] += n;
        }

        std::fill(cnt.begin(), cnt.begin() + classes, 0);

        for (int i = 0; i < n; i++) cnt[c[p_new[i]]]++;
        for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) sa[--cnt[c[p_new[i]]]] = p_new[i];

        c_new[sa[0]] = 0;
        classes = 1;

        for (int i = 1; i < n; i++) {
            std::pair<int, int> cur = {c[sa[i]], c[(sa[i] + (1 << h)) % n]};
            std::pair<int, int> prev = {c[sa[i - 1]], c[(sa[i - 1] + (1 << h)) % n]};
            if (cur != prev) classes++;
            c_new[sa[i]] = classes - 1;
        }
        c = c_new;
    }

    lcp.assign(n, 0);
    std::vector<int> rank(n);
    
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    int k = 0;
    
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) { k = 0; continue; }
        int j = sa[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[rank[i]] = k;
        if (k) k--;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s;
    std::cin >> s;

    int n = s.length();
    std::vector<int> sa, lcp;
    build_sa(s + '$', sa, lcp);

    long long result = 0;
    for (int i = 1; i <= n; i++) {
        result += (n - sa[i]);
        if (i < n) result -= lcp[i];
    }

    std::cout << result << "\n";

    return 0;
}