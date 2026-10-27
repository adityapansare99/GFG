#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int getMaxWeight(string &s) {
        // code here
        int far=0;
        int next=0;
        
        for(int i=s.size()-1;i>=0;i--){
            int ans=0;
        
            ans=max(ans,1+next);
            
            
            if(i<s.size()-1){
                if(s[i]!=s[i+1]){
                    ans=max(ans,4+far);
                }
                
                else{
                    ans=max(ans,3+far);
                }
            }
            
            far=next;
            next=ans;
        }
        
        return next;
    }
};
