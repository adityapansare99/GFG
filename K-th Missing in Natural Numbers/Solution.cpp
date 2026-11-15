#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int findKthSmall(vector<int>& arr, int k) {
        // code here
        sort(arr.begin(),arr.end());
        
        for(int i=0;i<arr.size();i++){
            if(arr[i]<=k){
                k++;
            }
            
            else{
                break;
            }
        }
        
        return k;
    }
};