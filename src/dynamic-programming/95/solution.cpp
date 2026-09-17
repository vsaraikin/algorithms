#include <vector>

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right)
		: val(x), left(left), right(right) {}
};

class Solution {
  public:
	std::vector<TreeNode *> generateTrees(int n) {
		std::vector<std::vector<std::vector<TreeNode *>>> cache(n+1, std::vector<std::vector<TreeNode *>>(n + 1));
		if (n == 0) {
			return {};
		}
		return build(cache, 1, n);
	}

	std::vector<TreeNode *> build(std::vector<std::vector<std::vector<TreeNode *>>>& cache, int start, int end) {
		if (start > end) {
			return {nullptr};
		}
		if (!cache[start][end].empty()) {
			return cache[start][end];
		}


		std::vector<TreeNode *> arr;

		for (int root = start; root <= end; root++) {
			auto lefts = build(cache, start, root - 1);
			auto rights = build(cache, root + 1, end);
			for (const auto &l : lefts) {
				for (const auto &r : rights) {
					TreeNode *node = new TreeNode(root, l, r);
					arr.push_back(node);
				}
			}
		}
		cache[start][end] = arr;
		return arr;
	}
};
