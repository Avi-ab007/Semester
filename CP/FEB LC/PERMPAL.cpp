#include <bits/stdc++.h>
using namespace std;


int main() {
	int t;
	cin>>t;
	while (t--) {
		string s;
		cin>>s;
		int len = s.length();
		int order[len];
		map<char, std::vector<int> > index;
		memset(order, -1, sizeof order);


		int freq[26] = {0};
		for (int i = 0; i < len; i++) {
			index[s[i]].push_back(i+1);
			freq[s[i] - 'a']++;
		}
		int odd = 0;
		for (int i = 0; i < 26; i++) {
			if (freq[i]%2)
				odd++;
		}
		bool flag = false;
		if ((len%2 == 1 && odd == 1) || (len%2 == 0 && odd == 0))
			flag = true;


		if (flag) {
			int beg = 0, end = len-1;
			for (int i = 0; i < 26; i++) {
				vector<int> v(index[i+'a'].begin(), index[i+'a'].end());

				if ((freq[i] > 0) && (freq[i]%2 == 0)) {
					for(int j = 0; j < v.size(); ) {
						order[beg++] = v[j++];
						order[end--] = v[j++];
					}
				} 
				else if ((freq[i] > 0) && (freq[i]%2 == 1)) {
					order[len/2] = v[0];
					for(int j = 1; j < v.size(); ) {
						order[beg++] = v[j++];
						order[end--] = v[j++];
					}
				}
			}
			for (int i = 0; i < len; i++)
				cout<<order[i]<<" ";
			cout<<endl;
		} else {
			cout<<-1<<endl;
		}
	}
}