#include<bits/stdc++.h>
using namespace std;

vector<int> fn(string ip){
   stringstream ss(ip);
   vector<int> res;
   string temp;
   while(getline(ss,temp,'.')){
      res.push_back(temp);
   }
   return res;
}
int main(){
    string ip;cin>>ip;
    int cidr;cin>>cidr;
    vector<int> vip=fn(ip);
    vector<int> mask(4,0);
    int bits=cidr;
    for(int i=0;i<4;i++){
        if(bits>=8){
            mask[i]=255;
            bits-=8;
        }else{
            mask[i]=256-pow(2,8-bits);
            bits=0;
        }
    }
    vector<int> nw(4,0);
    for(int i=0;i<4;i++){
        nw[i]=vip[i]&mask[i];
    }
    vector<int> bc(4,0);
    for(int i=0;i<4;i++){
        bc[i]=nw[i]|(~(mask[i])&255);
    }
    int host=pow(2,32-cidr)-2;
    cout<<"MASK is : "<<to_string(mask[0])+"."to_string(mask[1])+"."to_string(mask[2])+"."to_string(mask[3]);
    cout<<"Broadcast is : "<<to_string(bc[0])+"."to_string(bc[1])+"."to_string(bc[2])+"."to_string(bc[3]);
    cout<<"network  is : "<<to_string(nw[0])+"."to_string(nw[1])+"."to_string(nw[2])+"."to_string(nw[3]);
    cout<<"HOST is"<<host>>endl;

    return 0;
}