#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int findMinCost(string &s1, string &s2, int costS1, int costS2) {
        // code here
        int n=s1.size();
        int m=s2.size();
        
        vector<int> prev(m+1,1e9);
        prev[0]=0;
        
        for(int j=0;j<=m;j++){
            prev[j]=j*costS2;
        }
        
        for(int i=1;i<=n;i++){
            vector<int> curr(m+1,1e9);
            curr[0]=i*costS1;
            
            for(int j=1;j<=m;j++){
                if(s1[i-1]==s2[j-1]){
                    curr[j]=prev[j-1];
                }
                
                else{
                    curr[j]=min(costS1+prev[j],costS2+curr[j-1]);
                }
            }
            
            prev=curr;
        }
        
        return prev[m];
    }
};