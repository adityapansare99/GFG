#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    bool isPossible(int n, int m, string& s) {
        // code here
        int v=0;
        int h=0;
        
        int minv=0; 
        int maxv=0;
        int minh=0;
        int maxh=0;
        
        for(int i=0;i<s.size();i++){
            if(s[i]=='L'){
                h++;
            }
            
            else if(s[i]=='R'){
                h--;
            }
            
            else if(s[i]=='U'){
                v++;
            }
            
            else{
                v--;
            }
            
            minv=min(minv,v);
            maxv=max(maxv,v);
            minh=min(minh,h);
            maxh=max(maxh,h);
        }
        
        return (maxv-minv<n && maxh-minh<m);
    }
};