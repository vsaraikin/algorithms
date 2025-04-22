class Node:
    def __init__(self, key: int, value: int):
        self.key = key
        self.value = value
        self.prev = None
        self.next = None

class LRUCache:

    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache = {}
        self.head = Node(0, 0)
        self.tail = Node(0, 0)
        self.head.next = self.tail
        self.tail.prev = self.head

    def _remove(self, node: Node) -> None:
        """Remove Node from LL"""
        prev_node = node.prev
        next_node = node.next
        prev_node.next = next_node
        next_node.prev = prev_node
    
    def _add(self, node: Node) -> Node:
        """Add Node to LL"""
        prev_tail = self.tail.prev
        prev_tail.next = node
        node.prev = prev_tail
        node.next = self.tail
        self.tail.prev = node

    def get(self, key: int) -> int:
        if key in self.cache:
            node = self.cache[key]
            # move Node to the end
            self._remove(node)
            self._add(node)
            return node.value
        return -1

    def put(self, key: int, value: int) -> None:
        """Add/Update value by key"""
        if key in self.cache:
            self._remove(self.cache[key])
        node = Node(key, value)
        self._add(node)
        self.cache[key] = node
        
        if len(self.cache) > self.capacity:
            lru = self.head.next
            self._remove(lru)
            del self.cache[lru.key]
        
        

lru_cache = LRUCache(2)
lru_cache.put(1, 1)
lru_cache.put(2, 2)
print(lru_cache.get(1))  # Выведет 1

lru_cache.put(3, 3)      # Удаление ключа 2 (наименее использованный)
print(lru_cache.get(2))  # Выведет -1 (так как ключ 2 был удален)

lru_cache.put(4, 4)      # Удаление ключа 1
print(lru_cache.get(1))  # Выведет -1 (так как ключ 1 был удален)
print(lru_cache.get(3))  # Выведет 3
print(lru_cache.get(4))  # Выведет 4