#include <bits/stdc++.h>

using namespace std;

using pi = pair<long long, long long>;

int N;
vector<pi> v;

int ccw(pi &p1, pi &p2, pi &p3){
    long long sol = (p1.first*p2.second + p2.first*p3.second + p3.first*p1.second) - (p1.second*p2.first + p2.second*p3.first + p3.second*p1.first);
    return sol != 0LL ? (sol > 0LL ? 1 : -1) : 0;
}

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
    pi lowest = {100000, 100000};
    int idx = 0;
    for(int i = 0; i < N; i++){
        pi temp;
        cin >> temp.first >> temp.second;
        v.push_back(temp);
        if(lowest > temp){
            lowest = temp;
            idx = i;
        }
    }
    swap(v[0], v[idx]);
    sort(v.begin()+1, v.end(), comp);
    stack<int> s;
    s.push(0); s.push(1);
    int next = 2;
    while(next < N){
        while(s.size() >= 2){
            int second = s.top();
            s.pop();
            int first = s.top();
            if(ccw(v[first], v[second], v[next])>0){
                s.push(second);
                break;
            }
        }
        s.push(next++);
    }

    cout << s.size();
}