#include <bits/stdc++.h>

using namespace std;

int N;
bool prime[100002];

long long sol(int n){
    vector<int> divisor, power;
    long long ret = 1;
    for(int i = 2; i <= 100000; i++){
        if(!prime[i] && n%i==0){
            divisor.push_back(i);
            int cnt = 0;
            while(n%i==0){
                n /= i;
                cnt++;
            }
            power.push_back(cnt);
        }
    }
    for(int i = 0; i < divisor.size(); i++){
        ret *= ((int)pow(divisor[i], power[i])) - (int)(pow(divisor[i], power[i]-1));
    }
    if(n==1){
        return ret;
    } else {
        return ret*(n-1);
    }
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    for(int i = 2; i <= 100000; i++){
        if(!prime[i]){
            for(int j = 2 * i; j <= 100000; j += i){
                prime[j] = 1;
            }
        }
    }
    cin >> N;
    while(N){
        cout << sol(N) << '\n';
        cin >> N;
    }
}