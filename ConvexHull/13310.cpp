#include <bits/stdc++.h>

using namespace std;

using pi = pair<long long, long long>;
using ll = long long;

int T, N;
vector<pi> v,iv,dv;
vector<pi> cvhull;
int ccw(pi p1, pi p2){
    long long ret = p1.first*p2.second - p2.first*p1.second;
    if(ret<0)return -1;
    else if (ret>0) return 1;
    else return 0;
}

int ccw(pi p1, pi p2, pi p3)
{
    return ccw({p1.first-p3.first, p1.second-p3.second}, {p2.first-p3.first, p2.second-p3.second});
}

long long dist(pi a, pi b)
{
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

pi nextv(int idx)
{
    pi nxt = cvhull[(idx + 1) % cvhull.size()];
    return {cvhull[idx].first - nxt.first, cvhull[idx].second - nxt.second};
}

bool comp(pi &p1, pi &p2)
{
    int val = ccw(v[0], p1, p2);
    if (val != 0)
        return val > 0 ? true : false;
    if (p1.first == p2.first)
        return p1.second < p2.second;
    return p1.first < p2.first;
}

//creates a cvhull in cvhull vector(assuming v is sorted in correct ccw order)
void convex_hull(){
    cvhull.clear();
    cvhull.push_back(v[0]);
    cvhull.push_back(v[1]);
    int next = 2;
    while (next < N)
    {
        while (cvhull.size() >= 2)
        {
            auto second = cvhull.back(), first = cvhull[cvhull.size() - 2];
            if (ccw(first, second, v[next]) <= 0)
            {
                cvhull.pop_back();
            }
            else
            {
                break;
            }
        }
        cvhull.push_back(v[next++]);
    }
}

ll rcalipers(){
    int j  = 1;
    long long ans = 0;
    pi ans1, ans2;
    int cvsize = cvhull.size();
    for (int i = 0; i < cvhull.size(); i++)
    {
        while(i!=j && ccw(nextv(i), nextv(j)) > 0){
            j = (j+1)%cvsize;
            
        }
        if (ans < dist(cvhull[i], cvhull[j]))
        {
            ans = dist(cvhull[i], cvhull[j]);
            ans1 = cvhull[i];
            ans2 = cvhull[j];
        }
    }
    return ans;
}

ll sol(int x){
    for(int i = 0; i < N; i++){
        v[i]={iv[i].first+dv[i].first*x, iv[i].second+dv[i].second*x};
    }
    swap(v[0],*min_element(v.begin(),v.end()));
    sort(v.begin()+1,v.end(),comp);
    convex_hull();
    ll ret = rcalipers();
    return ret;
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> T;
    
    
    for (int i = 0; i < N; i++)
    {
        pi temp,temp2;
        cin >> temp.first >> temp.second >> temp2.first >> temp2.second;
        iv.push_back(temp);
        dv.push_back(temp2);
    }
    v.resize(N,{0,0});
    
    int s=0,e=T;
    while(s+3<=e){
        int l = (2*s+e)/3,r=(s+2*e)/3;
        if(sol(l)>sol(r))s=l;
        else e=r;
    }
    ll ans = 1e18;
    int idx=s;
    for(int i = s; i <= e; i++){
        ll tmp = sol(i);
        if(ans>tmp){
            ans=tmp;
            idx=i;
        }
    }
    cout << idx << '\n' << ans;
}