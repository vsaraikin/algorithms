class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end = False

class Trie:

    def __init__(self):
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        node = self.root
        for ch in word:
            if not node.children.get(ch):
                node.children[ch] = TrieNode()
            node = node.children[ch]
        node.is_end = True
                

    def search(self, word: str) -> bool:
        node = self._find_node(word)
        return bool(node and node.is_end)

    def startsWith(self, prefix: str) -> bool:
        node = self._find_node(prefix)
        return bool(node)

    def _find_node(self, prefix: str) -> TrieNode:
        node = self.root
        for ch in prefix:
            if not node.children.get(ch):
                return None
            node = node.children[ch]
        return node

        
# obj = Trie()
# obj.insert(word)
# param_2 = obj.search(word)
# param_3 = obj.startsWith(prefix)