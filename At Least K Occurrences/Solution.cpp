#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int firstElementKTime(vector<int>& arr, int k) {
        // code here
        int n=arr.size();
        map<int,int> mp;
        
        for(int i=0;i<n;i++){
            mp[arr[i]]++;
            
            if(mp[arr[i]]>=k){
                return arr[i];
            }
        }
        
        return -1;
    }
};