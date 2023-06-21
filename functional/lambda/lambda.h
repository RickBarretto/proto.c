/**
 *  ---
 *  section: Functional
 *  title: Lambda
 *  short_description: a module for anonymous functions called lambda
 *
 *  file: lambda.h
 *  license: MPL 2.0
 *  copyright: RickBarretto, 2023
 *  version: 1.0.0
 *  ---
 *
 * <!-- read the footer for more information about copyright -->
 *
 *  ## Description
 *
 *  This module provides you a sugar-syntax for GCC's anonymous functions.
 *
 *  ## Design Choices
 *
 *  There are a few alternatives names for lambda, they are: ʄ and ʎ.
 *  I added this for the case where the user wants to use a shorter name,
 *  since the C's syntax does not helps so much with that...
 *
 */

#ifndef LIB_LAMBDA_H
#define LIB_LAMBDA_H

#if !defined(__GNUC__)
#error "You need GCC compiler to use this module"
#endif

#define macro_var(var) var##_##__LINE__

/** ## lambda
 *
 *  > lambda(type, args, body)
 *  > type: macro
 *
 *  > **Note**: it's not C compilant, but GCC compilant,
 *  > it's currently using two extended features from GCC:
 *  >  - nested functions
 *  >  - statement expressions
 *
 *  Syntax-sugar for GCC's anonymous functions.
 *
 *  - type: the returned type
 *  - args: the arguments, enclosed by parentesis (`()`)
 * 	- note that colon (`,`) is needed between parameters.
 *  - body: the body of the function, enclosed by curly braces (`{}`)
 *    - note that you must use semi-colon (`;`) for each statement
 *  	and may need use `return` if some value is returned.
 *
 *  ### Alternative names
 *  - ʄ
 *  - ʎ
 *
 *  ### Usage
 *
 *  ```c
 *  int max = lambda(int, (int a, int b), { return (a > b)? a:b; });
 *  int max = ʄ(int, (int a, int b), { return (a > b)? a:b; });
 *  int max = ʎ(int, (int a, int b), { return (a > b)? a:b; });
 *  ```
 */
#define lambda(type, args, body)            \
	({                                  \
		type macro_var(lambda) args \
		    body macro_var(lambda); \
	})
#define \u0284 lambda /* ʄ */
#define \u028E lambda /* ʎ */

#endif /* LAMBDA_H */

/**
 *  Copyright (C) 2023 RickBarretto
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 */
