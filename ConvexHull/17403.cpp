#include <bits/stdc++.h>

using namespace std;

using pi = pair<long long, long long>;

int N;
vector<pi> v;
vector<pi> newv;

// int ccw(pi p1, pi p2){
//     long long ret = p1.first*p2.second - p2.first*p1.second;
//     if(ret<0)return -1;
//     else if (ret>0) return 1;
//     else return 0;
// }

int ccw(pi p1, pi p2, pi p3)
{
    long long sol = (p1.first * p2.second + p2.first * p3.second + p3.first * p1.second) - (p1.second * p2.first + p2.second * p3.first + p3.second * p1.first);
    return sol != 0LL ? (sol > 0LL ? 1 : -1) : 0;
}

long long dist(pi a, pi b)
{
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

bool comp(pi &p1, pi &p2)
{
    int val = ccw(newv[0], p1, p2);
    if (val != 0)
        return val > 0 ? true : false;
    if (p1.first == p2.first)
        return p1.second < p2.second;
    return p1.first < p2.first;
}
int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N;
    pi lowest = {100000 + 5, 100000 + 5};
    int idx = 0;
    map<pi,int> mp;
    for (int i = 0; i < N; i++)
    {
        pi temp;
        cin >> temp.first >> temp.second;
        v.push_back(temp);
        mp[temp]=i;
        if (lowest > temp)
        {
            lowest = temp;
            idx = i;
        }
    }
    vector<int> ansv(N);
    swap(v[0], v[idx]);
    int ans = 1;
    newv=vector<pi>(v.begin(), v.end());
 
    while (newv.size() >= 3)
    {
        
        vector<pi> cvhull;
        lowest = {1e6 + 5, 1e6 + 5};
        idx = 0;
        sort(newv.begin() + 1, newv.end(), comp);
        vector<pi> nextv(newv.begin(), newv.end());
        newv = vector<pi>();

        cvhull.push_back(nextv[0]);
        
        cvhull.push_back(nextv[1]);
        

        int next = 2;
        while (next < nextv.size())
        {

            while (cvhull.size() >= 2)
            {
                auto second = cvhull.back(), first = cvhull[cvhull.size() - 2];

                if (ccw(first, second, nextv[next]) <= 0)
                {
                    cvhull.pop_back();
                }
                else
                {
                    break;
                }
            }
            cvhull.push_back(nextv[next++]);
        }
        
        if(cvhull.size()<3)break;
        set<pi>checker(cvhull.begin(),cvhull.end());

        for(int i = 0; i < nextv.size(); i++){
            if(!checker.count(nextv[i])){
                newv.push_back(nextv[i]);
                if(lowest>nextv[i]){
                    lowest=nextv[i];
                    idx=newv.size()-1;
                }
            }
            else{
                ansv[mp[nextv[i]]]=ans;
            }
        }
        
        if (newv.size() < 3)
            break;
        swap(newv[0],newv[idx]);
        ans++;
    }
    for(int i = 0; i < N; i++){
        cout << ansv[i] << ' ';
    }
}