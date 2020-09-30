#include <iostream>

typedef unsigned long long INT;  // argmax_n(Fibonacci(n)) = 93; n=94开始上溢出, 因为：2^64-1 = 18446744073709551615

int Fibonacci(int n) {
	INT f_small = 0; // f(0)
	INT f_big = 1;  // f(1)

	if (n == 0 ) {
		return 0;
	} else if (n == 1) {
		return 1;
	}
	INT f_n = 0;
	int count = 1;

	while (n > count) {
		f_small = f_big + f_small;
		count++;
		if (n == count) {
			f_n = f_small;
		}
		f_big = f_small + f_big;
		count++;
		if (n == count) {
			f_n = f_big;
		}
	}
	std::cout << "Fibonacci(" << n << "): " << f_n << std::endl;
	return f_n;
}

int main() {
	int n;
	while (std::cin >> n) {
		if (n < 0 ){ 
			std::cout << "Invalid Number\n";
		} else {
			Fibonacci(n);
		}
	}
    return 0;	
}
