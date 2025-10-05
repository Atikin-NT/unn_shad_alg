#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    int n_count, m, l;
    std::cin >> n_count >> m >> l;

    std::vector<std::vector<int>> A_matrix(n_count, std::vector<int>(l));
    for (int i = 0; i < n_count; ++i) {
        for (int k = 0; k < l; ++k) {
            std::cin >> A_matrix[i][k];
        }
    }

    std::vector<std::vector<int>> B_matrix(m, std::vector<int>(l));
    for (int i = 0; i < m; ++i) {
        for (int k = 0; k < l; ++k) {
            std::cin >> B_matrix[i][k];
        }
    }

    int q_count;
    std::cin >> q_count;

    for (int query_num = 0; query_num < q_count; ++query_num) {
        int i_index, j_index;
        std::cin >> i_index >> j_index;
        
        i_index--;
        j_index--;

        auto& current_A = A_matrix[i_index];
        auto& current_B = B_matrix[j_index];

        if (current_A[0] > current_B[0]) {
            std::cout << 1 << "\n";
            continue;
        }
        if (current_A[l - 1] <= current_B[l - 1]) {
            std::cout << l << "\n";
            continue;
        }

        int left = 0;
        int right = l - 1;
        int boundary_index = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (current_A[mid] <= current_B[mid]) {
                boundary_index = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        int left_val = std::max(current_A[boundary_index], current_B[boundary_index]);
        int right_val = std::max(current_A[boundary_index + 1], current_B[boundary_index + 1]);

        if (left_val <= right_val) {
            std::cout << boundary_index + 1 << "\n";
        } else {
            std::cout << boundary_index + 2 << "\n";
        }
    }

    return 0;
}
