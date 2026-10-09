#include<bits/stdc++.h>
using namespace std;

class Solution {
    private:
    int solver(int n,vector<int> &dp){
        if(n<0){
            return 1e9;
        }
        
        if(n==0){
            return 0;
        }
        
        if(dp[n]!=-1){
            return dp[n];
        }
        
        int ans=1e9;
        
        if(n%2==0){
            ans=min(ans,1+solver(n/2,dp));
        }
        
        return dp[n]=min(ans,1+solver(n-1,dp));
    }
  public:
    int minOperation(int n) {
        // code here
        vector<int> dp(n+1,-1);
        
        return solver(n,dp);
    }
};