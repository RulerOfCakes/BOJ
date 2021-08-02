#include <bits/stdc++.h>

using namespace std;

int N, K;
bool prime[100002];


int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    string s;
    cin >> s;
    vector<int> stones;
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        stones.push_back(a);
    }
    if(N<=2){
        cout << 0;
        return 0;
    }
    deque<int> arr;
    int prev=0; char prevc;
    for(int i = 0; i < N; i++){
        if(i==0){
            prevc=s[i];
            prev=stones[i];
            continue;
        }
        if(s[i]!=prevc){
            arr.push_back(prev);
            prev=stones[i];
            prevc=s[i];
        }
        else{
            prev=max(stones[i],prev);
        }
    }
    arr.push_back(prev);
    
    arr.pop_back();
    if(!arr.empty())
    arr.pop_front();
    if(!arr.empty())
    sort(arr.begin(),arr.end(),greater<int>());
    long long ans = 0;
    for(int i = 0; i <(arr.size())/2+arr.size()%2; i++){
        ans+=arr[i];
    }
    cout << ans;   
}