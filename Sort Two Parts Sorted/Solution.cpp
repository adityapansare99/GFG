#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    void mergeTwoParts(vector<int>& arr) {
        // code here
        int n=arr.size();
        int gap=n/2+n%2;
        
        while(gap>0){
            int left=0;
            int right=left+gap;
            
            while(right<n){
                if(arr[left]>arr[right]){
                    swap(arr[left],arr[right]);
                }
                
                left++;
                right++;
            }
            
            if(gap==1){
                break;
            }
            
            gap=gap/2+gap%2;
        }
    }
};