#include <bits/stdc++.h>
using namespace std;
typedef long int li;

int main() {
	int t;
	cin>>t;

	while (t--) {
		li n;
		cin>>n;
		double p, q, d;
		double cp = 0, loss = 0, sp = 0;
		for (li i = 0; i < n; i++) {
			cin>>p>>q>>d;
			double price = p*q;
			d = d/100.0;
			cp = price;
			sp = price*(1+d)*(1-d);
			loss += cp - sp;
		}
		cout<<std::setprecision(100)<<abs(loss)<<endl;
	}
}