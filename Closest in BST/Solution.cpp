#include<bits/stdc++.h>
using namespace std;

class Node {
  public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};


class Solution {
    private:
    void solver(Node* root,int k,int &ans){
        if(root==NULL){
            return ;
        }
        
        ans=min(ans,abs(root->data-k));
        
        if(root->data>k){
            solver(root->left,k,ans);
        }
        
        else{
            solver(root->right,k,ans);
        }
    }
  public:
    int minDiff(Node *root, int k) {
        // code here
        int ans=1e9;
        
        solver(root,k,ans);
        
        return ans;
    }
};
