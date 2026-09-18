#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
}; 


class Solution {
    private:
    int ans;
    void solver(Node* root,int &prev){
        if(root==NULL){
            return ;
        }
        
        solver(root->left,prev);
        
        if(prev!=-1)
        ans=min(ans,root->data-prev);
        
        prev=root->data;
        
        solver(root->right,prev);
    }
  public:
    int absDiff(Node *root) {
        // code here
        int prev=-1;
        ans=INT_MAX;
        solver(root,prev);
        
        return ans;
    }
};