#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin>>t;
	while(t--) {
		int n,u,d;
		cin>>n>>u>>d;

		int hill[n];
		bool parachute = true;
		int pos = 0;
		for (int i = 0; i < n; i++) {
			cin>>hill[i];
		}

		for (int i = 1; i < n; i++) {
			if ((hill[i] >= hill[pos]) and ((hill[i] - hill[pos]) <= u))
				pos = i;
			else if ((hill[i] < hill[pos])) {
				if ((hill[pos] - hill[i]) <= d)
					pos = i;
				else if (parachute) {
					parachute = false;
					pos = i;
				} else break;
			} else break;
		}
		cout<<(pos + 1)<<endl;
	}
}