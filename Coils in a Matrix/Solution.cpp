#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<vector<int>> formCoils(int n) {
        // code here
        int total=4*n*4*n;
        vector<int> firstCoil;

        for(int i=1;i<=total;i+=4*n){
            firstCoil.push_back(i);
        }

        int take=4*n-1;
        bool first=true;
        int c=0;

        while(firstCoil.size()<total/2){
            //go below
            int x=-1;
            if(!first){
                c++;
                if(c>2){
                    c=1;
                    take-=2;
                }

                x=take-1;
                for(int i=0;i<x;i++){
                    firstCoil.push_back(firstCoil.back()+4*n);
                }
            }

            if(firstCoil.size()>total/2){
                break;
            }

            //go right
            c++;
            if(c>2){
                take-=2;
                c=1;
            }

            x=take-1;
            for(int i=0;i<x;i++){
                firstCoil.push_back(firstCoil.back()+1);
            }

            if(firstCoil.size()>total/2){
                break;
            }

            //go up
            c++;
            if(c>2){
                take-=2;
                c=1;
            }

            x=take-1;
            for(int i=0;i<x;i++){
                firstCoil.push_back(firstCoil.back()-4*n);
            }

            if(firstCoil.size()>total/2){
                break;
            }

            //go left
            c++;
            if(c>2){
                take-=2;
                c=1;
            }

            x=take-1;
            for(int i=0;i<x;i++){
                firstCoil.push_back(firstCoil.back()-1);
            }

            first=false;

            if(firstCoil.size()>total/2){
                break;
            }

            if(take<3){
                break;
            }
        }


        vector<int> secondCoil;

        for(int i=total;i>0;i-=4*n){
            secondCoil.push_back(i);
        }

        first=true;
        c=0;
        take=4*n-1;

        while(secondCoil.size()<total/2){
            //go up
            int x=-1;
            if(!first){
                c++;
                if(c>2){
                    c=1;
                    take-=2;
                }

                x=take-1;
                for(int i=0;i<x;i++){
                    secondCoil.push_back(secondCoil.back()-4*n);
                }
            }

            if(secondCoil.size()>total/2){
                break;
            }

            //go left
            c++;
            if(c>2){
                take-=2;
                c=1;
            }

            x=take-1;
            for(int i=0;i<x;i++){
                secondCoil.push_back(secondCoil.back()-1);
            }

            if(secondCoil.size()>total/2){
                break;
            }

            //go below
            c++;
            if(c>2){
                c=1;
                take-=2;
            }

            x=take-1;
            for(int i=0;i<x;i++){
                secondCoil.push_back(secondCoil.back()+4*n);
            }

            if(secondCoil.size()>total/2){
                break;
            }

            //go right
            c++;
            if(c>2){
                take-=2;
                c=1;
            }

            x=take-1;
            for(int i=0;i<x;i++){
                secondCoil.push_back(secondCoil.back()+1);
            }

            if(secondCoil.size()>total/2){
                break;
            }

            if(take<3){
                break;
            }
            
            first=false;

        }

        return {firstCoil,secondCoil};
    }
};