# MAL
I'm going to a make a lisp. Basically [this](https://github.com/kanaka/mal?tab=readme-ov-file).

This one will be in C++.

## Steps

- Step 0: REPL

    REPL just makes an AST that only has symbols, numbers, and lists and prints 
    these back on the console.


### General TODO:
What (if any) exceptions should be throw in the `Value` class?
For now things like bounds errors are handled by just throwing `std::logic_error` 
but this doesn't make sense to do long term.

I noticed that reference cpp implementation uses a custom reference counted pointer.
The `Environment` object is also reference counted by inheriting from `RefCounted`, 
which implements `acquire()` and `release()` methods that increment and decrement the 
reference count. I guess this is one way to avoid using a shared pointer?
