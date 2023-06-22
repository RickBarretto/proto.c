/**
 *  ---
 *  section: Error Handling
 *  title: Result
 *  short_description: result is a container that may contain a value or an error-code
 *
 *  file: optional.h
 *  license: MPL 2.0
 *  copyright: RickBarretto
 *  version: 1.0.1
 *  ---
 *
 * <!-- read the footer for more information about copyright -->
 *
 *  ## Description
 *
 *  You may be asking right now, Why should I use an result instead of other approaches?
 *  The answer is basically: you have a greater control about error-handling.
 *
 *  ## Objects
 *  - `result`
 *  - `def_result`
 *  - `ok`
 *  - `err`
 *  - `cast_result`
 *
 *  ## Design Choices
 *
 *  Due the fact that void pointers are not type safe, I created two ways to create results.
 *  - *The Generic Way*:
 *      - Using `result` type, but it's not type-safe as I told
 *  - *The Pseudo-generic Way*:
 *      - Using the preprocessor to create new result types for each type
 *
 *  You can choose one of them of both in your project,
 *  pseudo-generic generators can be a bit annoying to use sometimes,
 *  but it's definitelly type-safer than generics with `void*`.
 *
 *  ## Exports
 *  - `stdint.h`
 *
 */

#ifndef LIB_RESULT_H
#define LIB_RESULT_H

#include <stdint.h>

/** ## result
 *
 *  > `result<void* unwrap, uint8_t error>`
 *  > type: struct, type
 *
 *  Creates a generic result using `void*` to store the returned value.
 *  @`unwrap` stores the wrapped value itself,
 *  while @`error` is the returned error, 0 means success.
 *
 *  ### Fields
 *  - `void* unwrap`: The unwraped result
 *  - `uint8_t error`: The error code
 *
 *  ### Usage
 *
 *  	result fun(void){
 *      	return ok((void*)10);
 *  	}
 */
typedef struct result
{
        void *unwrap;
        uint8_t error;
} result;

/** ## def_result
 *
 *  > `def_result(name, type)`
 *  > structure: `@name<@type unwrap, uint8_t error>`
 *  > type: macro, struct, type
 *
 *  A macro that reates a pseudo-generic result struct/type,
 *  but with a fixed type instead of a `void*`, as it is for [[#result]].
 *
 *  ### Arguments
 *  1. `name`: the name of your new type/struct
 *  2. `type`: the `unwrap`'s type
 *
 *  ### Usage
 *  ```c
 *  def_result(result_uint8, uint8_t);
 *
 *  	// expands to:
 *  	// typedef struct result_uint8
 *  	// {
 *  	//      uint8_t unwrap;
 *  	//      uint8_t error;
 *  	// } result_uint8;
 *
 *   result_uint8 fun(void){
 *      return ok((void*)10);
 *   }
 *   ```
 *
 */
#define def_result(name, type) \
        typedef struct name    \
        {                      \
                type unwrap;   \
                uint8_t error; \
        } name

/** ## ok
 *
 *  > `ok(void *value)`
 *  > type: procedure
 *
 *  Returns an `result` with some value
 *
 *  ### Arguments
 *  1. `void* value`: any value to be returned
 *
 *  ### Usage
 *  ```c
 *  result fun(void){
 *      // `ok` returns: result<unwrap: 10, error: 0>
 *      return ok((void*)10);
 *  }
 *  ```
 *
 */
result ok(void *value)
{
        result res = {.unwrap = value, .error = 0};
        return res;
}

/** ## err
 *
 *  > `err(uint8_t error_code)`
 *  > type: procedure
 *
 *  Returns a `result` with an error code
 *
 *  ### Arguments
 *  1. `uint8_t error`: a error code
 *
 *  ### Usage
 *  ```
 *  result fun(void){
 *      // `err` returns: result<unwrap: NULL, error: 1>
 *      err(1);
 *  }
 *  ```
 *
 */
result err(uint8_t error_code)
{
        result res = {.unwrap = NULL, .error = error_code};
        return res;
}

/** ## cast_result
 *
 *  > `cast_result(result)`
 *  > type: macro
 *
 *  `cast_result` simply converts an @result to other.
 *   Be careful using this, you should use it when asigning l-values.
 *
 *  You can use it to convert generic `result`s to your own pseudo-generic one.
 *
 *  ### Arguments
 *  1. `result`: the generic result to be converted
 *
 *  ### Usage
 *
 *  ```c
 *  def_result(result_string, char*);
 *
 *  result_string fun(void){
 *      // note: `ok` returns result<unwrap: "Hello, world!", error: 0>
 *      result_string res = cast_result(ok((void*)"Hello, world!"));
 *      return res;
 *  }
 *  ```
 *
 */
#define cast_result(result)              \
        {                                \
                .unwrap = result.unwrap, \
                .error = result.error    \
        }

#endif /* LIB_RESULT_H */

/**
 *  Copyright (C) 2023 RickBarretto
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 */
