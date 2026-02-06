class Trie {
    public:
        class TrieNode {
            public:
                unordered_map<char, TrieNode*> ch;
                bool isWord;
    
                TrieNode(): isWord(false){};
        };
    
        TrieNode *root;
    
        Trie() {
            root = new TrieNode();
        }
        
        void insert(string word) {
            TrieNode *cur = root;
            for (int i = 0; i < word.size(); i++) {
                int curCh = word[i];
                if (!cur->ch.count(curCh)) {
                    TrieNode *newNode = new TrieNode();
                    cur->ch[curCh] = newNode;
                }
                cur = cur->ch[curCh];
            }
            cur->isWord = true;
        }
        
        bool search(string word) {
            TrieNode *cur = root;
            for (int i = 0; i < word.size(); i++) {
                int curCh = word[i];
                if (!cur->ch.count(curCh)) {
                    return false;
                }
                cur = cur->ch[curCh];
            }
            return cur->isWord;
        }
        
        bool startsWith(string prefix) {
            TrieNode *cur = root;
            for (int i = 0; i < prefix.size(); i++) {
                int curCh = prefix[i];
                if (!cur->ch.count(curCh)) {
                    return false;
                }
                cur = cur->ch[curCh];
            }
            return true;
        }
    };
    
    /**
     * Your Trie object will be instantiated and called as such:
     * Trie* obj = new Trie();
     * obj->insert(word);
     * bool param_2 = obj->search(word);
     * bool param_3 = obj->startsWith(prefix);
     */