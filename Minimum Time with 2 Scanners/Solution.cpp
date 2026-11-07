#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int minTime(int n, int s1, int s2) {
        // code here
        int maxi=max(s1,s2);
        int mini=min(s1,s2);
        
        int low=0;
        int high=n;
        
        long long ans=1e18;
        
        while(low<=high){
            int mid=(low+high)/2;
            
            int rem=n-mid;
            
            long long mint=mini*rem;
            long long maxt=maxi*mid;
            
            if(ans>=max(mint,maxt)){
                ans=max(mint,maxt);
            }
            
            if(mint>maxt){
                low=mid+1;
            }
            
            else{
                high=mid-1;
            }
        }
        
        return ans;
    }
};