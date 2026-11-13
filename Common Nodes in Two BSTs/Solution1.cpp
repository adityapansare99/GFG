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
    void traversal(Node* root,vector<int> &ans){
        if(root==NULL){
            return ;
        }
        
        traversal(root->left,ans);
        ans.push_back(root->data);
        traversal(root->right,ans);
    }
  public:
    vector<int> findCommon(Node* r1, Node* r2) {
        // code here
        vector<int> vec1;
        traversal(r1,vec1);
        
        vector<int> vec2;
        traversal(r2,vec2);
        
        vector<int> res;
        
        int i=0;
        int j=0;
        
        while(i<vec1.size() && j<vec2.size()){
            if(vec1[i]>vec2[j]){
                j++;
            }
            
            else if(vec1[i]<vec2[j]){
                i++;
            }
            
            else{
                res.push_back(vec1[i]);
                i++;
                j++;
            }
        }
        
        return res;
    }
};