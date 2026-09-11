#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int sameMod(vector<int> &arr) {
        // code here
        int n=arr.size();
        
        bool check=false;
        
        for(int i=1;i<n;i++){
            if(arr[i]!=arr[0]){
                check=true;
                break;
            }
        }
        
        if(check==false){
            return -1;
        }
        
        int g=0;
        
        for(int i=1;i<n;i++){
            g=__gcd(g,abs(arr[i]-arr[0]));
        }
        
        int ans=0;
        
        for(int i=1;i*i<=g;i++){
            if(g%i==0){
                ans++;
                if(i*i!=g){
                    ans++;
                }
            }
        }
        
        return ans;
    }
};