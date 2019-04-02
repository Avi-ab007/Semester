#include <bits/stdc++.h>
#include <gmp.h>
using namespace std;

int _mod(vector<int> res, int n) {
    int ans = 0;
    for (int i = 0; i < res.size(); i++) {
        ans = (ans*10 + res[i])%n;
    }
    return ans;
}

void printVector(vector<int> a) {
    for (int i = 0; i < a.size(); i++)
        cout<<a[i];
    
}

bool isSmaller(vector<int> a, vector<int> b) {
    int a_len = a.size();
    int b_len = b.size();

    if (a_len < b_len)
    return true;
    if (b_len < a_len)
    return false;
 
    for (int i = 0; i < a_len; i++) {
        if (a[i] < b[i])
            return true;
        else if (a[i] > b[i])
            return false;
    }
 
    return false;
}

void modularSum(vector<int> a, vector<int> b, int n) {

    vector<int> res;

    int carry = 0, sum = 0;
    if (a.size() > b.size())
        a.swap(b);

    int a_len = a.size();
    int b_len = b.size();
    int diff = b_len - a_len;

    for (int i = a_len - 1; i >= 0; i--) {
        int sum = (a[i] + b[i+diff] + carry);
        res.push_back(sum%10);
        carry = sum/10;
    }

    for (int i = b_len - a_len - 1; i >= 0; i--) {
        int sum = (b[i] + carry);
        res.push_back(sum%10);
        carry = sum/10;
    }

    if (carry)
        res.push_back(carry);

    reverse(res.begin(), res.end());

    cout<<"Sum: ";
    printVector(res);
    cout<<": "<<_mod(res, n)<<endl;
}

void modularDiff(vector<int> a, vector<int> b, int n) {
    if (isSmaller(a, b))
        a.swap(b);
 
    vector<int> res;
 
    int a_len = a.size();
    int b_len = b.size();

    int diff = a_len - b_len;

    int carry = 0;

    for (int i = b_len-1; i >= 0; i--) {
        int sub = (a[i + diff] - b[i] - carry);
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
 
        res.push_back(sub);
    }

    for (int i = a_len - b_len-1; i >= 0; i--) {
        if (a[i] == 0 && carry) {
            res.push_back(9);
            continue;
        }
        int sub = (a[i] - carry);
        if (i > 0 || sub > 0)
            res.push_back(sub);
        carry = 0;
 
    }

    reverse(res.begin(), res.end());
    cout<<"Difference: "; 
    printVector(res);
    cout<<": "<<_mod(res, n)<<endl;
}

void modularProd(vector<int> a, vector<int> b, int n) {

    cout<<"Product: ";

    int a_len = a.size();
    int b_len = b.size();
    if (a_len == 0 || b_len == 0) {
       cout<<0;
       return;
    }
 

    vector<int> res(a_len + b_len, 0);
    int i_a = 0; 
    int i_b = 0; 

    for (int i = a_len - 1; i >= 0; i--) {
        int carry = 0;
        int a_len = a[i];

        i_b = 0;
        
        for (int j = b_len-1; j >= 0; j--) {
            int b_len = b[j];

            int sum = a_len*b_len + res[i_a + i_b] + carry;

            carry = sum/10;

            res[i_a + i_b] = sum % 10;
 
            i_b++;
        }

        if (carry > 0)
            res[i_a + i_b] += carry;

        i_a++;
    }

    int i = res.size() - 1;
    while (i >= 0 && res[i] == 0)
       i--;

    if (i == -1) {
        cout<<0;
        return;
    }

    string s = "";
    reverse(res.begin(), res.end());
    
    printVector(res);
    cout<<": "<<_mod(res, n)<<endl;
}

int main() {
    vector<int> a, b;
    int sum, diff, prod, n;

    string inp;
    cin>>inp;
    for (int j = 0; j < inp.length(); j++) {
        a.push_back(inp[j] - '0');
    }
    cin>>inp;
    for (int j = 0; j < inp.length(); j++) {
        b.push_back(inp[j] - '0');
    }

    cin>>n;

    modularSum(a, b, n);
    modularDiff(a, b, n);
    modularProd(a, b, n);
}
