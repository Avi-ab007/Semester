#include <stdio.h>
#include <gmp.h>
#include <time.h>
void get_gcd(mpz_t x, mpz_t y,mpz_t res)
{
	while(mpz_cmp(x,y)!=0){
		if(mpz_cmp(x,y)>0)
			mpz_sub(x,x,y);
		else
			mpz_sub(y,y,x);
	}
	mpz_set(res,x);
}
int main()
{
	mpz_t z,x,y,res;
	mpz_inits(z,x,y,res,NULL);
	//gmp_printf("enter x,y number: \n");
	//gmp_scanf("%Zd %Zd",x,y);
	/*mpz_add(z,a,b);
	gmp_printf("result : %Zd\n",z);
	gmp_scanf("%Zd %Zd",a,b);
	mpz_mul(z,a,b);
	gmp_printf("result : %Zd\n",z);
	mpz_get_d(z);
	gmp_printf("float: %.Ff\n",z);
	*/
	gmp_randstate_t s;
	gmp_randinit_default(s);
	unsigned long seed;
	seed = time(NULL);
	//seed= 1234567;
	gmp_randseed_ui(s, seed);
	//gmp_randstate_ui(s,seed);
	mpz_urandomb(x,s,14);
	mpz_urandomb(y,s,14);
	gmp_printf("X is %Zd\n",x);
	gmp_printf("Y is %Zd\n",y);
	get_gcd(x,y,res);
	gmp_printf("GCD is %Zd\n",res);

	
	return 0;
}


