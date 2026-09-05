#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int longestSubseq(vector<int>& arr) {
        // code here
        int n=arr.size();
        map<int,int> mp;
        int ans=0;
        
        for(int i=n-1;i>=0;i--){
            int curr=arr[i];
            int next=curr+1;
            int prev=curr-1;
            
            int val=1;
            
            if(mp.find(next)!=mp.end()){
                val=max(val,mp[next]+1);
            }
            
            if(mp.find(prev)!=mp.end()){
                val=max(val,mp[prev]+1);
            }
            
            mp[curr]=val;
            
            ans=max(ans,val);
        }
        
        return ans;
    }
};