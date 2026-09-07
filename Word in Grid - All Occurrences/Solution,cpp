#include<bits/stdc++.h> 
using namespace std;

class Solution {
  public:
    vector<vector<int>> searchWord(vector<vector<char>> &mat, string &word) {
        // Code here
        int n=mat.size();
        int m=mat[0].size();
        set<pair<int,int>> ans;
        
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                for(int x=-1;x<=1;x++){
                    for(int y=-1;y<=1;y++){
                        int z=0;
                        int ni=i;
                        int nj=j;
                        while(z<word.size() && ni>=0 && ni<n && nj<m && nj>=0 && mat[ni][nj]==word[z]){
                            z++;
                            ni+=x;
                            nj+=y;
                        }
                        
                        if(z==word.size()){
                            ans.insert({i,j});
                        }
                    }
                }
            }
        }
        
        vector<vector<int>> res;
        
        for(auto &it:ans){
            res.push_back({it.first,it.second});
        }
        
        return res;
    }
};