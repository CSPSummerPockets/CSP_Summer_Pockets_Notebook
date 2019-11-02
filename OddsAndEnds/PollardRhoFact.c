/*
 * An implementation of Pollard-Rho algorithm for integer factorization
 * See http://www.giaithuatlaptrinh.com/?p=393 for details
 *
 *  Created on: Aug 14, 2015
 *      Author: hunglv
 */


#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define PRIME 1
#define COMPOSITE 0
#define MAXNUMFACT 64 // the maximum number of factors

typedef unsigned long long int LLU; // using unsigned long long type to avoid overflow

LLU Fa[MAXNUMFACT];// the array storing factors
int nfact = -1; // the number of factors

int miller_rabin_testing(int acc, LLU N);
void decompose(LLU p, int *k, LLU *m);
LLU llu_fsqrt(LLU N);
LLU mod_mul(LLU a, LLU b, LLU p);
LLU random64();
LLU next_prng(LLU x, LLU N);
LLU gcd(LLU a, LLU b);
LLU find_factor(LLU N);
LLU mod_power(LLU a, LLU b, LLU p);
void fast_native_fact(LLU N);
int llu_cmp(const void *a, const void *b);
void pollard_rho_fact(LLU N);
void print_factors(void);

int main (void){
	memset(Fa,0,sizeof(Fa)); // set everything to zero
	pollard_rho_fact((LLU)2432902008176640000);
	print_factors();
	return 0;
}


void pollard_rho_fact(LLU N){
	if(N == (LLU)1){
		return;
	}else if(N < (((LLU)1) << 10)){ // if N is too small
		fast_native_fact(N);
	}else if(miller_rabin_testing(10, N) == PRIME){ // 10 is the accuracy of the test which corresponds to 1 - 1/2^(10)
		Fa[++nfact] = N; // found a prime factor
	} else {
		LLU p = (LLU)0;
		while(p == 0 || p == N){
			p = find_factor(N);
		}
		pollard_rho_fact(p);
		pollard_rho_fact(N/p);
	}
}

LLU find_factor(LLU N){
	LLU x = random64()% N;
	LLU y = x;
	LLU p = 1;
	do{
		x = next_prng(x,N);  // x = f(x,N)
		y = next_prng(next_prng(y,N), N); // y = f(f(y,N),N)
		if(x > y){
			p = gcd(x-y,N);
		} else {
			p = gcd(y-x,N);
		}
	}while(p == 1);
	return p;
}
/*
 * compute f(x,N) = (x^2 + 1) mod N
 */
LLU next_prng(LLU x, LLU N){
	LLU xs = mod_mul(x,x,N);
	return xs + (LLU)1;
}
/*
 * The trial divisor algorithm for integer factorization
 * See http://www.giaithuatlaptrinh.com/?p=341 for details.
 */

void fast_native_fact(LLU N){
	while (N % 2 == 0){
		Fa[++nfact] = (LLU)2;
		N = N/2;
	}
	while (N % 3 == 0){
		Fa[++nfact] = (LLU)3;
		N = N/3;
	}
	if(N == 1){
		return;
	}
	if( miller_rabin_testing(10, N) == PRIME ){
			Fa[++nfact] = N;
			return;
	}
	LLU Q = 5;
	int diff = 2;
	int sqrtN = llu_fsqrt(N);
	while(Q <= sqrtN){
		if(N %Q == 0){
			Fa[++nfact] = Q;
			N = N/Q;
			sqrtN = llu_fsqrt(N);
			if(miller_rabin_testing(10, N) == PRIME ){
				Fa[++nfact] = N;
				return;
			}
		}else {
			Q = Q + (LLU)diff;
			diff = (diff&2) + 2;// diff is alternating between 2 and 4
		}
	}
}

void print_factors(){
	qsort(Fa, nfact+1, sizeof(*Fa), llu_cmp);
	int i = 0;
	for(i = 0; i < nfact; i++){
		printf("%llu*", Fa[i]);
	}
	printf("%llu\n", Fa[nfact]);

}
int llu_cmp(const void *a, const void *b){
	return *(LLU*)a - *(LLU*)b;
}

/*
 * The miller-rabin primality testing algorithm
 * See http://www.giaithuatlaptrinh.com/?p=278 for details.
 */

int miller_rabin_testing(int acc, LLU N){
	LLU a = 0;
	int i = 0;
	for(i = 0; i <= acc; i++){
		a = random64()%(N-2)+ 2;
		if(gcd(a,N) != 1){
			return COMPOSITE;
		} else if (mod_power(a,N-1,N) != 1){
			return COMPOSITE;
		}else {
			if (witness(a,N) == COMPOSITE){
				return COMPOSITE;
			}
		}
	}
	return PRIME;
}


int witness(LLU a,  LLU N){
	LLU m;
	int k;
	decompose(N-1,&k,&m);
	LLU B[k+1];
	B[0] = mod_power(a,m,N);
	if(B[0] == 1){
		return PRIME;
	} else {
		int i = 1;
		while(i <= k){
			B[i] =  mod_mul(B[i-1],B[i-1],N);// (B[i-1]*B[i-1])%N;
			if(B[i] == 1){
				if(B[i-1] == N-1){
					return PRIME;
				} else {
					return COMPOSITE;
				}
			}
			i++;
		}
	}
	return COMPOSITE;
}
/*
 * decompose p = 2^k*m
 */
void decompose(LLU p, int *k, LLU *m){
	int i = 0;
	while ((p& 1) == 0){ // p is even
		i++;
		p = p >> 1; // p = p /2
	}
	*k = i;
	*m = p;
}

/*
 * computing (a*b) mod p using (\log_2 b + 1) space
 */

LLU mod_mul(LLU a, LLU b, LLU p){
	if (b == 1){
		return a %p;
	} else {
		LLU x = mod_mul(a, b>>1, p);
		if((b& 1) == 0){ // b is even
			return (x<<1)%p;
		} else {
			return (((x<<1)%p)+a)%p;
		}
	}
	return 0;
}
/*
 * Computing $a^b mod p$
 */
LLU mod_power(LLU a, LLU b, LLU p){
	if (b == 1){
		return a %p;
	} else {
		LLU x = mod_power(a, b/2, p);
		if((b& 1) == 0){ // b is even
			return mod_mul(x,x,p); // return  (x*x)%p;
		} else {
			return (mod_mul(mod_mul(x,x,p), a, p));// return (x*x*a)%p;
		}
	}
}
/*
 * computing the greatest common divisor of $a$ and $b$
 */
LLU gcd(LLU a, LLU b){
	LLU tmp;
	while  (b != 0){
		tmp  = b;
		b = a % b;
		a = tmp;
	}
	return a;
}

/*
 * generating  a 64-bit random integer
 */
LLU random64(){
	LLU n  = 0;
	int l = rand()%(RAND_MAX-2)+2;
	int r = rand()%(RAND_MAX) + rand()%2;
	n = n | ((LLU)r);
	n = n << 32;
	n = n | ((LLU)l);
	return n;
}
/*
 * Computing the floor of square root of a 64-bit integer
 * See http://www.giaithuatlaptrinh.com/?p=402 for details.
 */
LLU llu_fsqrt(LLU  N){
	LLU X, A2, R;
	X = N;
	A2 = ((LLU)1) << 62; // guessing a[1]^2
	R = 0;
	while(N < A2){
		A2 >>= 2;
	}

	while(A2 > 0){
		if (X >= R + A2) {
			X -= R + A2;
			R = (R >> 1) + A2;
			A2 = A2>> 2;
		} else {
			A2 = A2 >> 2;
			R = R >> 1;
		}
	}
	return R;
}

