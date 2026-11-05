#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int getMinimumDays(string &s, vector<int> &p) {
        // code here
        int n=s.size();
        
        unordered_map<int,int> mp;
        
        for(int i=0;i<n;i++){
            mp[p[i]]=i;
        }
        
        int ans=INT_MIN;
        
        for(int i=0;i<n-1;i++){
            if(s[i]==s[i+1]){
                int day1=mp[i];
                int day2=mp[i+1];
                
                ans=max(ans,min(day2,day1));
            }
        }
        
        if(ans==INT_MIN){
            return 0;
        }
        
        return ans+1;
    }
};
