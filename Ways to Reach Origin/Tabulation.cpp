#include<bits/stdc++.h>
using namespace std;

class Solution {
    int mod=1e9+7;
  public:
    int ways(int x, int y) {
        // code here
        vector<vector<int>> dp(x+2,vector<int>(y+2,0));
        dp[1][1]=1;
        
        for(int i=1;i<=x+1;i++){
            for(int j=1;j<=y+1;j++){
                if(i==1 && j==1){
                    continue;
                }
                
                dp[i][j]=((dp[i-1][j]%mod)+(dp[i][j-1]%mod))%mod;
            }
        }
        
        return dp[x+1][y+1];
    }
};