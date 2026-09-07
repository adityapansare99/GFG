#include<bits/stdc++.h>
using namespace std;

class Solution {
    private:
    int solver(int i,int inc,int dec,vector<int> &arr,vector<vector<vector<int>>> &dp){
        if(i==arr.size()){
            return 0;
        }
        
        if(dp[i][inc+1][dec+1]!=-1){
            return dp[i][inc+1][dec+1];
        }
        
        int ans=solver(i+1,inc,dec,arr,dp);
        
        if(inc==-1 || arr[inc]<arr[i]){
            ans=max(ans,1+solver(i+1,i,dec,arr,dp));
        }
        
        if(dec==-1 || arr[dec]>arr[i]){
            ans=max(ans,1+solver(i+1,inc,i,arr,dp));
        }
        
        return dp[i][inc+1][dec+1]=ans;
    }
  public:
    int minCount(vector<int>& arr) {
        // code here
        int n=arr.size();
        
        vector<vector<vector<int>>> dp(n,vector<vector<int>>(n+2,vector<int>(n+2,-1)));
        
        return n-solver(0,-1,-1,arr,dp);
    }
};