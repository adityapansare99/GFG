#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int maxProduct(vector<int> &arr, int k) {
        // code here
        int n=arr.size();
        
        sort(arr.begin(),arr.end());
        
        long long mul=1;
        
        int i=0;
        int j=n-1;
        
        if(k%2==1){
            mul*=arr[j];
            j--;
            k--;
        }
        
        if(mul<0){
            long long temp=1;
            int x=n-1;
            while(k>=0 && x>=0){
                temp*=arr[x];
                x--;;
                k--;
            }
            
            return temp;
        }
        
        while(i<j && k>0){
            if(arr[i]*arr[i+1]>arr[j]*arr[j-1]){
                mul*=(arr[i]*arr[i+1]);
                k-=2;
                i+=2;
            }
            
            else{
                mul*=(arr[j]*arr[j-1]);
                k-=2;
                j-=2;
            }
        }
        
        return mul;
        
    }
};