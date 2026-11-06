#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int countBT(int h) {
        // code here
        int mod=1e9+7;
        
        if(h==1){
            return 1;
        }
        
        long long prev1=1;
        long long prev2=1;
        
        for(int i=2;i<=h;i++){
            long long curr=(prev1*prev1%mod+2*prev1*prev2%mod)%mod;
            prev2=prev1;
            prev1=curr;
        }
        
        return prev1;
    }
};