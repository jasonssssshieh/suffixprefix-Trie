//
//  main.cpp
//  Trie
//
//  Created by Zijian Xie on 2016/10/20.
//  Copyright © 2016年 Jason Xie. All rights reserved.
//  Contains: Insert, search, delete and search_start_with operation.

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;


class TrieNode{
public:
    unordered_map<char, TrieNode> children;
    bool isEnd;
    TrieNode(){//construction function
        children = *new unordered_map<char, TrieNode>();
        isEnd = false;
    }
    TrieNode(unordered_map<char, TrieNode> child, bool end){
        children = child;
        isEnd = end;
    }
    TrieNode(TrieNode& node):children(node.children), isEnd(node.isEnd){}
    ~TrieNode(){};
};

class Trie{
public:
    TrieNode root;
    Trie(){root = *new TrieNode();}
    Trie(Trie& trie):root(trie.root){}
    ~Trie(){};
    
    //insert
    void insert(string str){
        TrieNode cur = root;
        for(int i = 0; i < str.size(); ++i){
            char tmp = str[i];
            TrieNode node = cur.children[tmp];
            if(cur.children.find(tmp) == cur.children.end()){
                node = *new TrieNode();
                cur.children[tmp] = node;
            }
            cur = node;
        }
        cur.isEnd = true;
    }
    
    bool research(string str){
        return research_help(str, root, 0);
    }
    
    bool research_help(string str, TrieNode root, int start){
        if(start == str.size()) return root.isEnd;
        char tmp = str[start];
        if(root.children.find(tmp) == root.children.end()){
            return false;
        }
        TrieNode node = root.children[tmp];
        return research_help(str, node, start + 1);
    }
    
    void Delete(string str){
        Delete_help(str, root, 0);
    }
    
    //关于什么时候应该删掉这个node，什么时候不应该删，那么不删又该如何满足delete的条件呢？
    //记住，我们构建trie的时候，都设置了一个尾部的哨兵节点。map 为空，isEnd = T!
    //我们在trieNode里面设置了isEnd就是用来记录是否到了这个点，这个单词str已经到了结尾，如果isEnd = true，说明已经到了结尾。
    //那什么时候应该删掉这个node呢？ 如果我们搜索到这个节点，isEnd = true，说明单词搜索完毕，我们就可以先从map里面删掉这个char，如果此时删掉之后，map为空，那整个节点都可以被删除。
    //如果这个地方 isEnd = false，那么是绝对不可以删；
    //如果这个地方，isEnd = true，还记得我们设置的尾部哨兵节点么，如果此时map为空，说明我们已经抵达了哨兵节点，当然可以删掉，如果map不为空，就不能删！
    bool Delete_help(string str, TrieNode root, int start){
        if(start == str.size()){
            //only when we reached the end of this word, we can delete this word
            if(root.isEnd == false){return false;}
        //if it is the end of this word, we just change isEnd to "false";
        root.isEnd = false;
        return root.children.empty();
        }
        
        char tmp = str[start];
        if(root.children.find(tmp) == root.children.end()) return false;//如果都没找到这个节点，就更不能删
        TrieNode node = root.children[tmp];//找得到，就继续进入其子树去寻找
        bool DeleteCurrentNode = Delete_help(str, node, start + 1);
        
        if(DeleteCurrentNode){
            root.children.erase(tmp);
            return root.children.empty();
        }
        return false;
    }
    
    bool startsWith(string str){
        return startsWith_help(str, root, 0);
    }
    
    bool startsWith_help(string str, TrieNode root, int start){
        if(start == str.size()){
            return true;
        }
        char tmp = str[start];
        if(root.children.find(tmp) == root.children.end()) return false;
        TrieNode node = root.children[tmp];
        return startsWith_help(str, node, start + 1);
    };
};
