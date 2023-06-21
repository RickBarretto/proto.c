---
author: RickBarretto
copyright: public domain
version: 1.0.0
---

# Lambda

This module provides you a sugar-syntax for GCC's anonymous functions.

## Usage

```c
int max = lambda(int, (int a, int b), { return (a > b)? a:b; });
int max = ʄ(int, (int a, int b), { return (a > b)? a:b; });
int max = ʎ(int, (int a, int b), { return (a > b)? a:b; });
```

## lambda

> lambda(type, args, body)
> **type**: macro

> **Note**: it's not C compilant, but GCC compilant,
> it's currently using two extended features from GCC:
>  - nested functions
>  - statement expressions

- `type`: the returned type
- `args`: the arguments, enclosed by parentesis (`()`)
- note that colon (`,`) is needed between parameters.
- `body`: the body of the function, enclosed by curly braces (`{}`)
  - note that you must use semi-colon (`;`) for each statement
	and may need use `return` if some value is returned.

### Alternative names
- `ʄ`
- `ʎ`


## Licenses

This readme and `test.c` are under Public Domain,
while the implementation itself (`lambda.h`) is under MPL 2.0.

---

> This file covers the usage and API of [`lambda.h`](./lambda.h).
>
> The current version is covered on Markdown's metadata,
> and must be synced with the implementation.


> Any copyright is dedicated to the Public Domain.
> https://creativecommons.org/publicdomain/zero/1.0/
