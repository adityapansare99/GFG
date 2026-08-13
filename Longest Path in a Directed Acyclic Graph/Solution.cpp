#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> maxDistance(int V, int src, vector<vector<int>> &edges) {
        // code here
        vector<vector<pair<int,int>>> adj(V);
        
        for(auto &it:edges){
            int u=it[0];
            int v=it[1];
            int w=it[2];
            
            adj[u].push_back({v,w});
        }
        
        vector<int> dist(V,INT_MIN);
        priority_queue<pair<int,int>> pq;
        pq.push({0,src});
        dist[src]=0;
        
        while(!pq.empty()){
            auto top=pq.top();
            pq.pop();
            
            int we=top.first;
            int node=top.second;
            
            if(we<dist[node]){
                continue;
            }
            
            for(auto &it:adj[node]){
                int w=it.second;
                int n=it.first;
                
                if(we+w>dist[n]){
                    dist[n]=we+w;
                    pq.push({we+w,n});
                }
            }
        }
        
        return dist;
    }
};