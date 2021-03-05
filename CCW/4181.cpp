#include <bits/stdc++.h>

using namespace std;

using pi = pair<long long, long long>;

int N;

vector<pi> v;

int ccw(pi &p1, pi &p2, pi &p3){
    long long sol = (p1.first*p2.second + p2.first*p3.second + p3.first*p1.second) - (p1.second*p2.first + p2.second*p3.first + p3.second*p1.first);
    return sol != 0LL ? (sol > 0LL ? 1 : -1) : 0;
}
/*
int dot(pi &p1, pi &p2, pi &p3){
    long long sol = (p2.first - p1.first)*(p3.first-p2.first) + (p2.second-p1.second)*(p3.second-p2.second);
    return sol > 0 ? 1 : -1;
}
*/
bool comp(pi &p1, pi &p2){
    int val = ccw(v[0], p1, p2);
    if(val!=0) return val>0?true:false;
    if(p1.first == p2.first)return p1.second<p2.second;
    return p1.first<p2.first;
}
int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    pi lowest = {INT_MAX, INT_MAX};
    
    int idx = 0, minus = 0;
    for(int i = 0; i < N; i++){
        pi temp; char chk;
        cin >> temp.first >> temp.second >> chk;
        if(chk == 'N'){
            minus++;
            continue;
        }
        v.push_back(temp);
        if(lowest > temp){
            lowest = temp;
            idx = i - minus;
        }
    }
    swap(v[0], v[idx]);
    sort(v.begin()+1, v.end(), comp);
    for(int i = N-1 - minus; i > 1; i--){
            if(ccw(v[0], v[i], v[i-1])){
                reverse(v.begin()+i, v.begin() + N - minus);
                break;
            }
        }
    cout << v.size() << '\n';
    for(auto t : v){
        cout << t.first << ' ' << t.second << '\n';
    }
}