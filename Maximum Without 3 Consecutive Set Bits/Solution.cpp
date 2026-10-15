#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int maxValue(int n) {
        // code here
        int ans=0;
        int c=0;
        
        for(int i=31;i>=0;i--){
            if(((n>>i)&1)==1){
                c++;
            }
            
            else{
                c=0;
            }
            
            if(c==3){
                n=((1<<i)^n);
                c=0;
            }
        }
        
        
        return n;
    }
};