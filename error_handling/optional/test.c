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

#include "optional.h"

optional return_some_int()
{
	return some((void *)10);
}

optional return_some_string()
{
	return some((void *)"Hello, world!");
}

optional return_none()
{
	return none();
}

def_optional(optional_string, char *);

optional_string return_pseudo_generic()
{
	optional_string res = cast_optional(some("Hello, world! :)"));
	return res;
}

int main(void)
{

	optional my_int = return_some_int();
	printf("%d\n", my_int.value);

	assert(10 == my_int.value);
	assert(true == my_int.has_some);

	printf("%d * 2 is = %d\n",
	       my_int.value,
	       (int)my_int.value * 2);

	/* **** **** **** **** **** **** **** */

	optional my_string = return_some_string();
	printf("%s\n", my_string.value);

	assert(0 == strcmp("Hello, world!", my_string.value));
	assert(true == my_string.has_some);

	/* **** **** **** **** **** **** **** */

	optional_string my_string2 = return_pseudo_generic();
	printf("%s\n", my_string2.value);

	assert(0 == strcmp("Hello, world! :)", my_string2.value));
	assert(true == my_string2.has_some);

	/* **** **** **** **** **** **** **** */

	optional empty = return_none();
	if (empty.has_some)
		printf("empty is an empty optional\n");
	else
		printf("empty is not an empty optional\n");

	assert(NULL == empty.value);
	assert(false == empty.has_some);

	/* **** **** **** **** **** **** **** */

	struct string_result
	{
		char *value;
		bool has_some;
	};

	optional temp = return_some_string();
	struct string_result s;

	s.value = (char *)temp.value;
	s.has_some = temp.has_some;

	printf("{\n\tvalue: %s,\n\thas_some: %s\n}\n",
	       s.value,
	       s.has_some ? "true" : "false");

	return 0;
}
