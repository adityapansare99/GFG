#include<bits/stdc++.h>
using namespace std;

// Binary Tree Node Structure
class Node {
  public:
    int data;
    Node *left;
    Node *right;

    Node(int x) {
        data = x;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
  public:
    int getCount(Node *root, int k) {
        // code here
        queue<Node*> q;
        q.push(root);
        int level=1;
        
        int ans=0;
        
        if(root->left==NULL && root->right==NULL){
            if(level<=k){
                ans++;
                k-=level;
            }
            
            else{
                return ans;
            }
        }
        
        
        while(!q.empty()){
            int size=q.size();
            level++;
            
            for(int i=0;i<size;i++){
                auto top=q.front();
                q.pop();
                
                if(top->left!=NULL){
                    q.push(top->left);
                    
                    if(top->left->left==NULL && top->left->right==NULL && level<=k){
                        ans++;
                        k-=level;
                    }
                }
                
                if(top->right!=NULL){
                    q.push(top->right);
                    
                    if(top->right->left==NULL && top->right->right==NULL && level<=k){
                        ans++;
                        k-=level;
                    }
                }
            }
            
            if(level>k){
                return ans;
            }
        }
        
        
        return ans;
    }
};