#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int transform(string &s1, string &s2) {
        // code here
        map<char,int> mp;
        
        for(int i=0;i<s1.size();i++){
            mp[s1[i]]++;
        }
        
        for(int i=0;i<s2.size();i++){
            mp[s2[i]]--;
            
            if(mp[s2[i]]==0){
                mp.erase(s2[i]);
            }
        }
        
        if(mp.size()!=0){
            return -1;
        }
        
        int i=s1.size()-1;
        int j=s2.size()-1;
        
        int ans=0;
        
        while(i>=0 && j>=0){
            if(s1[i]==s2[j]){
                i--;
                j--;
            }
            
            else{
                ans++;
                i--;
            }
        }
        
        return ans;
    }
};
