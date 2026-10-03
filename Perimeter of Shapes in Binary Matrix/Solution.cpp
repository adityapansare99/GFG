#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int findPerimeter(vector<vector<int>> &mat) {
        // code here
        int n=mat.size();
        int m=mat[0].size();
        
        int ans=0;
        
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(mat[i][j]==1){
                    ans+=4;
                    
                    if(i>0){
                        ans-=mat[i-1][j];
                    }
                    
                    if(i<n-1){
                        ans-=mat[i+1][j];
                    }
                    
                    if(j>0){
                        ans-=mat[i][j-1];
                    }
                    
                    if(j<m-1){
                        ans-=mat[i][j+1];
                    }
                }
            }
        }
        
        return ans;
    }
};