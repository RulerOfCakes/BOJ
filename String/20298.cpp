#include <bits/stdc++.h>

using namespace std;

int N, K;
vector<int> v1,v2;
int pi[2000002];
int res[2000002];
int cnt;

class segtree{
public:
    vector<int> tree;
    vector<int> cnt;
    int size;
    segtree(int n){
        for(size=1;size<=n;size*=2);
        tree.resize(size*2,0);
        cnt.resize(size*2,0);
    }
    void update(int pos, int x){
        int idx = pos+size-1;
        if(x==1){
            if(tree[idx]){
                cnt[idx]++;
            }
            else{
                while(idx){
                    tree[idx]+=1;
                    idx/=2;
                }
            }
        }
        else{
            if(cnt[idx]){
                cnt[idx]--;
            }
            else{
                if(!tree[idx]){
                    //cout << "WRONGACCESS\n";
                    return;
                }
                while(idx){
                    tree[idx]-=1;
                    idx/=2;
                }
            }
        }
    }
    int getsum(int node, int s, int e, int l, int r){
        if(s>r||e<l)return 0;
        if(l<=s&&e<=r)return tree[node];
        int mid = s+e>>1;
        return getsum(node*2,s,mid,l,r)+getsum(node*2+1,mid+1,e,l,r);
    }
};
segtree seg0(101010),seg01(101010);
int lim1,lim2;
void getPi(){
    int n = v2.size();
    for(int i = 1, mat=  0; i < n; ++i){
        int cur1 = seg0.getsum(1,1,seg0.size,1,v2[i]-1)+1;
        int cur2 = seg01.getsum(1,1,seg01.size,1,v2[mat]-1)+1;
        if(cur1==cur2){
            seg0.update(v2[i],1);
            seg01.update(v2[mat],1);
            pi[i] = ++mat;
        } else if(mat != 0){
            --i;
            int newmat=pi[mat-1];
            for(int j = i-mat+1; j <= i-newmat; j++){
                seg0.update(v2[j],0);
            }
            for(int j = newmat; j < mat; j++){
                seg01.update(v2[j],0);
            }
            mat=newmat;
        }
    }
}
segtree seg1(101010),seg2(101010);

void kmp(){
    int n = v1.size(), m = v2.size();
    //i: index, mat: number of matches
    for(int i = 0, mat = 0; i < n; i++){
        int cur1 = seg1.getsum(1,1,seg1.size,1,v1[i]-1)+1;
        int cur2 = seg2.getsum(1,1,seg2.size,1,v2[mat]-1)+1;
        int t1 = seg1.getsum(1,1,seg1.size,1,lim1)+1,
            t2 = seg2.getsum(1,1,seg2.size,1,lim2)+1;
        if(seg1.getsum(1,1,seg1.size,v1[i],v1[i]))t1--;
        if(seg2.getsum(1,1,seg2.size,v2[mat],v2[mat]))t2--;
        //cout << i << ' ' << mat << ' ' << t1 << '/' << cur1 << ":" << t2<<'/'<<cur2 << '\n';
        if((cur1==cur2)&&(t1==t2)){
            seg1.update(v1[i],1);
            seg2.update(v2[mat],1);
            if(++mat==m){
                res[cnt++] = i-m+1;
                int newmat = pi[mat-1];
                for(int j = i-mat+1; j <=i-newmat; j++){
                    seg1.update(v1[j],0);
                }
                // maybe newmat+1?
                for(int j = newmat; j < mat; j++){
                    seg2.update(v2[j],0);
                }
                mat=newmat;
            }
        }
        //not matched this time
        else if (mat != 0){
            //already have a few matches
            //start from the previous position(where a match was available)
            --i;
            
            //move number of matches to previous location
            int newmat=pi[mat-1];
            //update seg1 and seg2
            for(int j = i-mat+1; j <=i-newmat; j++){
                seg1.update(v1[j],0);
            }
            // maybe newmat+1?
            for(int j = newmat; j < mat; j++){
                seg2.update(v2[j],0);
            }
            mat=newmat;
        }
    }
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> K;
    vector<int> xlist,ylist;
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        ylist.push_back(a);
        v1.push_back(a);
    }
    for(int i = 0; i < K; i++){
        int a;
        cin >> a;
        xlist.push_back(a);
        v2.push_back(a);
    }
    sort(ylist.begin(),ylist.end());
    ylist.erase(unique(ylist.begin(),ylist.end()),ylist.end());
    sort(xlist.begin(),xlist.end());
    xlist.erase(unique(xlist.begin(),xlist.end()),xlist.end());
    map<int,int> idxs1,idxs2;
    for(int i = 0; i < ylist.size(); i++){
        idxs1[ylist[i]]=i+2;
    }
    for(int i = 0; i < N; i++){
        v1[i]=idxs1[v1[i]];
    }
    for(int i = 0; i < xlist.size(); i++){
        idxs2[xlist[i]]=i+2;
    }
    for(int i = 0; i < K; i++){
        v2[i]=idxs2[v2[i]];
    }
    lim1=ylist.size()+3,lim2=xlist.size()+3;
    for(int i = 0; i < K-1; i++){
        v1.push_back(v1[i]);
    }
    getPi();
    // for(int i =  0; i <= K; i++){
    //     cout << pi[i] << ' ';
    // }
    // cout << '\n';
    // for(int i = 1; i <= K; i++){
    //     pi[i]=i;
    // }
    kmp();
    
    cout << cnt;
    // for(int i = 0; i < cnt; i++){
    //     cout << res[i] << ' ';
    // }
}