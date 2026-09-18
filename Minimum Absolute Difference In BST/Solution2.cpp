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
    void solver(Node* root,vector<int> &ans){
        if(root==NULL){
            return ;
        }
        
        solver(root->left,ans);
        ans.push_back(root->data);
        solver(root->right,ans);
    }
  public:
    int absDiff(Node *root) {
        // code here
        vector<int> ans;
        
        solver(root,ans);
        
        sort(ans.begin(),ans.end());
        
        int res=INT_MAX;
        
        for(int i=1;i<ans.size();i++){
            res=min(res,ans[i]-ans[i-1]);
        }
        
        return res;
    }
};