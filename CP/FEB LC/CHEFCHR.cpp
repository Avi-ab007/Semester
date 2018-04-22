#include <bits/stdc++.h>
using namespace std;

bool isChef(char x) {
	return ((x == 'c') || (x == 'h') || (x == 'e') || (x == 'f'));
}

bool check(string s) {
	string a = "chef";
	int cnt[256] = {0}, i;
	for (i = 0; i < 4; i++) {
		cnt[s[i]]++;
		cnt[a[i]]--;
	}
	for (i = 0; i < 256; i++) {
		if (cnt[i] != 0)
			return false;
	}
	return true;
}
int main() {
	int t;
	cin>>t;
	while (t--) {
		string s;
		cin>>s;
		int cnt = 0, match = 0, len = s.length();
		for (int i = 0; i < len; i++) {
			int j = i;
			match = 0;
			if (isChef(s[j])) {
				j++;
				match++;
				while (isChef(s[j])) {
					j++;
					match++;
					if (match == 4) {
						if (check(s.substr(i, 4)))
							cnt++;
						break;
					}
				}
				if (match < 4)
					i = j;
			}
		}
		if (cnt > 0) 
			printf("lovely %d\n", cnt);
		else 
			printf("normal\n");
	}
}