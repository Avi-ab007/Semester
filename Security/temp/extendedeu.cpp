#include <stdio.h>
#include <gmp.h>
int main()
{
	mpz_t x,y,d,a,b,q,r,x1,x2,y1,y2,temp,one,zero;
	mpz_inits(d,x,y,a,b,q,r,x1,x2,y1,y2,temp,one,zero,NULL);
	gmp_printf("enter a,b number: \n");
	gmp_scanf("%Zd %Zd",a,b);
	mpz_set_si(one,1);
	mpz_set_si(zero,0);
	if(mpz_cmp(b,zero)==0){
		mpz_set(d,a);
		mpz_set(x,one);
		mpz_set(y,zero);
		gmp_printf("gcd is %Zd and x is %Zd , y is %Zd\n",d,x,y);
		return 0;
	}
	mpz_set_si(x2,1);
	mpz_set_si(x1,0);
	mpz_set_si(y2,0);
	mpz_set_si(y1,1);
	while(mpz_cmp(b,zero)>0){
		mpz_fdiv_q(q,a,b);
		mpz_mul(temp,q,b);
		mpz_sub(r,a,temp);
		mpz_mul(temp,q,x1);
		mpz_sub(x,x2,temp);
		mpz_mul(temp,q,y1);
		mpz_sub(y,y2,temp);
		mpz_set(a,b);
		mpz_set(b,r);
		mpz_set(x2,x1);
		mpz_set(x1,x);
		mpz_set(y2,y1);
		mpz_set(y1,y);
	}
	mpz_set(d,a);
	mpz_set(x,x2);
	mpz_set(y,y2);
	gmp_printf("gcd is %Zd and x is %Zd , y is %Zd\n",d,x,y);	
	return 0;
}


