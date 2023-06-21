/**
 * Tests for lambda.h
 *
 * Any copyright is dedicated to the Public Domain.
 * https://creativecommons.org/publicdomain/zero/1.0/
 *
 * Compile with: `gcc test.c -o test.exe`
 * And then run: `./test`
 *
 */

#include <assert.h>
#include <stdio.h>

#include "lambda.h"

void test_default(void)
{
	int (*max)(int, int) = lambda(int, (int a, int b),
				      { return (a > b) ? a : b; });

	int (*min)(int, int) = ʎ(int, (int a, int b),
				 { return (a < b) ? a : b; });

	printf("max(2, 5) = %d\n", max(2, 5));
	assert(5 == max(2, 5));
	printf("min(2, 5) = %d\n", min(2, 5));
	assert(2 == min(2, 5));
}

void test_clousure(void)
{
	typedef int (*adder_proc)(int);

	adder_proc adder(int x)
	{
		// cast unnecessary, it just is here to improve readability
		return (adder_proc)lambda(int, (int y), { return x + y; });
	}

	adder_proc adder5 = adder(5);
	int res;

	res = adder5(1);
	printf("%d\n", res);
	assert(6 == res);

	res = adder5(1);
	printf("%d\n", res);
	assert(7 == res);

	res = adder5(2);
	printf("%d\n", res);
	assert(9 == res);
}

int main(void)
{
	test_default();
	test_clousure();
	test_generic_programming();

	return 0;
}
