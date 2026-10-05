#include<bits/stdc++.h>
using namespace std;

class Solution {
    private:
    vector<vector<int>> solver(vector<vector<int>> &adj,int v,int src){
        vector<int> dist(v,1e9);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
        dist[src]=0;
        pq.push({0,src});
        
        while(!pq.empty()){
            auto top=pq.top();
            pq.pop();
            
            int node=top.second;
            int val=top.first;
            
            for(auto &it:adj[node]){
                if(dist[it]>dist[node]+1){
                    pq.push({dist[node]+1,it});
                    dist[it]=dist[node]+1;
                }
            }
        }
        
        vector<vector<int>> res;
        for(int i=1;i<src;i++){
            if(dist[i]!=1e9){
                res.push_back({src,i,dist[i]});
            }
        }
        
        return res;
    }
  public:
    vector<vector<int>> socialNetwork(vector<int>& arr) {
        // code here
        int n=arr.size();
        
        int v=n+2;
        
        vector<vector<int>> adj(v);
        int curr=2;
        
        for(int i=0;i<n;i++){
            int val=arr[i];
            
            // adj[val].push_back(curr);
            adj[curr].push_back(val);
            curr++;
        }
        
        vector<vector<int>> res;
        
        for(int i=2;i<v;i++){
            auto ans=solver(adj,v,i);
            res.insert(res.end(),ans.begin(),ans.end());
        }
        
        return res;
    }
};