#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int findMinCost(string &s1, string &s2, int costS1, int costS2) {
        // code here
        int n=s1.size();
        int m=s2.size();
        
        vector<vector<int>> dp(n+1,vector<int>(m+1,1e9));
        dp[0][0]=0;
        
        for(int j=0;j<=m;j++){
            dp[0][j]=j*costS2;
        }
        
        for(int i=0;i<=n;i++){
            dp[i][0]=i*costS1;
        }
        
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(s1[i-1]==s2[j-1]){
                    dp[i][j]=dp[i-1][j-1];
                }
                
                else{
                    dp[i][j]=min(costS1+dp[i-1][j],costS2+dp[i][j-1]);
                }
            }
        }
        
        return dp[n][m];
    }
};