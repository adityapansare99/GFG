#include<bits/stdc++.h>
using namespace std;

class Solution {
    int mod=1e9+7;
    
    int solver(int x,int y,vector<vector<int>> &dp){
        if(x<0 || y<0){
            return 0;
        }
        
        if(x==0 && y==0){
            return 1;
        }
        
        if(dp[x][y]!=-1){
            return dp[x][y];
        }
        
        return dp[x][y]=((solver(x-1,y,dp)%mod)+(solver(x,y-1,dp))%mod)%mod;
    }
  public:
    int ways(int x, int y) {
        // code here
        vector<vector<int>> dp(x+1,vector<int>(y+1,-1));
        return solver(x,y,dp);
    }
};