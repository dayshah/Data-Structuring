
class TrieNode:
    def __init__(self):
        self.children = {}
        self.endOfWord = False

class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word: str):
        current = self.root
        for c in word:
            if c not in current.children:
                current.children[c] = TrieNode()
            current = current.children[c]
        current.endOfWord = True
        
    def search(self, word: str):
        current = self.root
        for c in word:
            if (c not in current.children):
                return False
            current = current.children[c]
        if current.endOfWord:
            return True
        return False

    def startsWith(self, prefix: str):
        current = self.root
        for c in prefix:
            if (c not in current.children):
                return False
            current = current.children[c]
        return True






