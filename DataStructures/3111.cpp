#include <bits/stdc++.h>
using namespace std;

string cmp,os;
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> cmp >> os;
    bool flip=0;
    deque<char> ldq,rdq;
    int l=0,r=os.length()-1;
    while(l<=r){
        //front
        while(l<=r){
            bool found=0;
            ldq.push_back(os[l++]);
            if(ldq.size()>=cmp.size()){
                found=1;
                for(int i = 0; i < cmp.size(); i++){
                    if(cmp[i]!=ldq[ldq.size()-cmp.size()+i]){
                        found=0;
                        break;
                    }
                }
            }
            if(found){
                for(int i = 0; i < cmp.size(); i++)ldq.pop_back();
                break;
            }
        }
        //back
        while(l<=r){
            bool found=0;
            rdq.push_front(os[r--]);
            if(rdq.size()>=cmp.size()){
                found=1;
                for(int i =0 ; i < cmp.size(); i++){
                    if(cmp[i]!=rdq[i]){
                        found=0;break;
                    }
                }
            }
            if(found){
                for(int i = 0; i < cmp.size(); i++)rdq.pop_front();
                break;
            }
        }
    }
    string ans;
    for(int i = 0; i < ldq.size(); i++){
        ans+=ldq[i];
    }
    for(int i = 0; i < rdq.size(); i++){
        ans+=rdq[i];
    }
    
    while(ans.find(cmp)!=ans.npos){
        ans.erase(ans.find(cmp),cmp.size());
    }
    cout << ans;
}