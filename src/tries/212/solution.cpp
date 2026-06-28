#include <vector>
#include <string>

struct TrieNode {
	TrieNode* children[26] = {};
	std::string word;
};

class Trie {
public:
	void insert(const std::string& w) {
		TrieNode* cur = &root;
		for (char c: w) {
			int i = c - 'a';
			if (!cur->children[i]) {
				cur->children[i] = new TrieNode();
			}
			cur = cur->children[i];
		}
		cur->word = w;
	}
	TrieNode root;
};

class Solution {
public:
    std::vector<std::string> findWords(std::vector<std::vector<char>>& board, std::vector<std::string>& words) {
		res.clear();  // reset so repeated calls are independent
		Trie trie;
		for (auto& w: words) {
			trie.insert(w);
		}

		int m = board.size();
		int n = board[0].size();
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				dfs(board, i, j, &trie.root);
			}
		}
		return res;
    }

private:
	std::vector<std::string> res;

	void dfs(std::vector<std::vector<char>>& board, int i, int j, TrieNode* node) {
		if (i < 0 || j < 0 || i >= (int)board.size() || j >= (int)board[0].size() || board[i][j] == '#' || !node->children[board[i][j] - 'a']) {
			return;
		}
		char c = board[i][j];
		node = node->children[c - 'a'];
		if (!node->word.empty()) {
			res.push_back(node->word);
			node->word.clear();
		}
		board[i][j] = '#';
		dfs(board, i + 1, j, node);
		dfs(board, i - 1, j, node);
		dfs(board, i, j + 1, node);
		dfs(board, i, j - 1, node);
		board[i][j] = c;
	}
};