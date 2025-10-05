#include <iostream>
#include <vector>

struct PathInfo {
    int length;        // Длина пути, заканчивающегося этим элементом
    int prev_index;    // Индекс предыдущего элемента в пути
    bool is_up;        // Направление последнего перехода
};

struct TreeNode {
    int value;
    bool is_up;
    bool is_root;
    int index;
    std::vector<TreeNode*> children;

    TreeNode(const int& val, const bool _is_up, const bool _is_root, const int& _index) : 
    value(val), is_up(_is_up), is_root(_is_root), index(_index) {}

    ~TreeNode() {
        for (TreeNode* child : children) {
            delete child;
        }
    }

    void addNode(const int& newValue, bool (*predicate)(TreeNode* parent, const int& candidate), 
    const int& _index) {
        if (predicate(this, newValue)) {
            if (this->is_root)
                children.push_back(new TreeNode(newValue, this->value < newValue, false, _index));
            else
                children.push_back(new TreeNode(newValue, !is_up, false, _index));
        }
        for (auto child : children) {
            child->addNode(newValue, predicate, _index);
        }
    }
};

bool myPredicate(TreeNode* parent, const int& candidate) {

    if (parent->is_root && parent->value != candidate)
        return true;
    if (parent->is_up && parent->value > candidate)
        return true;
    if (!(parent->is_up) && parent->value < candidate)
        return true;
    return false;
}

void findLongestPath(TreeNode* node,
                     std::vector<TreeNode*>& currentPath,
                     std::vector<TreeNode*>& bestPath)
{
    if (!node) return;
    currentPath.push_back(node);

    if (node->children.empty()) {
        if (currentPath.size() > bestPath.size()) {
            bestPath = currentPath;
        } else if (currentPath.size() == bestPath.size()) {
            bool is_better = false;
            for (size_t i = 0; i < currentPath.size(); ++i) {
                if (currentPath[i]->index < bestPath[i]->index) {
                    is_better = true;
                    break;
                } else if (currentPath[i]->index > bestPath[i]->index) {
                    is_better = false;
                    break;
                }
            }
            if (is_better) {
                bestPath = currentPath;
            }
        }
    } else {
        for (TreeNode* child : node->children) {
            findLongestPath(child, currentPath, bestPath);
        }
    }
    currentPath.pop_back();
}


int main()
{
    size_t element_count;
    std::cin >> element_count;
    int *data = new int[element_count];
    for (size_t i = 0; i < element_count; ++i)
    {
        std::cin >> data[i];
    }
    std::vector<TreeNode*> all_trees;
    all_trees.push_back(new TreeNode(data[0], false, true, 0));

    for (size_t i = 1; i < element_count; ++i)
    {
        all_trees.push_back(new TreeNode(data[i], false, true, 0));
        for (size_t j = 0; j < i + 1; ++j)
        {
            all_trees[j]->addNode(data[i], myPredicate, i);
        }
    }
    std::vector<TreeNode*> best_tree;
    for (size_t j = 0; j < element_count; ++j) {
        std::vector<TreeNode*> curr, best;
        findLongestPath(all_trees[j], curr, best);

        if (best.size() > best_tree.size())
            best_tree = best;
        
        // for (auto node : best)
        //     cout << node->value << " ";
        // cout << endl;
    }
    // findLongestPath(root, curr, best);

    // for (auto node : best)
    //     cout << node->value << " ";
    // cout << endl;

    for (auto node : best_tree)
        std::cout << node->value << " ";
    std::cout << std::endl;

    delete[] data;
    return 0;
}
