//Leetcode question No. 208	Implement Trie (Prefix Tree)  

class TrieNode {
public:
// Initialize your data structure here.
TrieNode() {
    memset(children, NULL, sizeof(children));
}
TrieNode* children[26];
bool isEnd = false;
};

class Trie {
public:
Trie() {
    root = new TrieNode();
}

// Inserts a word into the trie.
void insert(string word) {
    TrieNode* root_cpy = root;
    for(int i = 0; i < word.size(); ++i){
        int index = word[i] - 'a';
        if(root_cpy->children[index] == NULL){
            TrieNode* node = new TrieNode();
            root_cpy->children[index] = node;
        }
        root_cpy = root_cpy->children[index];
    }
    // the end (solider TrieNode)
    root_cpy->isEnd = true;
   }

// Returns if the word is in the trie.
bool search(string word) {
    TrieNode* root_cpy = root;
    for(int i = 0; i < word.size(); ++i){
        int index = word[i] - 'a';
        if(root_cpy->children[index] == NULL){return false;}
        root_cpy = root_cpy->children[index];
    }
    return root_cpy->isEnd;
}

// Returns if there is any word in the trie
// that starts with the given prefix.
bool startsWith(string prefix) {
    TrieNode* root_cpy = root;
    for(int i = 0; i < prefix.size(); ++i){
        int index = prefix[i] - 'a';
        if(root_cpy->children[index] == NULL) return false;
        else{
            root_cpy = root_cpy->children[index];
        }
    }
    return true;
}

private:
TrieNode* root;
};
