#include<bits/stdc++.h>
using namespace std;

class Solution {
    int xorVal(int n){
        if(n%4==0){
            return n;
        }
        
        else if(n%4==1){
            return 1;
        }
        
        else if(n%4==2){
            return n+1;
        }
        
        else{
            return 0;
        }
    }
  public:
    int findXOR(int l, int r) {
        // code here
        return xorVal(r)^xorVal(l-1);
    }
};


