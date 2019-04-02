
#include<bits/stdc++.h>
using namespace std;
int to_integer(string s) {
 int val=0;
 int power=1;
 for(int i=s.length()-1;i>=0;i--)
 {
    val+=(s[i]-'0')*power;
    power*=2;
 }
 return val;
}
int main(int argc,char *argv[]) {  
 if(argc!=4) {
  cout<<"give all inputs"<<endl;
  return 0; 
 }
 int n;
 cout<<"Enter n value ";
 cin>>n;
 int a,b,c;
 a=to_integer(argv[1]);
 b=to_integer(argv[2]);
 c=to_integer(argv[3]);
 cout<<a<<" "<<b<<" "<<c<<endl;
 int value=1<<(n-1); 
 cout<<value<<endl;
 int values[n];
 values[0]=a;
 for(int i=1;i<n;i++)
 {
    int temp =values[i-1];
   if(value&temp) {
      temp=temp^value;
      temp=temp<<1;
      temp=temp^c;
      values[i]=temp;
   }
   else
   values[i]=temp<<1;
   bitset <8> bt1(values[i]);
    cout<<"f(x)* x^"<<i<<" : "<<bt1<<endl;
 }

 int result=0,count=0;
 while(b) {
  if(b&1){
       result^=(values[count]);
  }
    b=b>>1;
    count++;     
 }
 bitset <8> bt1(result);
 cout<<"result: "<<bt1<<endl;
 return 0;
}
