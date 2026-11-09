#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int getCount(string &s, int k) {
        // code here
        int n=s.size();
        map<char,int> mp;
        
        for(int i=0;i<n;i++){
            mp[s[i]]++;
            
            while(i<n && s[i]==s[i+1]){
                i++;
            }
        }
        
        int ans=0;
        
        for(auto &it:mp){
            if(it.second==k){
                ans++;
            }
        }
        
        return ans;
    }
};