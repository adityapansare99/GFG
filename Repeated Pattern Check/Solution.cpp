#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    bool findPattern(string& s) {
        // code here
        int n=s.size();
        int c=0;
        int i=0;
        while(i<n){
            while(i<n && s[i]=='x'){
                c++;
                i++;
            }
            
            while(i<n && s[i]=='y'){
                c--;
                i++;
            }
            
            if(c!=0){
                return false;
            }
        }
        
        return c==0;
    }
};