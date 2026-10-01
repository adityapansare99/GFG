#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int minTime(vector<int> &dura, vector<vector<int>> &edges) {
        // code here
        int n=dura.size();
        int m=edges.size();
        
        vector<vector<int>> adj(n);
        vector<int> finish=dura;
        vector<int> indeg(n,0);
        
        int c=0;
        for(auto &it:edges){
            int u=it[0];
            int v=it[1];
            
            indeg[v]++;
            
            adj[u].push_back(v);
        }
        
        queue<int> q;
        
        for(int i=0;i<n;i++){
            if(indeg[i]==0){
                q.push(i);
                c++;
            }
        }
        
        while(!q.empty()){
            auto top=q.front();
            q.pop();
            
            for(auto &it:adj[top]){
                indeg[it]--;
                finish[it]=max(finish[it],finish[top]+dura[it]);
                
                if(indeg[it]==0){
                    q.push(it);
                    c++;
                }
            }
        }
        
        if(c!=n){
            return -1;
        }
        
        return *max_element(finish.begin(),finish.end());
    }
};