#include <stdio.h>
#include<iostream>
using namespace std;			
#include <gmp.h>

int main()
{
	int n;
	cin>>n;
	mpz_t r[n],m[n];
	mpz_t temp;
	mpz_init(temp);
	mpz_set_ui(temp,1);
	for(int i=0;i<n;i++)
	{
		mpz_t a,b;
		mpz_init(a);
		mpz_init(b); 
		gmp_scanf("%Zd",a);
  		gmp_scanf("%Zd",b);
  		mpz_init_set(r[i],a);
  		mpz_init_set(m[i],b);
  		mpz_mul(temp,temp,b);
	}	
	mpz_t s;
	mpz_init(s);
	mpz_set_ui(s,0);
	mpz_t temp1;
	mpz_init(temp1);
	mpz_set(temp1,m[0]);
	for(int i=1;i<n;i++)
	{
		mpz_gcd(temp1,temp1,m[i]);	
	}
	if(mpz_cmp_ui(temp1,1)==0)
	{
		for(int i=0;i<n;i++)
		{
			mpz_t t1,t2,t3;
			mpz_init(t1);mpz_init(t2);mpz_init(t3);
			mpz_div(t1,temp,m[i]);
			mpz_mul(t2,t1,r[i]);
			mpz_invert(t3,t1,m[i]);
			gmp_printf("invere %Zd\n",t3);
			mpz_mul(t2,t2,t3);
			//mpz_mod(t2,t2,m[i]);
			mpz_add(s,s,t2);
		}
		mpz_mod(s,s,temp);
		gmp_printf("%Zd",s);
	}
	else
	{
	cout<<"cant generate"<<endl;
	}
	
}
