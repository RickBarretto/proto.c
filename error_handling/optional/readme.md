---
author: RickBarretto
copyright: public domain
version: 1.0.2
---

# Optional

Optionals are a good way to do error-handling and to be used
as simple data containers.

Sometimes we want to wrap some data that may or not may exist,
and that is the use of optionals.

It's present in a lot of modern programming languages,
such as Python, Rust and Swift.

> You can read more about Option Type on [Wikipedia][wiki-option-type].


## Usage

An example of usage: imagine you have an array and you want to
search for a generic element.
This element may or not may exist,
and also, sometimes this element may be a `NULL`,
and it is considered a valid value.

In this case, you can't return `NULL` when not found, instead of that,
you should return an Optional type.

Let's see that in practice:

```c

typedef struct array {
    void *content;
    size_t size;
} array;

array my_array;

...

optional look_for_element(const void *element)
{
    for (size_t i = 0; i < my_array.size; i++)
    {
        if (element == my_array.content[i])
            return some(i);
    }

    return none();

}

// now we can just:
optional index_of = look_for_element(element);
if (index_of.has_some) ...

// or we can cast it for a fixed type instead of void generic
def_optional(optional_index, size_t);

optional_index index_of = cast_optional(
        look_for_element(element));
if (index_of.has_some) ...
```

## API


### optional

`optional` can be used as a type or struct, and stores two values,
a `value` that is the wrapped value itself,
and a `has_some` that defines if `value` should be or not be considered
as existent.

In this case, `value` is stored as a void pointer,
used for generic programming in C. So you can store any type here,
but it's not type-safe.

#### Fields
- `*void value`: wraps the value itself
- `bool has_some`: defines if the optional has some or none value

#### See
- [`some`](#some)
- [`none`](#none)
- [`def_optional`](#def_optional)
- [`cast_optional`](#cast_optional)


### def_optional

`def_optional` is a macro used for create new pseudo-generic,
but type-safe optionals.

Basically it gets two arguments, `name` and `type`, and generates
an optional like this:

```c
typedef struct `name` {
    `type` value;
    bool has_some;
} `name`;
```

You can use [`cast_optional`](#cast_optional) to translate generic-optionals
to your own pseudo-generic optionals.

#### Arguments
1. `name`: the name of your new type/struct
2. `type`: the `value`'s type

#### See
- [`optional`](#optional)
- [`cast_optional`](#cast_optional)


### some

Is a function that returns an generic `optional` with some value.

#### Arguments
1. `void* value`: can be any value

#### See
- [`optional`](#optional)
- [`none`](#none)


### none

Is a function that returns an generic `optional` with no value.

#### Arguments
1. `void`: it takes no argument

#### See
- [`optional`](#optional)
- [`some`](#some)

### cast_optional

It's a macro that converts a generic `optional` to your own
pseudo-generic options types.

> **Note**:
> It can only be used as an r-value, and you always need to asign it to a variable.

#### Arguments
1. `optional`: the generic optional to be converted

#### Usage
```c
optional some_function(void);
def_optional(str_opt, char*);

str_opt casted;
casted = cast_optional(some("Hello!"));
casted = cast_optional(none());
casted = cast_optional(some_function());
```

#### See
- [`optional`](#optional)
- [`def_optional`](#def_optional)

## Licenses

This readme and `test.c` are under Public Domain,
while the implementation itself (`option.h`) is under MPL 2.0.


[wiki-option-type]: https://en.wikipedia.org/wiki/Option_type

---

> This file covers the usage and API of [`optional.h`](./optional.h).
>
> The current version is covered at Markdown's metadata,
> and must be synced with the implementation.


> Any copyright is dedicated to the Public Domain.
> https://creativecommons.org/publicdomain/zero/1.0/
