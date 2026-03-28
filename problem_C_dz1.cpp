#include <iostream>
#include <cstring>

const int MAXN = 100005;
struct Node {
    int len, link;
    int next[26];
};

Node st[MAXN * 2];
int sz = 1, last = 0;

void sam_init() {
    st[0].len = 0;
    st[0].link = -1;
    std::memset(st[0].next, -1, sizeof(st[0].next));
}

void sam_extend(int c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    std::memset(st[cur].next, -1, sizeof(st[cur].next));
    int p = last;

    while (p != -1 && st[p].next[c] == -1) {
        st[p].next[c] = cur;
        p = st[p].link;
    }

    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];

        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            std::memcpy(st[clone].next, st[q].next, sizeof(st[q].next));
            st[clone].link = st[q].link;

            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

inline int fast_tolower(char c) {
    if (c >= 'A' && c <= 'Z') return c + 32 - 'a';
    return c - 'a';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    sam_init();
    char type;
    char buffer[100005];
    
    while (std::cin >> type >> buffer) {
        if (type == 'A') {
            for (int i = 0; buffer[i] != '\0'; ++i) {
                sam_extend(fast_tolower(buffer[i]));
            }
        } else {
            int cur = 0;
            bool found = true;

            for (int i = 0; buffer[i] != '\0'; ++i) {
                int c_idx = fast_tolower(buffer[i]);
                if (c_idx < 0 || c_idx >= 26 || st[cur].next[c_idx] == -1) {
                    found = false;
                    break;
                }
                cur = st[cur].next[c_idx];
            }
            
            if (found) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }
    }
    return 0;
}