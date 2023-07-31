

# Kwargs, How to create default arguments in C

Tags: C Programming Language, API


## What are kwargs

`kwargs` comes from Python, and it means "Keyword Arguments", they are optional arbitrary arguments.

```py
def print_user(id: UserId, **kwargs):
        print(f"ID: {id}")
        for key, val in kwargs.items():
                print(f"  {key}, {val}")

if __name__ == "__main__":
        print_user(user_id, name = "RickBarretto", repository = "proto.c")
```

The difference between the Python code above and my C implementation will be
the fact that in C it won't get arbitrary parameters because I'll be using a struct
instead of a dictionary.


## The usage

In Python, you will probably want to use it when you need to pass arbitrary values
without creating a dictionary, which creates a nice interface to work with.

See the differences:

```py
# for -> def print_user(user_id: UserId, kwargs: Dict)
print_user(user_id, { "name": "RickBarreto", "repository": "proto.c" })
# for -> def print_user(user_id: UserId, **kwargs)
print_user(user_id, name = "RickBarreto", repository = "proto.c")
```

In C, you get a similar interface, but with keys defined at compile time.

Have a look:

```c
print_user(user_id, .name = "RickBarretto", .repository = "proto.c");
```

Remember the key arguments should be the latest one,
and you'll get some limitations that I'll explain later.


## The Implementation

```c
/** KW(fn): Just a macro that expands to fn_kwargs
 *      - fn: the function's name
 *
 */
#define KW(fn) struct fn ## _kwargs

/** def_kwargs(fn, definition)
 *      - fn: the function's name
 *      - definition: a block with internal definition of arguments
 *
 *  Usage:
 *      def_kwargs(function, { int arg1; double arg2 });
 *
 *  Expansion:
 *      struct function_kwargs { int arg1; double arg2 };
 *
 */
#define def_kwargs(fn, definition) KW(fn) definition

```

So, what is the plan here? Well, the macros above are completely optional,
and you can write them by hand if you want to.

But, the plan is actually pass a struct to the latest one argument.
You might be thinking how that is going to happen, and the answer is:
* Some magic with macro expansions
* And Variadic Arguments

```c
/** struct print_user_kwargs
 *      - char [65]name;
 *      - char [65]repository;
 *      - int commits;
 */
def_kwargs(print_user, { char name[65]; char repository[65]; int commits });

/** print_user(unsigned id, **kwargs): Prints the user's information
 *      - id: it's the user's id
 *      - kwargs:
 *        obligatory:
 *          - int commits: the amount of commits in that repo
 *        optionals:
 *          - char [65]name = "Anonymous": the user's name
 *          - char [65]repository = "Private": the user's repo
 *
 */
#define print_user(id, ...)                                     \
        internal_print_user((id), (KW(print_user)){             \
                .name = "Anonymous", .repository = "Private",   \
                __VA_ARGS__ })

static void internal_print_user(unsigned int id, KW(print_user) kwargs)
{
        // don't forget to #include <stdio.h>
        printf("ID: %d\n",              id);
        printf("  user: %s\n",          kwargs.name);
        printf("  repository: %s\n",    kwargs.repository);
        printf("  commits: %d\n",       kwargs.commits);
        return;
}
```

Some important details:
- Creating an anonymous struct `(struct fn_kwargs){...}`
  and passing it directly to our function.
- Declaring `internal_print_user` as `static`, so it's not
  available to the user's API, but to the internal one.

### Explanation

The magic happens when we convert our variable arguments
into members of a struct with `__VA_ARGS__`

In fact, we overwrite the default values, so this:

```c
print_user(10,
           .name = "RickBarretto", .repository = "proto.c", .commits = 10);
```

Is the same as:

```c
internal_print_user((10), (struct print_user_kwargs) {
           .name = "Anonymous", .repository = "Private",
           .name = "RickBarretto", .repository = "proto.c", .commits = 10});
```

If we miss some argument, the default one will be used.

> [!NOTE]
> you can also use without keys if you type it in order:
>
> ```c
> print_user(10, "RickBarretto", "proto.c", 10);
> ```

### Limitations

Due to the fact that `__VA_ARGS__` is already being used as a member of a struct,
you won't be able to have something like `*args, **kwargs` from Python.

----

<p xmlns:cc="http://creativecommons.org/ns#" xmlns:dct="http://purl.org/dc/terms/"><span property="dct:title">Kwargs, How to create default arguments in C</span> by <a rel="cc:attributionURL dct:creator" property="cc:attributionName" href="https://github.com/RickBarretto">RickBarretto</a> is marked with <a href="http://creativecommons.org/publicdomain/zero/1.0?ref=chooser-v1" target="_blank" rel="license noopener noreferrer" style="display:inline-block;">CC0 1.0 Universal<img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg?ref=chooser-v1"><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/zero.svg?ref=chooser-v1"></a></p>
