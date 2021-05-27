#include <bits/stdc++.h>

using namespace std;

int A, B, C;

long double func(long double x){
    return A*x+B*sin(x);
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> A >> B >> C;
    //Ax+Bsinx=C
    long double ans=0, left = 0, right = 2e6;
    while(right-left>1e-11 && left <= right){
        long double mid = (right+left)/2;
        long double tmpans=func(mid);
        ans=mid;
        if(tmpans>(long double)C){
            right=mid;
            continue;
        }else if(tmpans<(long double)C){
            left=mid;
            continue;
        }else{
            
            break;
        }
    }
    cout<<fixed;
    cout.precision(11);
    cout << ans;
}