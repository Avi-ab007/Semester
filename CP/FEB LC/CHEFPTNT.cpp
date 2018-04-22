#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin>>t;
	int n, m, x, k;
	while (t--) {
		cin>>n>>m>>x>>k;
		string s;
		cin>>s;

		for (int i = 1; i <= m; i++) {
			int mcnt = 0;
			for (int j = 0; j < k; j++) {
				if (i%2 == 0 && (s[j] == 'E')){
					mcnt ++;
					s[j] = 'B';
				}
				else if (i%2 == 1 && (s[j] == 'O')) {
					mcnt ++;
					s[j] = 'B';
				}

				if (mcnt >= x) {
					mcnt = x;
					break;
				}
			}
			if (k < mcnt)
				mcnt = k;

			n -= mcnt;
		}

		if (n <= 0)
			printf("yes\n");
		else
			printf("no\n");
	}
}