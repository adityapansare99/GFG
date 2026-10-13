#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    string findRollOut(string& s, vector<int>& roll) {
        // code here
        int n=s.size();
        int m=roll.size();
        
        vector<int> suff(n,0);
        
        for(int i=0;i<m;i++){
            suff[roll[i]-1]++;
        }
        
        for(int i=n-2;i>=0;i--){
            suff[i]+=suff[i+1];
        }
        
        for(int i=0;i<n;i++){
            s[i]=(((s[i]-'a')+suff[i])%26)+'a';
        }
        
        return s;
    }
};
