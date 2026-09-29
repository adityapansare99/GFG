#include<bits/stdc++.h>
using namespace std;

class Solution {
    int mod=1e9+7;
  public:
    int ways(int x, int y) {
        // code here
        vector<int> prev(y+2,0);
        prev[1]=1;
        
        for(int i=1;i<=x+1;i++){
            vector<int> curr(y+2,0);
            if(i==1){
                curr[1]=1;
            }
            
            for(int j=1;j<=y+1;j++){
                if(i==1 && j==1){
                    continue;
                }
                
                curr[j]=((prev[j]%mod)+(curr[j-1]%mod))%mod;
            }
            
            prev=curr;
        }
        
        return prev[y+1];
    }
};