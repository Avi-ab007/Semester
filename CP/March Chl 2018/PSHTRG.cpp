#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

bool check(lli x, lli y, lli z) {
	return ((((x + y) > z) && ((y + z) > x) && ((x + z) > y)));
}

int main() {
	int n, q;
	cin>>n>>q;
	lli v[n+1];
	for (int i = 1; i <= n; i++)
		cin>>v[i];
	for (int i = 0; i < q; i++) {
		int qr, l, r, pos;
		lli val;
		cin>>qr;
		if (qr == 1) {
			cin>>pos>>val;
			v[pos] = val;
		}
		if (qr == 2) {
			cin>>l>>r;
			bool flag = false;
			lli _max = INT_MIN;
			vector<lli> arr(v + l, v + r + 1);
			int x = arr.size();
			sort(arr.begin(), arr.end());
			for (int i = x - 1; i >= 2; i--) {
				if (check(arr[i], arr[i-1], arr[i-2])) {
					_max = max(_max, (arr[i] + arr[i-1] + arr[i-2]));
					flag = true;
				}
			}
			if (flag)
				cout<<_max<<endl;
			else
				cout<<0<<endl;
		}
	}
}