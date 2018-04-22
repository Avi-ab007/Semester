#include <bits/stdc++.h>
using namespace std;
typedef long int lli;

int main() {
	int t;
	cin>>t;
	while (t--) {
		lli n, tmp;
		cin>>n;
		vector<lli> fl, gl;

		for (lli i = 0; i < n; i++) {
			cin>>tmp;
			fl.push_back(tmp);
		}

		for (lli i = 0; i < n; i++) {
			cin>>tmp;
			gl.push_back(tmp);
		}
		int dir = 1;
		bool front = true, back = true;
		for (lli i = 0; i < n; i++) {
			if (fl[i] > gl[i])
				front = false;
			if (fl[i] > gl[n - i -1])
				back = false;
		}
		if (front and back)
			cout<<"both\n";
		else if (front)
			cout<<"front\n";
		else if (back)
			cout<<"back\n";
		else cout<<"none\n";
	}
}