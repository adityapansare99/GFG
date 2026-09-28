#include<bits/stdc++.h>
using namespace std;

class Solution {
    private:
    void build(vector<int> &seg,vector<int> &arr,int l,int r,int i){
        if(l==r){
            seg[i]=arr[r];
            
            return ;
        }
        
        int mid=(l+r)/2;
        build(seg,arr,l,mid,2*i+1);
        build(seg,arr,mid+1,r,2*i+2);
        
        seg[i]=__gcd(seg[2*i+1],seg[2*i+2]);
    }
    
    int search(vector<int> &seg,int i,int l,int r,int left,int right){
        if(left<=l && r<=right){
            return seg[i];
        }
        
        else if(left>r || right<l){
            return 0;
        }
        
        int mid=(l+r)/2;
        int leftVal=search(seg,2*i+1,l,mid,left,right);
        int rightVal=search(seg,2*i+2,mid+1,r,left,right);
        
        return __gcd(leftVal,rightVal);
    }
    
    void update(vector<int> &seg,int i,int l,int r,int index,int val){
        if(l==r){
            seg[i]=val;
            return ;
        }
        
        int mid=(l+r)/2;
        
        if(index<=mid){
            update(seg,2*i+1,l,mid,index,val);
        }
        
        else{
            update(seg,2*i+2,mid+1,r,index,val);
        }
        
        seg[i]=__gcd(seg[2*i+1],seg[2*i+2]);
    }
    
  public:
    vector<int> processQueries(vector<int>& arr, vector<vector<int>>& queries) {
        // code here
        int n=arr.size();
        vector<int> seg(4*n);
        
        build(seg,arr,0,n-1,0);
        
        vector<int> ans;
        
        for(auto &it:queries){
            if(it[0]==0){
                int l=it[1];
                int r=it[2];
                
                ans.push_back(search(seg,0,0,n-1,l,r));
            }
            
            else{
                int index=it[1];
                int value=it[2];
                
                update(seg,0,0,n-1,index,value);
            }
        }
        
        return ans;
    }
};