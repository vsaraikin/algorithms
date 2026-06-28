#include <cassert>
#include <string>

class WordDictionary {
    struct Node {
        Node* children[26] = {};
        bool isEnd = false;
    };

    Node root;
public:
    void addWord(std::string word) {
        Node* cur = &root;
        for (char c: word) {
            int i = c - 'a';
            if (!cur->children[i]) {
                cur->children[i] = new Node();
            }
            cur = cur->children[i];
        }
        cur->isEnd = true;
    }
    
    bool search(std::string word) {
		return dfs(&root, word, 0);
    }
    
private:
	bool dfs(Node* node, const std::string& word, int idx) {
		if (idx == word.size()) {
			return node->isEnd;
		}
		char c = word[idx];
		if (c == '.') {
			for (int i = 0; i < 26; ++i) {
				if (node->children[i] && dfs(node->children[i], word, idx + 1)) {
					return true;
				}
			}
			return false;
		}
		int i = c - 'a';
		if (!node->children[i]) {
			return false;
		}
		return dfs(node->children[i], word, idx + 1);
	}
};

int main() {
	// 1) базовый сценарий из задачи
	{
		WordDictionary d;
		d.addWord("bad");
		d.addWord("dad");
		d.addWord("mad");
		assert(d.search("pad") == false);
		assert(d.search("bad") == true);
		assert(d.search(".ad") == true);
		assert(d.search("b..") == true);
	}

	// 2) пустой словарь
	{
		WordDictionary d;
		assert(d.search("a") == false);
		assert(d.search(".") == false);
	}

	// 3) одно слово, разные wildcard-паттерны
	{
		WordDictionary d;
		d.addWord("hello");
		assert(d.search("hello") == true);
		assert(d.search("hell") == false);
		assert(d.search("helloo") == false);
		assert(d.search("h....") == true);
		assert(d.search(".....") == true);
		assert(d.search("....") == false);
		assert(d.search("......") == false);
	}

	// 4) все точки разной длины
	{
		WordDictionary d;
		d.addWord("a");
		d.addWord("ab");
		d.addWord("abc");
		assert(d.search(".") == true);
		assert(d.search("..") == true);
		assert(d.search("...") == true);
		assert(d.search("....") == false);
	}

	// 5) общий префикс — точка должна найти любую ветку
	{
		WordDictionary d;
		d.addWord("car");
		d.addWord("card");
		d.addWord("care");
		assert(d.search("car") == true);
		assert(d.search("ca.") == true);
		assert(d.search("ca..") == true);
		assert(d.search("..r.") == true);
		assert(d.search("c.r.") == true);
		assert(d.search("c.r") == true);
		assert(d.search("c..") == true);
		assert(d.search("c..k") == false);
	}

	// 6) wildcard в начале
	{
		WordDictionary d;
		d.addWord("apple");
		d.addWord("apply");
		assert(d.search(".pple") == true);
		assert(d.search(".pply") == true);
		assert(d.search(".pplx") == false);
	}

	// 7) повторная вставка
	{
		WordDictionary d;
		d.addWord("a");
		d.addWord("a");
		assert(d.search("a") == true);
	}

	// 8) длинный wildcard
	{
		WordDictionary d;
		d.addWord("abcdef");
		assert(d.search("......") == true);
		assert(d.search(".....f") == true);
		assert(d.search("a.....") == true);
		assert(d.search(".....g") == false);
	}

	return 0;
}
