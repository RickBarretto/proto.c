/**
 * Tests for optional.h
 *
 * Any copyright is dedicated to the Public Domain.
 * https://creativecommons.org/publicdomain/zero/1.0/
 *
 * Compile with: `gcc test.c -o test.exe`
 * And then run: `./test`
 *
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "result.h"

result return_ok_int()
{
	return ok((void *)10);
}

result return_ok_string()
{
	return ok((void *)"Hello, world!");
}

result return_error()
{
	return err(1);
}

def_result(result_string, char *);

result_string return_pseudo_generic()
{
	result_string res = cast_result(ok("Hello, world! :)"));
	return res;
}

int main(void)
{

	result my_int = return_ok_int();
	printf("%d\n", my_int.unwrap);

	assert(10 == my_int.unwrap);

	printf("%d * 2 is = %d\n",
	       my_int.unwrap,
	       (int)my_int.unwrap * 2);

	/* **** **** **** **** **** **** **** */

	result my_string = return_ok_string();
	printf("%s\n", my_string.unwrap);

	assert(0 == strcmp("Hello, world!", my_string.unwrap));

	/* **** **** **** **** **** **** **** */

	result_string my_string2 = return_pseudo_generic();
	printf("%s\n", my_string2.unwrap);

	assert(0 == strcmp("Hello, world! :)", my_string2.unwrap));

	/* **** **** **** **** **** **** **** */

	result error = return_error();
	if (error.error)
		printf("result contains an error %d\n", error.error);
	else
		printf("result does not contain an error\n");

	assert(NULL == error.unwrap);
	assert(1 == error.error);

	/* **** **** **** **** **** **** **** */

	struct string_result
	{
		char *unwrap;
		uint8_t error;
	};

	result temp = return_ok_string();
	struct string_result s;

	s.unwrap = (char *)temp.unwrap;
	s.error = temp.error;

	printf("{\n\tunwrap: %s,\n\terror: %d\n}\n",
	       s.unwrap,
	       s.error);

	return 0;
}
