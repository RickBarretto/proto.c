---
author: RickBarretto
copyright: public domain
version: 1.0.0
---

# Result

Results are an elegant way to do error-handling.

Sometimes we want to wrap some function's returned value that may also contain return errors.

It's present in a lot of modern programming languages,
such as C++, Rust and Swift.

> You can read more about Result Type on [Wikipedia][wiki-result-type].


## Usage

An example of usage: imagine you have an array and you want to
get an element of this array.

Your funcition must return the element at the same time it
must return an error-code. 

Note that, in this case, you can't return `NULL` if something went wrong,
because it can be a valid value. 
So, instead of that, you should return a Result type.

Let's see that in practice:

```c

typedef struct array {
    void *content;
    size_t size;
} array;

array my_array;

result get_element_from(const array *data, const size_t index)
{
    #define ARRAY_EMPTY 1
    #define OUT_OF_INDEX 2

    if (0 == data->size)     return err(ARRAY_EMPTY);
    if (0 > index)           return err(OUT_OF_INDEX);
    if (index >= data->size) return err(OUT_OF_INDEX);

    return ok(array.content[index]);

}

// now we can just:
result element = get_element_from(my_array, 10);
if (1 == element.error) ...
if (2 == element.error) ...

// or we can cast it for a fixed type instead of void generic
def_result(u8_result, uint8_t);

u8_result element = cast_result(get_element_from(my_array, 10));
if (1 == element.error) ...
if (2 == element.error) ...
```

## API


#### result

`result` can be used as a type or struct, and stores two values,
a `unwrap` that is the wrapped value itself, 
and a `error` that is the error-code, if it's `0`, it's a success code by default.

In this case, `unwrap` is stored as a void pointer, 
used for generic programming in C. So you can store any type here,
but it's not type-safe.

##### Fields
- `*void unwrap`: wraps the value itself
- `uint_8 error`: defines the function-return's status

##### See
- [`ok`](#ok)
- [`err`](#err)
- [`def_result`](#def_result)
- [`cast_result`](#cast_result)


#### def_result

`def_result` is a macro used for create new pseudo-generic, 
but type-safe results.

Basically it gets two arguments, `name` and `type`, and generates
an result like this:

```c
typedef struct `name` {
    `type` unwrap;
    uint8_t error;
} `name`;
```

You can use [`cast_result`](#cast_result) to translate generic-result 
to your own pseudo-generic results.

##### Arguments
1. `name`: the name of your new type/struct
2. `type`: the `unwrap`'s type

##### See
- [`result`](#result-1)
- [`cast_result`](#cast_result)


#### ok

Is a function that returns an generic `result` with some value, and a success code.

##### Arguments
1. `void* value`: can be any value

##### See
- [`result`](#result-1)
- [`err`](#err)

#### err

Is a function that returns an generic `result` with an error code.
In this case, `unwrap`'ll be a `NULL`.

##### Arguments
1. `uint8_t error_code`: the error code itself

##### See
- [`result`](#result-1)
- [`ok`](#ok)

#### cast_result

It's a macro that converts a generic `result` to your own
pseudo-generic results types.

> **Note**: 
> It can only be used as an r-value, and you always need to asign it to a variable.

##### Arguments
1. `result`: the generic result to be converted

##### Usage
```c
result some_function(void);
def_result(str_res, char*);

str_res casted;
casted = cast_result(ok("Hello!"));
casted = cast_result(err());
casted = cast_result(some_function());
```

##### See
- [`result`](#result-1)
- [`def_result`](#def_result)

## Licenses

This readme and `test.c` are under Public Domain,
while the implementation itself (`result.h`) is under MPL 2.0.


[wiki-result-type]: https://en.wikipedia.org/wiki/Result_type

---

> This file covers the usage and API of [`result.h`](./result.h).
>
> The current version is covered at Markdown's metadata,
> and must be synced with the implementation.


> Any copyright is dedicated to the Public Domain.
> https://creativecommons.org/publicdomain/zero/1.0/
