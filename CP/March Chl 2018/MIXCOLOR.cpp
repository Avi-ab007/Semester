#include <bits/stdc++.h>
using namespace std;
typedef long int li;

int main() {
	int t;
	cin>>t;
	while (t--) {
		multimap<li, bool> color;
		int n;
		cin>>n;
		int dup = 0;
		li tmp;
		for (int i = 0; i < n; i++) {
			cin>>tmp;
			if (color.find(tmp) != color.end())
				dup++;
			color.insert(make_pair(tmp, true));
		} 
		cout<<dup<<endl;
	}
}