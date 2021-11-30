#include <bits/stdc++.h>

using namespace std;

int N, K;
vector<int> v1,v2;
int pi[1001002];
int res[1001002];
int cnt;

class segtree{
public:
    vector<int> tree;
    int size;
    segtree(){}
    segtree(int n){
        for(size=1;size<=n;size*=2);
        tree.resize(size*2,0);
    }
    void update(int x, int v){ for(x++; x<size*2; x+=x&-x) tree[x] += v; }
    int query(int x){ int ret = 0; for(x++; x; x^=x&-x) ret += tree[x]; return ret; }
    int getsum(int s, int e){ return query(e) - query(s-1); }
};
segtree seg;
//preprocessing segtree queries for pattern string
vector<int> lv,gv;
int lim1,lim2;

bool valid(int mat, int idx, segtree& sg){
    int lwr = sg.getsum(1,idx-1);
    if((lv[mat]!=lwr)||
        (gv[mat]!=sg.getsum(idx+1,sg.size-1)))return false;
    else return true;
}

void getPi(){
    int n = v2.size();
    lv.resize(n);gv.resize(n);
    seg=segtree(lim2);
    for(int i = 0; i < n; i++){
        lv[i]=seg.getsum(1,v2[i]-1);
        gv[i]=seg.getsum(v2[i]+1,seg.size-1);
        seg.update(v2[i],1);
    }
    seg=segtree(lim2);
    for(int i = 1, mat=  0; i < n; ++i){
        while(mat&&!valid(mat,v2[i],seg)){
            int newmat=pi[mat-1];
            for(int j = i-mat; j < i-newmat; j++){
                seg.update(v2[j],-1);
            }
            mat=newmat;
        }
        if(valid(mat,v2[i],seg)){
            seg.update(v2[i],1);
            pi[i]=++mat;
        }
    }
}

void kmp(){
    int n = v1.size(), m = v2.size();
    seg=segtree(lim1);
    //i: index, mat: number of matches
    for(int i = 0, mat = 0; i < n; i++){
        while(mat&&!valid(mat,v1[i],seg)){
            int newmat=pi[mat-1];
            for(int j = i-mat; j < i-newmat; j++){
                seg.update(v1[j],-1);
            }
            mat=newmat;
        }
        if(valid(mat,v1[i],seg)){
            if(++mat==m){
                res[cnt++]=i-m+1;
                int newmat=pi[mat-1];
                for(int j = i-mat+1; j < i-newmat+1; j++){
                    seg.update(v1[j],-1);
                }
                mat=newmat;
            }
            seg.update(v1[i],1);
        }
    }
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> K >> N;
    vector<int> ylist;
    vector<int> tv2;
    for(int i = 0; i < K; i++){
        int a;
        cin >> a;
        tv2.push_back(a);
    }
    v2.resize(K);
    for(int i = 0; i < K; i++){
        v2[tv2[i]-1]=i+1;
    }
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        ylist.push_back(a);
        v1.push_back(a);
    }
    
    sort(ylist.begin(),ylist.end());

    map<int,int> idxs1;
    for(int i = 0; i < ylist.size(); i++){
        idxs1[ylist[i]]=i+2;
    }
    for(int i = 0; i < N; i++){
        v1[i]=idxs1[v1[i]];
    }
    
    lim1=ylist.size()+3,lim2=v2.size()+3;

    getPi();

    kmp();
    
    cout << cnt << '\n';
    
    for(int i = 0; i < cnt; i++){
        cout << res[i]+1 << ' ';
    }
}