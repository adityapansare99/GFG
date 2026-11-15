#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int subsequenceSum(string &s) {
        // code here
        int n=s.size();
        int mod=1e9+7;
        long long sum=0;
        
        for(int i=0;i<n;i++){
            sum=((s[i]-'0')+sum)%mod;
        }
        
        long long pow2=1;
        
        for(int i=0;i<n-1;i++){
            pow2=(pow2*2)%mod;
        }
        
        
        return (sum*pow2)%mod;
    }
};