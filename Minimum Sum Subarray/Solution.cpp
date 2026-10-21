#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int minSubarraySum(vector<int> &arr) {
        // code here
        int n=arr.size();
        
        int mini=INT_MAX;
        int ans=INT_MAX;
        int sum=0;
        
        for(int i=0;i<n;i++){
            sum+=arr[i];
            
            if(sum>0){
                sum=0;
            }
            
            ans=min(ans,sum);
            
            mini=min(arr[i],mini);
        }
        
        if(ans==0){
            return mini;
        }
        
        return ans;
    }
};