#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int minimumEdgeReversal(vector<vector<int>> &edges, int n, int src, int dst) {
        // code here  
        vector<vector<int>> adj(n+1);
        vector<vector<int>> reverse(n+1);
        
        for(auto &it:edges){
            int u=it[0];
            int v=it[1];
            
            adj[u].push_back(v);
            reverse[v].push_back(u);
        }
        
        priority_queue<pair<int,int> , vector<pair<int,int>> , greater<>> pq;
        vector<int> cost(n+1,1e9);
        
        pq.push({0,src});
        cost[src]=0;
        
        while(!pq.empty()){
            auto top=pq.top();
            pq.pop();
            
            int node=top.second;
            int val=top.first;
            
            if(node==dst){
                return val;
            }
            
            for(auto &it:adj[node]){
                int n=it;
                if(cost[n]>cost[node]){
                    cost[n]=cost[node];
                    pq.push({cost[node],n});
                }
            }
            
            for(auto &it:reverse[node]){
                int n=it;
                if(cost[n]>cost[node]+1){
                    cost[n]=cost[node]+1;
                    pq.push({cost[n],n});
                }
            }
        }
        
        return -1;
    }
};