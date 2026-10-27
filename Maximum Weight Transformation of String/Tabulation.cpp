#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int getMaxWeight(string &s) {
        // code here
        vector<int> dp(s.size()+1,0);
        
        for(int i=s.size()-1;i>=0;i--){
            int ans=0;
        
            ans=max(ans,1+dp[i+1]);
            
            
            if(i<s.size()-1){
                if(s[i]!=s[i+1]){
                    ans=max(ans,4+dp[i+2]);
                }
                
                else{
                    ans=max(ans,3+dp[i+2]);
                }
            }
            
            dp[i]=ans;
        }
        
        return dp[0];
    }
};