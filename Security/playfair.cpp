#include <bits/stdc++.h>
using namespace std;

char mat[5][5];
std::map<char, pair<int, int> > matpos;
set<char> exist;
bool foundIJ;

bool addToTable(char x, int i, int j) {
	if (exist.find(x) == exist.end()) {
		mat[i][j] = x;
		exist.insert(x);
		matpos[x] = make_pair(i, j);
		if (x == 'i' || x == 'j') {
			exist.insert('i');
			exist.insert('j');
		}
		return true;
	} else {
		return false;
	}
}

string encode(string msg) {
	for (int i = 0; i < msg.length(); ) {
		int x1, y1, x2, y2;
		pair<int, int> coord1 = matpos[msg[i]];
		pair<int, int> coord2 = matpos[msg[i+1]];

		x1 = coord1.first;	y1 = coord1.second;
		x2 = coord2.first;	y2 = coord2.second;
		printf("(%d, %d), (%d, %d)\n", x1, y1, x2, y2);

		if ((x1 != x2) && y1 != y2) {
			msg[i] = mat[x1][y2];
			msg[i+1] = mat[x2][y1];
		} else if (x1 != x2) {
			msg[i] = mat[(x1 + 1)%5][y1];
			msg[i+1] = mat[(x2 + 1)%5][y1];
		} else {
			msg[i] = mat[x1][(y1 + 1)%5];
			msg[i+1] = mat[x1][(y2 + 1)%5];
		}

		i+= 2;
	}

	return msg;
}

string decode(string cipher) {
	for (int i = 0; i < cipher.length(); ) {
		int x1, y1, x2, y2;
		pair<int, int> coord1 = matpos[cipher[i]];
		pair<int, int> coord2 = matpos[cipher[i+1]];

		x1 = coord1.first;	y1 = coord1.second;
		x2 = coord2.first;	y2 = coord2.second;
		// printf("(%d, %d), (%d, %d)\n", x1, y1, x2, y2);

		if ((x1 != x2) && y1 != y2) {
			cipher[i] = mat[x1][y2];
			cipher[i+1] = mat[x2][y1];
		} else if (x1 != x2) {
			cipher[i] = mat[(x1 - 1)%5][y1];
			cipher[i+1] = mat[(x2 - 1)%5][y1];
		} else {
			cipher[i] = mat[x1][(y1 - 1)%5];
			cipher[i+1] = mat[x1][(y2 - 1)%5];
		}

		i+= 2;
	}

	return cipher;
}

int main() {
	string key;
	cin>>key;
	foundIJ = false;

	char alph = 'a';
	int k = 0, size = key.length();
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; ) {
			if (k < size) {
				if (addToTable(key[k], i, j))
					j++;
				k++;
			} else {
				if (addToTable(alph, i, j))
					j++;
				alph++;
			}
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			cout<<mat[i][j]<<" ";
		cout<<endl;
	}

	string var;
	cin>>var;

	string msg = "";

	int i = 0, j = 0;
	while (i < var.length()) {
		msg.push_back(var[i]);
        i++;
        if (i == var.size()) {
            msg.push_back('x');
            break;
        }
        if (var[i] == msg[j]) {
            msg.push_back('x');
            j++;
        }
        else if(var[i] != msg[j]) {
            j++;
            msg.push_back(var[i]);
            i += 1;
        }
        j++;
	}

	cout<<msg<<endl;

	string cipher = encode(msg);
	string origmsg = decode(cipher);

	for (int i = 0; i < origmsg.length(); i++) {
		if (origmsg[i] == 'x') {
			string ftmp = origmsg.substr(0, i);
			string stmp = origmsg.substr(i+1);
			origmsg = ftmp;
			origmsg += stmp;
		}
	}

	cout<<"Encrypted Message: "<<cipher<<endl;
	cout<<"Decrypted Message: "<<origmsg<<endl;
	
}
