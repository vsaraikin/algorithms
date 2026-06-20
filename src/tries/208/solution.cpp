#include <cassert>
#include <string>

class Trie {
	struct Node {
		Node* children[26] = {};
		bool isEnd = false;
	};
	Node root;

public:
	void insert(std::string word) {
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
		Node* n = traverse(word);
		return n && n->isEnd;
	}

	bool startsWith(std::string prefix) {
		return traverse(prefix) != nullptr;
	}

private:
	Node* traverse(const std::string& s) {
		Node* cur = &root;
		for (char c: s) {
			int i = c - 'a';
			if (!cur->children[i]) {
				return nullptr;
			}
			cur = cur->children[i];
		}
		return cur;
	}
};

int main() {
	// 1) базовый сценарий из задачи
	{
		Trie t;
		t.insert("apple");
		assert(t.search("apple") == true);
		assert(t.search("app") == false);
		assert(t.startsWith("app") == true);
		t.insert("app");
		assert(t.search("app") == true);
	}

	// 2) пустой trie
	{
		Trie t;
		assert(t.search("anything") == false);
		assert(t.startsWith("any") == false);
	}

	// 3) одно слово, разные подстроки
	{
		Trie t;
		t.insert("hello");
		assert(t.search("hello") == true);
		assert(t.search("hell") == false);
		assert(t.search("helloo") == false);
		assert(t.startsWith("h") == true);
		assert(t.startsWith("he") == true);
		assert(t.startsWith("hello") == true);
		assert(t.startsWith("helloo") == false);
	}

	// 4) несколько слов с общим префиксом
	{
		Trie t;
		t.insert("car");
		t.insert("card");
		t.insert("care");
		t.insert("careful");
		assert(t.search("car") == true);
		assert(t.search("card") == true);
		assert(t.search("care") == true);
		assert(t.search("careful") == true);
		assert(t.search("ca") == false);
		assert(t.search("cars") == false);
		assert(t.startsWith("ca") == true);
		assert(t.startsWith("car") == true);
		assert(t.startsWith("care") == true);
		assert(t.startsWith("carx") == false);
	}

	// 5) одиночные символы
	{
		Trie t;
		t.insert("a");
		assert(t.search("a") == true);
		assert(t.search("b") == false);
		assert(t.startsWith("a") == true);
	}

	// 6) повторная вставка того же слова
	{
		Trie t;
		t.insert("dog");
		t.insert("dog");
		assert(t.search("dog") == true);
	}

	// 7) слова где одно — префикс другого
	{
		Trie t;
		t.insert("a");
		t.insert("ab");
		t.insert("abc");
		assert(t.search("a") == true);
		assert(t.search("ab") == true);
		assert(t.search("abc") == true);
		assert(t.search("abcd") == false);
	}

	return 0;
}
