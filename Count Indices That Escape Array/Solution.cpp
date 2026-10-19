#include<bits/stdc++.h>
using namespace std;

class Solution {
    private:
    int dfs(vector<int> &visi,int i,vector<int> &arr){
        if(i<0 || i>=visi.size()){
            return visi.size()+1;
        }
        
        if(visi[i]!=-1e6){
            return visi[i];
        }
        
        visi[i]=i;
        
        int inx=dfs(visi,i+arr[i],arr);
        
        visi[i]=inx;
        
        return inx;
    }
  public:
    int goodIndices(vector<int> &arr) {
        // code here
        int n=arr.size();
        vector<int> visi(n,-1e6);
        
        for(int i=0;i<n;i++){
            if(visi[i]==-1e6){
                dfs(visi,i,arr);
            }
        }
        
        int ans=0;
        
        for(int i=0;i<n;i++){
            if(visi[i]==visi.size()+1){
                ans++;
            }
        }
        
        return ans;
    }
};