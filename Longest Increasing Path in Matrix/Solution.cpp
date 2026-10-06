#include<bits/stdc++.h>
using namespace std;

class Solution {
    private:
    int solver(vector<vector<int>> &mat,int n,int m,int i,int j,vector<vector<int>> &dp){
        if(dp[i][j]!=-1){
            return dp[i][j];
        }
        
        int val=mat[i][j];
        
        int ans=1;
        
        if(i>0 && val<mat[i-1][j]){
            ans=max(ans,1+solver(mat,n,m,i-1,j,dp));
        }
        
        if(j>0 && val<mat[i][j-1]){
            ans=max(ans,1+solver(mat,n,m,i,j-1,dp));
        }
        
        if(i<n-1 && val<mat[i+1][j]){
            ans=max(ans,1+solver(mat,n,m,i+1,j,dp));
        }
        
        if(j<m-1 && val<mat[i][j+1]){
            ans=max(ans,1+solver(mat,n,m,i,j+1,dp));
        }
        
        return dp[i][j]=ans;
    }
  public:
    int longIncPath(vector<vector<int>> &matrix, int n, int m) {
        // code here
        int val=0;
        vector<vector<int>> dp(n,vector<int>(m,-1));
        
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                val=max(val,solver(matrix,n,m,i,j,dp));
            }
        }
        
        return val;
    }
};