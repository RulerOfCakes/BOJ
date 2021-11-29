#include <bits/stdc++.h>
using namespace std;

int N,K;
int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    vector<int> v(N),sv(N);
    for(int i = 0; i < N; i++){
        cin >> v[i];
        sv[i]=v[i];
    }
    cin >> K;
    deque<int> dq;
    while(K--){
        int a,b;
        cin >> a >> b;
        b=-b;
        while(!dq.empty()&&abs(dq.front())<=abs(a)){
            dq.pop_front();
        }
        dq.push_front(a);
        while(!dq.empty()&&abs(dq.front())<=abs(b)){
            dq.pop_front();
        }
        dq.push_front(b);
    }
    sort(v.begin(),v.begin()+abs(dq.back()));
    int cdx=abs(dq.back())-1;
    int i1=0,i2=abs(dq.back())-1;

    while(!dq.empty()){
        int cx = dq.back();
        dq.pop_back();
        int nx;
        if(dq.empty()){
            nx=0;
        }
        else{
            nx=dq.back();
        }
        int diff = abs(cx)-abs(nx);
        if(cx>0){
            while(diff>0){
                diff--;
                sv[cdx--]=v[i2--];
            }
        }
        else{
            while(diff>0){
                diff--;
                sv[cdx--]=v[i1++];
            }
            
        }
    }
    for(int x : sv){
        cout << x << ' ';
    }
}