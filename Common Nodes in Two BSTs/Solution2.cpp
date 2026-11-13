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
  public:
    vector<int> findCommon(Node* r1, Node* r2) {
        // code here
        stack<Node*> s1,s2;
        
        vector<int> ans;
        
        while(true){
            while(r1){
                s1.push(r1);
                r1=r1->left;
            }
            
            while(r2){
                s2.push(r2);
                r2=r2->left;
            }
            
            if(s1.empty() || s2.empty()){
                break;
            }
            
            Node* a=s1.top();
            Node* b=s2.top();
            
            if(a->data==b->data){
                s1.pop();
                s2.pop();
                
                ans.push_back(a->data);
                
                r1=a->right;
                r2=b->right;
            }
            
            else if(a->data>b->data){
                s2.pop();
                r2=b->right;
            }
            
            else{
                s1.pop();
                r1=a->right;
            }
        }
        
        return ans;
    }
};