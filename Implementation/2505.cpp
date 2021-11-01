#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int,int>;

int N;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> N;
    vector<int> v(N+1);
    for(int i = 1; i <= N; i++){
        cin >> v[i];
    }
    vector<int> rv(v.begin(),v.end());
    bool solved=1;
    pi p1={1,1},p2={1,1};
    bool f1=0,f2=0;
    for(int i = 1; i <= N; i++){
        if(!f1&&i!=v[i]){
            f1=1;
            p1.first=i;
        }
        else if(f1&&v[i]==p1.first){
            p1.second=i;
            break;
        }
    }
    reverse(v.begin()+p1.first,v.begin()+p1.second+1);
    for(int i = 1; i <= N; i++){
        if(!f2&&i!=v[i]){
            f2=1;
            p2.first=i;
        }
        else if(f2&&v[i]==p2.first){
            p2.second=i;
            break;
        }
    }
    reverse(v.begin()+p2.first,v.begin()+p2.second+1);
    // cout << p1.first << ' ' << p1.second << '\n' << p2.first << ' ' << p2.second << endl;
    // for(int i = 1; i <= N; i++){
    //     cout << v[i] << ' ';
    // }
    // cout << endl;
    for(int i = 1; i <= N; i++){
        if(i!=v[i]){
            solved=0;break;
        }
    }
    if(!solved){
        solved=1;
        //cout << "HA\n";
        p1={1,1},p2={1,1};
        f1=0,f2=0;
        for(int i = N; i > 0; i--){
            if(!f1&&i!=rv[i]){
                f1=1;
                p1.second=i;
            }
            else if(f1&&rv[i]==p1.second){
                p1.first=i;
                break;
            }
        }
        reverse(rv.begin()+p1.first,rv.begin()+p1.second+1);
        for(int i = N; i > 0; i--){
            if(!f2&&i!=rv[i]){
                f2=1;
                p2.second=i;
            }
            else if(f2&&rv[i]==p2.second){
                p2.first=i;
                break;
            }
        }
        reverse(rv.begin()+p2.first,rv.begin()+p2.second+1);
        for(int i = 1; i <= N; i++){
            if(i!=rv[i]){
                solved=0;break;
            }
        }
    }
    assert(solved);
    cout << p1.first << ' ' << p1.second << '\n' << p2.first << ' ' << p2.second;
}