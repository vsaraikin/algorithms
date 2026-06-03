#include <cassert>
#include <unordered_map>

class LRUCache {

struct Node {
    int key, val;
    Node *prev, *next;
    Node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {};
};

private:
    int capacity;
    std::unordered_map<int, Node*> storage;
    Node *head, *tail;

    void add(Node *node) { // add to front
        Node *mru = head->next;
		head->next = node;
		node->prev = head;
		node->next = mru;
		mru->prev = node;
    }

    void remove(Node *node) { // remove node
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
		this->head = new Node(0, 0);
		this->tail = new Node(0, 0);
		this->head->next = this->tail;
		this->tail->prev = this->head;
    }
    
    int get(int key) {
        if (storage.count(key)) {
            Node* n = storage[key];
            remove(n);
            add(n);
            return n->val;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (storage.count(key)) {
            Node *n = storage[key];
            n->val = value;
            remove(n);
            add(n);
            return;
        }
        Node *n = new Node(key, value);
        storage[key] = n;
        add(n);
        if (storage.size() > this->capacity) {
			Node *lru = tail->prev;
            remove(lru);
			storage.erase(lru->key);
			delete lru;
        }
    }
};

int main() {
	// 1) базовый пример из условия
	{
		LRUCache c(2);
		c.put(1, 1);
		c.put(2, 2);
		assert(c.get(1) == 1); // {2=2, 1=1}, 1 — MRU
		c.put(3, 3);		   // вытеснит 2 (LRU)
		assert(c.get(2) == -1);
		c.put(4, 4); // вытеснит 1
		assert(c.get(1) == -1);
		assert(c.get(3) == 3);
		assert(c.get(4) == 4);
	}

	// 2) перезапись существующего ключа не вытесняет
	{
		LRUCache c(2);
		c.put(1, 1);
		c.put(2, 2);
		c.put(1, 10); // обновили, не добавили
		assert(c.get(1) == 10);
		assert(c.get(2) == 2); // 2 ещё здесь
	}

	// 3) capacity = 1
	{
		LRUCache c(1);
		c.put(1, 1);
		assert(c.get(1) == 1);
		c.put(2, 2);
		assert(c.get(1) == -1);
		assert(c.get(2) == 2);
	}

	// 4) get несуществующего
	{
		LRUCache c(2);
		assert(c.get(42) == -1);
	}

	// 5) get освежает позицию (предотвращает вытеснение)
	{
		LRUCache c(2);
		c.put(1, 1);
		c.put(2, 2);
		assert(c.get(1) == 1); // 1 теперь MRU, 2 — LRU
		c.put(3, 3);		   // вытеснит 2
		assert(c.get(2) == -1);
		assert(c.get(1) == 1);
		assert(c.get(3) == 3);
	}

	return 0;
}
