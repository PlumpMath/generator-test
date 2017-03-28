// generator-test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include <experimental/resumable>
#include <experimental/generator>
namespace ex = std::experimental;

// References
// http://kirkshoop.github.io/async/rxcpp/await/c++/2015/03/17/await-in-c++-yield-the-next.html
// https://blogs.msdn.microsoft.com/vcblog/2014/11/12/resumable-functions-in-c/

ex::generator<int> fibonacci(int n) {
	int a = 0;
	int b = 1;

	while (n-- > 0) {
		co_yield a;
		auto next = a + b; a = b;
		b = next;
	}
}

template <typename T>
ex::generator<T> fibonacci2() {
	T a = 0;
	T b = 1;

	while (true) {
		co_yield a;
		auto next = a + b; a = b;
		b = next;
	}
}

template <typename T>
ex::generator<T> SieveOfEratosthenes(T upperBound) {
	bool* isPrime = new bool[upperBound + 1];
	memset(isPrime, true, sizeof(bool) * (upperBound + 1));

	for (T p = 2; p*p <= upperBound; p++) {
		if (isPrime[p]) {
			for (T i = p * 2; i <= upperBound ; i += p) {
				isPrime[i] = false;
			}

			co_yield p;
		}
	}

	delete [] isPrime;
}

int main()
{
	//for (auto v : fibonacci(35)) {
	//for (auto v : fibonacci2<int>()) {
	//	if (v > 10)
	//		break;
	//	std::cout << v << ' ';
	//}

	for (auto v : SieveOfEratosthenes(100 * 100)) {
		if (v > 100)
			break;
		std::cout << v << ' ';
	}
}
