/**
 *  ---
 *  section: Error Handling
 *  title: Optional
 *  short_description: optional is a container for a value that may or not may exist
 *
 *  file: optional.h
 *  license: MPL 2.0
 *  copyright: RickBarretto, 2023
 *  version: 1.0.1
 *  ---
 *
 * <!-- read the footer for more information about copyright -->
 *
 *  ## Description
 *
 *  You may be asking right now, Why should I use an optional instead of a NULL?
 *  The answer is basically: In some ocasions you may consider NULL as a proper value,
 *  instead of a tool for error handling.
 *
 *  ## Objects
 *  - [[#optional|`optional`]]
 *  - [[#def_optional|`def_optional`]]
 *  - [[#some|`some`]]
 *  - [[#none|`none`]]
 *  - [[#cast_optional|`cast_optional`]]
 *
 *  ## Design Choices
 *
 *  Due the fact that void pointers are not type safe, I created two ways to create optionals.
 *  - *The Generic Way*:
 *      - Using `optional` type, but it's not type-safe as I told
 *  - *The Pseudo-generic Way*:
 *      - Using the preprocessor to create new optional types for each type
 *
 *  You can choose one of them of both in your project,
 *  pseudo-generic generators can be a bit annoying to use sometimes,
 *  but it's definitelly type-safer than generics with `void*`.
 *
 *  ## Exports
 *  - "stdbool.h"
 *  - "stdlib.h"
 *
 */

#ifndef LIB_OPTIONAL_H
#define LIB_OPTIONAL_H

#include <stdbool.h>
#include <stdlib.h>

/** ## optional
 *
 *  > `optional<void* value, bool has_some>`
 *  > type: struct, type
 *
 *  Creates a generic optional using `void*` to store the value.
 *  @`value` stores the wrapped value itself,
 *  while @`has_some` defines if the value exists or not.
 *
 *  ### Attributes
 *  - `value`: `void*`
 *  - `has_some`: `bool`
 *
 *  ### Usage
 *
 *      optional fun(void){
 *          return some(10);
 *      }
 */
typedef struct optional
{
	void *value;
	bool has_some;
} optional;

/** ## def_optional
 *
 *  > `def_optional(name, type)`
 *  > structure: `@name<@type value, bool has_some>`
 *  > type: struct, type
 *
 *  Creates a pseudo-generic optional struct/type,
 *  but with a fixed type instead of a `void*`, as it is for [[#optional]].
 *
 *  ### Usage
 *
 *      #include <stdint.h>
 *
 *      def_optional(optional_uint8, uint8_t);
 *
 *      // expands to:
 *      // typedef struct optional_uint8
 *      // {
 *      //      uint8_t value;
 *      //      bool has_some;
 *      // } optional_uint8;
 *
 *      optional_uint8 fun(void){
 *          return some(10);
 *      }
 */
#define def_optional(name, type) \
	typedef struct name           \
	{                             \
		type value;                \
		bool has_some;             \
	} name

/** ## some
 *
 *  > `some(void *value)`
 *  > type: procedure
 *
 *  returns an `optional` with some value
 *
 *  ### Usage
 *
 *      optional fun(void){
 *          return some(10); // optional<value: 10, has_some: true>
 *      }
 *
 */
optional some(void *value)
{
	optional res = {.value = value, .has_some = true};
	return res;
}

/** ## none
 *
 *  > `none(void)`
 *  > type: procedure
 *
 *  none defined some optional-like struct as empty
 *
 *  ### Usage
 *
 *      optional fun(void){
 *          return (optional) none(); // optional<value: NULL, has_some: false>
 *      }
 *
 */
optional none(void)
{
	optional res = {.value = NULL, .has_some = false};
	return res;
}

/** ## cast_optional
 *
 *  > `cast_optional(optional)`
 *  > type: macro
 *
 *  `cast_optional` simply converts an @optional to other.
 *   Be careful using this, you should use it when asigning l-values.
 *
 *  You can use it to convert generic `optional`s to your own pseudo-generic one.
 *
 *  ### Usage
 *
 *      def_optional(optional_string, char*);
 *
 *  	optional_string fun(void){
 *          // note: `some` returns optional<value: "Hello, world!", has_some: true>
 *          optional_string res = cast_optional(some("Hello, world!"));
 *          return res;
 *      }
 *
 */
#define cast_optional(optional)     \
	{                                \
		.value = optional.value,      \
		.has_some = optional.has_some \
	}

#endif /* LIB_OPTIONAL_H */

/**
 *  Copyright (C) 2023 RickBarretto
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 */
