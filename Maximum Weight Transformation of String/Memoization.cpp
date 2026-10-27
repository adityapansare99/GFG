#include<bits/stdc++.h>
using namespace std;

class Solution {
    private:
    int solver(string &str,int i,vector<int> &dp){
        if(i>=str.size()){
            return 0;
        }
        
        if(dp[i]!=-1){
            return dp[i];
        }
        
        int ans=0;
        
        ans=max(ans,1+solver(str,i+1,dp));
        
        
        if(i<str.size()-1){
            if(str[i]!=str[i+1]){
                ans=max(ans,4+solver(str,i+2,dp));
            }
            
            else{
                ans=max(ans,3+solver(str,i+2,dp));
            }
        }
        
        return dp[i]=ans;
    }
  public:
    int getMaxWeight(string &s) {
        // code here
        vector<int> dp(s.size(),-1);
        
        return solver(s,0,dp);
    }
};