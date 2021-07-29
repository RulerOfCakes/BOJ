#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
int N;
ll ans[11];

void sol(int n, int proc){
    while(n){
        ans[n%10]+=proc;
        n/=10;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    int start = 1, end = N, proc=1;
    while(start<=end){
        while(start%10!=0&&start<=end){
            sol(start,proc);
            start++;
        }
        if(start>end)break;
        while(end%10!=9&&start<=end){
            sol(end,proc);
            end--;
        }
        if(start>end)break;
        int tmp = (end/10-start/10+1);
        for(int i = 0; i <= 9; i++){
            ans[i]+=tmp*proc;
        }
        start/=10;
        end/=10;
        proc*=10;
    }
    for(int i= 0; i <= 9; i++){
        cout << ans[i] << ' ';
    }
    return 0;
}