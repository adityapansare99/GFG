#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int minMoves(vector<int>& arr) {
        // code here
        int n=arr.size();
        
        vector<int> pos(n+1,0);
        
        for(int i=0;i<n;i++){
            pos[arr[i]]=i;
        }
        
        int maxi=1;
        int curr=1;
        
        for(int i=1;i<n;i++){
            if(pos[i]<pos[i+1]){
                curr++;
            }
            
            else{
                curr=1;
            }
            
            maxi=max(maxi,curr);
        }
        
        return n-maxi;
    }
};