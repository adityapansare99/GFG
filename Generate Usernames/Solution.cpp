#include<bits/stdc++.h>
using namespace std;    

class Solution {
  public:
    vector<string> generateUsernames(vector<string> arr) {
        // code here
        int n=arr.size();
        map<string,int> mp;
        vector<bool> covered(n,true);
        
        for(int i=0;i<n;i++){
            string temp=arr[i];
            
            mp[temp]++;
            
            if(mp[temp]==1){
                covered[i]=false;
            }
        }
        
        for(int i=0;i<n;i++){
            string temp=arr[i];
            
            if(!covered[i]){
                continue;
            }
            
            int c=1;
            
            int size=temp.size();
            
            while(mp.count(temp)){
                temp=temp.substr(0,size);
                temp+=to_string(c);
                c++;
            }
            
            arr[i]=temp;
            mp[temp]++;
        }
        
        return arr;
    }
};