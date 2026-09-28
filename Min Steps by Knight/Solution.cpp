#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int minStepToReachTarget(vector<int>& knightPos, vector<int>& targetPos, int n) {
        // Code here
        vector<vector<int>> dist(n,vector<int>(n,1e9));
        
        priority_queue<pair<int,pair<int,int>> , vector<pair<int,pair<int,int>>>, greater<>> pq;
        
        pq.push({0,{knightPos[0]-1,knightPos[1]-1}});
        
        dist[knightPos[0]-1][knightPos[1]-1]=0;
        
        while(!pq.empty()){
            auto top=pq.top();
            pq.pop();
            
            int val=top.first;
            int i=top.second.first;
            int j=top.second.second;
            
            if(targetPos[0]-1==i && targetPos[1]-1==j){
                return val;
            }
            
            int ni=i;
            int nj=j;
            
            ni=i-2;
            nj=j+1;
            
            if(ni>=0 && nj<n && dist[ni][nj]>dist[i][j]+1){
                dist[ni][nj]=val+1;
                pq.push({val+1,{ni,nj}});
            }
            
            ni=i-2;
            nj=j-1;
            
            if(ni>=0 && nj>=0 && dist[ni][nj]>dist[i][j]+1){
                dist[ni][nj]=val+1;
                pq.push({val+1,{ni,nj}});
            }
            
            ni=i+2;
            nj=j+1;
            
            if(ni<n && nj<n && dist[ni][nj]>dist[i][j]+1){
                dist[ni][nj]=val+1;
                pq.push({val+1,{ni,nj}});
            }
            
            ni=i+2;
            nj=j-1;
            
            if(ni<n && nj>=0 && dist[ni][nj]>dist[i][j]+1){
                dist[ni][nj]=val+1;
                pq.push({val+1,{ni,nj}});
            }
            
            ni=i-1;
            nj=j+2;
            
            if(ni>=0 && nj<n && dist[ni][nj]>dist[i][j]+1){
                dist[ni][nj]=val+1;
                pq.push({val+1,{ni,nj}});
            }
            
            ni=i-1;
            nj=j-2;
            
            if(ni>=0 && nj>=0 && dist[ni][nj]>dist[i][j]+1){
                dist[ni][nj]=val+1;
                pq.push({val+1,{ni,nj}});
            }
            
            ni=i+1;
            nj=j+2;
            
            if(ni<n && nj<n && dist[ni][nj]>dist[i][j]+1){
                dist[ni][nj]=val+1;
                pq.push({val+1,{ni,nj}});
            }
            
            ni=i+1;
            nj=j-2;
            
            if(ni<n && nj>=0 && dist[ni][nj]>dist[i][j]+1){
                dist[ni][nj]=val+1;
                pq.push({val+1,{ni,nj}});
            }
            
        }
        
        return -1;
    }
};