#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> update(int n, vector<int>& updates) {
        // code here
        vector<int> res(n,0);
        sort(updates.begin(),updates.end());
        int i=n-1;
        int j=updates.size()-1;
        
        while(i>=0 && j>=0){
            int val=updates[j]-1;
            
            if(i>=val){
                res[i--]=j+1;
            }
            
            else{
                j--;
            }
        }
        
        return res;
    }
};