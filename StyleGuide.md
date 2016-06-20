# Style Guide for Vick and plugins

To accomplish the majority of stylistic choices, use `clang-format`
with the format specified in `.clang-format`.

1.  Keep lines to 70 characters, with 80 as absolute maximum.  This
    rule is important as it encourages readability of code.  I
    commonly read code with many columns open, and small column limits
    facilitate this.
2.  Never use C style casts, always use a `static_cast` when
    appropriate.  C style casts will *never* perform a `dynamic_cast`
    and they can lead to `reinterpret_cast`, which can have extremely
    bad consequences.  Prefer the verbose casts to do each task, as
    they are more reliable and more clearly expose your intent.
    `static_cast` will always be checked at compile time for validity.
3.  Use the keywords `and`, `or`, and `not` over the operators `&&`,
    `||`, and `!`, respectively.  They do the exact same things but
    are more readable.
4.  Namespace your code properly.  Use a subnamespace of `vick`.
5.  `typedef`s should be used extensively to provide meaning to types.
    Use `size_t` over `unsigned int` as `size_t` is cross platform and
    more readable!
6.  Prefer templates over preprocessor macros for generic functions,
    but use macros for code duplication.
7.  Put parenthesis around the ternary operator to prevent ambiguity.
    `1 + false ? 3 : 1000` is `3`, while `1 + (false ? 3 : 1000)` is
    `1001`.
8.  Put parenthesis around assignment in expressions to prevent
    ambiguity and show you aren't mistaking equality for assignment:
    `if ((x = fun()) != 3) {}`
9.  Follow the Java style guidelines of always having brackets
    touching their respective declaration.  In addition, do not indent
    code inside a namespace declaration.

Example:

    namespace vick {
    namespace plugin_name {

    class ex {
        void say_hi() {
            if (true) {
                std::cout << "hi\n";
            }
        }
    };

    }
    }

10. Properly generate changes for your edits by tracking what happens
    and recording it _and_ displaying it live.
11. Prefer running shell commands in a separate thread.  Do not edit
    the buffer if you use multithreading.  Instead make a new one and
    edit it, calling `print_contents` periodically.
12. Put a space after control keywords such as `if`, `while`, and
    `for`.
13. Always put brackets around control statements.  It is more
    consistent and helps catch errors.

Example:

    for (auto x : xs) {
        std::cout << x;
    }
    for (auto x : xs) { std::cout << x; }

13. Put the star or ampersand for a pointer or reference,
    respectively, with the type, unless it is in a list of variables,
    where you should annotate each individual variable with a star or
    ampersand.
14. Prefer raw pointers and references to smart pointers when it makes
    sense to use them.  This forces you to recognize who owns a
    resource and have them manage it instead of having a resource
    magically managed.  Note that functions that interact with the
    user return a `boost::optional<std::shared_ptr<change> >`.  This
    shared pointer is required because `change`, as an abstract class,
    cannot be used as a value type, and because discarding the return
    value of the function should *not* cause a memory leak!
15. Wrap macros in `do { ... } while (0)` to prevent dangling `else`s.
16. Write tests for your code.
