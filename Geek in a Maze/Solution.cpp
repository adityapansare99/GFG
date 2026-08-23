#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int numberOfCells(int r, int c, int u, int d, vector<vector<char>> &mat) {
        // code here
        int n=mat.size();
        int m=mat[0].size();
        
        if(mat[r][c]=='#'){
            return 0;
        }
        
        vector<vector<int>> visi(n,vector<int>(m,-1));
        vector<vector<int>> up(n,vector<int>(m,0));
        vector<vector<int>> down(n,vector<int>(m,0));
        
        queue<pair<int,int>> q;
        q.push({r,c});
        visi[r][c]=u;
        up[r][c]=u;
        down[r][c]=d;
        
        
        while(!q.empty()){
            auto top=q.front();
            q.pop();
            
            int i=top.first;
            int j=top.second;
            
            int ni=i;
            int nj=j-1;
            
            if(nj>=0 && visi[ni][nj]<up[i][j] && mat[ni][nj]!='#'){
                visi[ni][nj]=up[i][j];
                up[ni][nj]=up[i][j];
                down[ni][nj]=down[i][j];
                q.push({ni,nj});
            }
            
            ni=i;
            nj=j+1;
            
            if(nj<m && visi[ni][nj]<up[i][j] && mat[ni][nj]!='#'){
                visi[ni][nj]=up[i][j];
                up[ni][nj]=up[i][j];
                down[ni][nj]=down[i][j];
                q.push({ni,nj});
            }
            
            ni=i-1;
            nj=j;
            
            if(ni>=0 && visi[ni][nj]<up[i][j]-1 && up[i][j]>0 && mat[ni][nj]!='#'){
                up[ni][nj]=up[i][j]-1;
                visi[ni][nj]=up[i][j]-1;
                down[ni][nj]=down[i][j];
                q.push({ni,nj});
            }
            
            ni=i+1;
            nj=j;
            
            if(ni<n && visi[ni][nj]<up[i][j] && down[i][j]>0 && mat[ni][nj]!='#'){
                down[ni][nj]=down[i][j]-1;
                visi[ni][nj]=up[i][j];
                up[ni][nj]=up[i][j];
                q.push({ni,nj});
            }
        }
        
        int ans=0;
        
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(visi[i][j]!=-1){
                    ans++;
                }
            }
        }
        
        return ans;
    }
};