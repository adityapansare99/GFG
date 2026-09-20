#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int largestSubsquare(vector<vector<char>> &mat) {
        // code here
        int n=mat.size();
        vector<vector<int>> row(n,vector<int>(n,0));
        vector<vector<int>> col(n,vector<int>(n,0));
        
        bool present=false;
        
        for(int i=0;i<n;i++){
            int c=0;
            for(int j=n-1;j>=0;j--){
                if(mat[i][j]=='X'){
                    c++;
                    present=true;
                }
                
                else{
                    c=0;
                }
                
                row[i][j]=c;
            }
        }
        
        for(int j=0;j<n;j++){
            int c=0;
            for(int i=n-1;i>=0;i--){
                if(mat[i][j]=='X'){
                    c++;
                }
                
                else{
                    c=0;
                }
                
                col[i][j]=c;
            }
        }
        
        int ans=0;
        
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                int size=min(col[i][j],row[i][j]);
                
                while(size>ans){
                    int right=j+size-1;
                    int bottom=i+size-1;
                    
                    if(row[bottom][j]>=size && col[i][right]>=size){
                        ans=size;
                        break;
                    }
                    
                    size--;
                }
            }
        }
        
        return ans;
    }
};