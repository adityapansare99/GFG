#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> lexicographicallyLargest(vector<int> &arr) {
        // code here
        vector<int> ans=arr;
        int n=arr.size();
        int start=0;
        
        for(int i=0;i<n-1;i++){
            if(arr[i]%2!=arr[i+1]%2){
                sort(ans.begin()+start,ans.begin()+i+1,greater<int>());
                start=i+1;
            }
        }
        
        sort(ans.begin()+start,ans.end(),greater<int>());
        
        return ans;
    }
};