from node import TrieNode

class WordDictionary:
    def __init__(self):
        self.root = TrieNode()

    def addWord(self, word: str) -> None:
        node = self.root
        for ch in word:
            if not node.children.get(ch):
                node.children[ch] = TrieNode()
            node = node.children[ch]
        node.is_end = True

    def search(self, word: str) -> bool:
        def dfs(node: TrieNode, i: int):
            if len(word) == i:
                return node.is_end
            
            if word[i] == '.':
                for ch in node.children.values():
                    if dfs(ch, i + 1):
                        return True
                return False
            else:
                if word[i] not in node.children:
                    return False
                return dfs(node.children[word[i]], i + 1)
            
        return dfs(self.root, 0)
