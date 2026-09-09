#include<bits/stdc++.h>
using namespace std;

class Solution {
    private:
    int ans;
    int mx;
    
    void solver(int i,int n,string &str,int currSum,int val,int choose){
        if(i==n){
            if(currSum>mx){
                ans=val;
                mx=currSum;
            }
            
            else if(currSum==mx){
                ans=max(ans,val);
            }
            
            return;
        }
        
        if(choose){
            solver(i+1,n,str,currSum+9,val*10+9,choose);
        }
        
        else{
            int temp=str[i]-'0';
            solver(i+1,n,str,currSum+temp,val*10+temp,0);
            solver(i+1,n,str,currSum+temp-1,val*10+temp-1,1);
        }
    }
  public:
    int findMax(int n) {
        // code Here
        mx=0;
        ans=0;
        
        string str=to_string(n);
        
        solver(0,str.size(),str,0,0,0);
        
        return ans;
    }
};
