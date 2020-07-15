#include <iostream>
using namespace std;

long cl(long n) {
	if(n == 1) return 1;
	return n % 2 == 0 ? 1 + cl(n>>1) : 1 + cl(3*n+1);
}

int main() {
	long i = 1, j = 0;
	while(j < 1000000) {
		j = i + 100;
		long max = 0;
		for(long x = i; x <= j; x++) {
			long m = cl(x);
			if(m > max) max = m;
		}
		cout << max << endl;
		i += 100;
	}
}
