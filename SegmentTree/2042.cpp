#include <bits/stdc++.h>

const int BIGNUM = 1000000007;

using namespace std;
int N, M, K;

class fwtree {
public:
	vector<long long> tree;
	vector<long long> numbers;
	int size;

	fwtree(int n) {
		for (size = 1; size < n; size *= 2);
		tree.resize(size + 1);
		numbers.resize(size + 1);
	}
	void update(int pos, long long x) {
		long long u = x - numbers[pos];
		numbers[pos] = x;
		while (pos <= size) {
			tree[pos] += u;
			pos += (pos & (-pos));
		}
	}
	long long sum(int pos) {
		long long ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			pos -= (pos & (-pos));
		}
		return ret;
	}
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int a, b;
    long long c;
	cin >> N >> M>>K;
	fwtree big(N);
	for (int i = 1; i <= N; i++) {
		cin >> a;
		big.update(i, a);
	}
	for (int i = 0; i < M+K; i++) {
		cin >> a >> b >> c;
		if (a == 1) {
			big.update(b, c);
		}
		else if (a == 2) {
			cout << big.sum(c) - big.sum(b-1) << "\n";
		}
	}
	
}