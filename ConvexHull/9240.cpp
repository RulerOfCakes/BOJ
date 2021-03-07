#include <bits/stdc++.h>

using namespace std;

using pi = pair<long long, long long>;

int N;
vector<pi> v;
vector<pi> cvhull;

int ccw(pi p1, pi p2, pi p3){
    long long sol = (p1.first*p2.second + p2.first*p3.second + p3.first*p1.second) - (p1.second*p2.first + p2.second*p3.first + p3.second*p1.first);
    return sol != 0LL ? (sol > 0LL ? 1 : -1) : 0;
}

long long dist(pi a, pi b){
    return (a.first - b.first)*(a.first - b.first) + (a.second - b.second)*(a.second - b.second);
}

pi nextv(int idx){
    pi nxt = cvhull[(idx+1)%cvhull.size()];
    return {cvhull[idx].first - nxt.first, cvhull[idx].second - nxt.second};
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
    
    cvhull.push_back(v[0]); cvhull.push_back(v[1]);
    int next = 2;
    while(next < N){
        while(cvhull.size() >= 2){
            auto second = cvhull.back(), first = cvhull[cvhull.size()-2];
            
            if(ccw(first, second, v[next])<=0){
                cvhull.pop_back();
            }
            else{
                break;
            }
        }
        cvhull.push_back(v[next++]);
    }

    
    int p1 = min_element(cvhull.begin(), cvhull.end())-cvhull.begin(),
        p2 = max_element(cvhull.begin(), cvhull.end())-cvhull.begin();
    long long ans = dist(cvhull[p1], cvhull[p2]);
    int cvsize = cvhull.size();
    for(int i = 0; i < N; i++){
        if(ccw(nextv(p1), {0, 0}, nextv(p2))>0){
            p1 = (p1+1)%cvsize;
        } else {
            p2 = (p2+1)%cvsize;
        }
        ans = max(ans, dist(cvhull[p1], cvhull[p2]));
    }
    cout.precision(12);
    cout << sqrt(ans);
}