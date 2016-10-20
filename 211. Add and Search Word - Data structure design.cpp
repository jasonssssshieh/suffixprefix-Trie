//Leetcode No.211
//Using Trie & Backtracking method
class TrieNode{
public:
    TrieNode(){
        children.resize(26,NULL);
    }
    bool isEnd = false;
    vector<TrieNode*> children;
};

class WordDictionary {
public:
    WordDictionary(){root = new TrieNode();}
    // Adds a word into the data structure.
    void addWord(string word) {
        auto cur = root;
        for(int i = 0; i < word.size(); ++i){
            int index = word[i] - 'a';
            if(!cur->children[index]){
                auto node = new TrieNode();
                cur->children[index] = node;
            }
            cur = cur->children[index];
        }
        cur->isEnd = true;
    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        return search_help(word, root, 0);
    }
    
    bool search_help(string word, TrieNode* root, int start){
        if(start == word.size()) return root->isEnd;
        auto cur = root;
        if(word[start] != '.'){
            int index = word[start] - 'a';
            return cur->children[index] && search_help(word, cur->children[index], start + 1);
        }else{
            for(auto c : cur->children){
                if(c && search_help(word, c, start + 1)) return true;
            }
            return false;
        }
        return cur->isEnd;
    }
private:
    TrieNode* root;
};
