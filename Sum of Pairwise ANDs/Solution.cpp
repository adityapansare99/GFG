#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    long long pairAndSum(vector<int> &arr) {
        // code here
        int n=arr.size();
        
        long long ans=0;
        
        for(int i=0;i<=31;i++){
            long long set_count=0;
            
            for(auto &it:arr){
                if((it & (1LL<<i))!=0){
                    set_count++;
                }
            }
            
            ans+=((set_count*(set_count-1)/2) * (1LL<<i));
        }
        
        return ans;
    }
};