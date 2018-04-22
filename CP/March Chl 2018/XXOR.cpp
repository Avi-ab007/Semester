#include <bits/stdc++.h>
using namespace std;
// typedef long int li;
typedef long long int uli;

int main() {
	ios_base::sync_with_stdio(false);
	int n, q;
	cin>>n>>q;
	int arr[n+1];
	int tree[n + 1][32];
	memset(tree, 0, sizeof tree);
	for (int i = 1; i <= n; i++)
		cin>>arr[i];

	for (int k = 0; k < 31; k++) {
		if (arr[1]&(1<<k)) 
			tree[1][k]++;
	}
	for (int k = 0; k < 31; k++) {
		for (int i = 2; i <= n; i++) {
			if (arr[i]&(1<<k))
				tree[i][k] = tree[i - 1][k] + 1;
			else
				tree[i][k]=tree[i-1][k];

		}
	}

	int l, r;
	for (int i = 0; i < q; i++) {
		cin>>l>>r;
		uli X=0;
		
		for (int k = 0; k < 31; k++) {
			uli cone = 0, czero = 0;
			cone = tree[r][k] - tree[l-1][k];
			czero = (r - l + 1) - cone;
			if(czero > cone) {
				X = X|(1<<k);
			}
		}
		cout<<X<<endl;
	}
}