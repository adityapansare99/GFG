#include<bits/stdc++.h>
using namespace std;

class Solution {
    private:
    int solver(string &s1,string &s2,int i,int j,int cost1,int cost2,vector<vector<int>> &dp){
        if(i<0 && j<0){
            return 0;
        }
        
        if(i<0){
            return (j+1)*cost2;
        }
        
        if(j<0){
            return (i+1)*cost1;
        }
        
        if(dp[i][j]!=-1){
            return dp[i][j];
        }
        
        if(s1[i]==s2[j]){
            return dp[i][j]=solver(s1,s2,i-1,j-1,cost1,cost2,dp);
        }
        
        return dp[i][j]=min(cost1+solver(s1,s2,i-1,j,cost1,cost2,dp),cost2+solver(s1,s2,i,j-1,cost1,cost2,dp));
    }
  public:
    int findMinCost(string &s1, string &s2, int costS1, int costS2) {
        // code here
        int n=s1.size();
        int m=s2.size();
        
        vector<vector<int>> dp(n,vector<int>(m,-1));
        
        return solver(s1,s2,n-1,m-1,costS1,costS2,dp);
    }
};