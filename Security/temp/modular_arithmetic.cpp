#include <bits/stdc++.h>
#include <gmp.h>
using namespace std;
bool isSmaller(vector<int> a, vector<int> b)
{
    int n1 = a.size(),n2=b.size();
    if (n1 < n2)
    return true;
    if (n2 < n1)
    return false;
    for (int i=0; i<n1; i++)
    if (a[i] < b[i])
        return true;
    else if (a[i] > b[i])
        return false;
    return false;
}
vector<int> findmod(vector<int> , vector<int> );
vector<int>  modularDiff(vector<int> a, vector<int> b, vector<int>  n) {
	if (isSmaller(a,b))
        	a.swap(b);
 
    vector<int> ans;
    int n1 = a.size();
    int n2 = b.size();
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
     
    int carry = 0;
 
    for (int i=0; i<n2; i++)
    {
             
        int sub = (a[i]-b[i]-carry);
        if (sub < 0)
        {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
 	ans.push_back(sub);
    }

    for (int i=n2; i<n1; i++)
    {
        int sub = (a[i] - carry);
        if (sub < 0)
        {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
             
        ans.push_back(sub);
    }
    int i=ans.size()-1;
    while(i>=0 and ans[i]==0){
    ans.pop_back();
    i--;
}  
    reverse(ans.begin(), ans.end());
    return findmod(ans, n);
}
vector<int>  findmod(vector<int> ans, vector<int>  n) {
	 while(1){
    if(isSmaller(ans,n)){
		return ans;
	}
    else {
    	//ans.clear();
    	ans = modularDiff(ans,n,n);
    }
    }
}

vector<int>  modularSum(vector<int> a, vector<int> b, vector<int>  n) {

    vector<int> ans;
    int a_len = a.size() - 1;
    int b_len = b.size() - 1;
    int carry = 0, sum = 0;
    while (a_len >= 0 and b_len >= 0) {
        int tmp = a[a_len] + b[b_len] + carry;
        carry = tmp/10;
        sum = tmp%10;
        ans.push_back(sum);
        a_len--;
      	b_len--;
    }

    if (a_len == -1) {
        while(b_len >=0) {
            int tmp = b[b_len--] + carry;
            carry = tmp/10;
            sum = tmp%10;
            ans.push_back(sum);
        }
    }

    if (b_len == -1) {
        while(a_len >=0) {
            int tmp = a[a_len--] + carry;
            carry = tmp/10;
            sum = tmp%10;
            ans.push_back(sum);
        }
    }
    if (carry)
        ans.push_back(carry);

    reverse(ans.begin(), ans.end());
cout<<"Sum is ";
for(int i=0;i<ans.size();i++)
	cout<<ans[i];
cout<<endl;
cout<<"modular sum is ";
    return findmod(ans, n);
}


vector<int> modularProd(vector<int> num1, vector<int> num2, vector<int> n) {
	int n1 = num1.size();
    int n2 = num2.size();
    vector<int> zero;
    zero.push_back(0);
    if (n1 == 0 || n2 == 0)
       return zero;

    vector<int> result(n1 + n2, 0);

    int i_n1 = 0; 
    int i_n2 = 0; 
 

    for (int i=num1.size()-1; i>=0; i--)
    {
        int carry = 0;
        int n1 = num1[i];

        i_n2 = 0; 
          
        for (int j=num2.size()-1; j>=0; j--)
        {
            
            int n2 = num2[j] ;
 
            int sum = n1*n2 + result[i_n1 + i_n2] + carry;

            carry = sum/10;

            result[i_n1 + i_n2] = sum % 10;
 
            i_n2++;
        }

        if (carry > 0)
            result[i_n1 + i_n2] += carry;

        i_n1++;
    }
 
     int i = result.size() - 1;
    while (i>=0 && result[i] == 0)
       i--;

    if (i == -1)
       return zero;
       i=result.size()-1;
    while(i>=0 and result[i]==0){
    result.pop_back();
    i--;
    }
       reverse(result.begin(), result.end());
   cout<<"Product is ";
for(int i=0;i<result.size();i++)
	cout<<result[i];
cout<<endl;
cout<<"modular product is ";
    return findmod(result, n);
}

int main() {
    vector<int> a, b,n_vec;
    vector<int> sum, diff, prod;

    string inp,n;
    cout<<"Enter first number : \n";
    cin>>inp;
    for (int j = 0; j < inp.length(); j++) {
        a.push_back(inp[j] - '0');
    }
    cout<<"Enter second number : \n";
    cin>>inp;
    for (int j = 0; j < inp.length(); j++) {
        b.push_back(inp[j] - '0');
    }
    cout<<"enter the value of n\n";
    cin>>n;
    for (int j = 0; j < n.length(); j++) {
        n_vec.push_back(n[j] - '0');
    }
       sum = modularSum(a, b, n_vec);
       if(sum.size()==0)
       cout<<"0"<<endl;
       for(int i=0;i<sum.size();i++)
	cout<<sum[i];
	cout<<endl;
       diff = modularDiff(a, b, n_vec);
       cout<<"modular diff is ";
       if(diff.size()==0)
       cout<<"0"<<endl;
        for(int i=0;i<diff.size();i++)
	cout<<diff[i];
	cout<<endl;
     prod = modularProd(a, b, n_vec);
     if(prod.size()==0)
       cout<<"0"<<endl;
     for(int i=0;i<prod.size();i++)
	cout<<prod[i];
	cout<<endl;
}
    
    
    
