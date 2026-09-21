#include<bits/stdc++.h>
using namespace std;

class Node {
    public:
    int data;
    Node *left, *right;
    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};

class Solution {
  public:
    bool areAnagrams(Node* root1, Node* root2) {
        // code here
        map<int,multiset<int>> mp;
        
        queue<Node*> q;
        q.push(root1);
        int level=0;
        
        
        while(!q.empty()){
            vector<int> temp;
            int size=q.size();
            
            for(int i=0;i<size;i++){
                auto top=q.front();
                q.pop();
                mp[level].insert(top->data);
                
                if(top->left){
                    q.push(top->left);
                }
                
                if(top->right){
                    q.push(top->right);
                }
            }
            
            level++;
        }
        
        queue<Node*> rq;
        rq.push(root2);
        level=0;
        
        while(!rq.empty()){
            vector<int> temp;
            int size=rq.size();
            
            for(int i=0;i<size;i++){
                auto top=rq.front();
                rq.pop();
                if(!mp[level].count(top->data)){
                    return false;
                }
                
                mp[level].erase(mp[level].find(top->data));
                
                if(top->left){
                    rq.push(top->left);
                }
                
                if(top->right){
                    rq.push(top->right);
                }
            }
            
            level++;
        }
        
        for(auto &it:mp){
            if(it.second.size()>0){
                return false;
            }
        }
        
        return true;
    }
};
