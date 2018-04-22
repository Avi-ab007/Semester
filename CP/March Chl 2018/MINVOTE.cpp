#include <bits/stdc++.h>
using namespace std;
typedef long int li;

int main() {
	int t;
	cin>>t;

	while (t--) {
		li n;
		cin>>n;
		li inf[n], lsum[n], vote1[n], vote2[n];
		memset(lsum, 0, sizeof lsum);
		memset(vote1, 0, sizeof vote1);
		memset(vote2, 0, sizeof vote2);

		for (li i = 0; i < n; i++) 
			cin>>inf[i];
		
		lsum[0] = inf[0];
		for (int i = 1; i < n; i++) {
			lsum[i] = lsum[i-1] + inf[i];
		}

		int lcast[n], rcast[n];
		memset(lcast, -1, sizeof lcast);
		memset(rcast, -1, sizeof rcast);
		for (int i = 0; i < n; i++) {
			int low = i + 1, high = n-1;
			int ans = INT_MIN;
			while (low <= high) {
				int mid = (low + high)/2;
				if (lsum[mid - 1] - lsum[i] <= inf[i]) {
					ans = max(ans, mid);
					low = mid + 1;
				} else high = mid - 1;
			}
			if (ans == INT_MIN)
				ans = -1;
			lcast[i] = ans;
			// cout<<ans<<" ";
		}
		// cout<<endl;

		for (int i = n - 1; i >= 0; i--) {
			int low = 0, high = i - 1;
			int ans = INT_MAX;
			while (low <= high) {
				int mid = (low + high)/2;
				if ((lsum[i - 1] - lsum[mid]) <= inf[i]) {
					ans = min(ans, mid);
					high = mid - 1;
				} else low = mid + 1;
			}
			if (ans == INT_MAX)
				ans = -1;
			rcast[i] = ans;
			// cout<<ans<<" ";
		}
		// cout<<endl;

		for (int i = 0; i < n - 1; i++) {
			vote1[i+1] += 1;
			if (lcast[i] < n-1)
				vote1[lcast[i] + 1] -= 1;
		}
		for (int i = 1; i < n; i++)
			vote1[i] += vote1[i-1];

		for (int i = 1; i < n; i++) {
			vote2[rcast[i]] += 1;
			vote2[i] -= 1;
		}
		for (int i = 1; i < n; i++)
			vote2[i] += vote2[i-1];

		for (int i = 0; i < n; i++)
			cout<<(vote1[i] + vote2[i])<<" ";
		cout<<endl;
	}
}