if youre curious, oh, there are so, so many differences from ruby
identifiers:
- you cant use `?` or `!` at the end of functions (`^is_`—or in one instance (`iterator_p`) `_p$`— are used)
- you can define `..` and `::` functions
- constants start with `%`, not capital letters
- class names don't have to be constants
- constants (`%...`, instance vars (`@...`), and globals (`$...`) can start with digits
    - exception is for globals, `$[1-9]` are reserved, but eg `$10` is allowed.
- Only a handful of the special globals are present (but they retain their meanings, except `=`, which is actually used): `$[*$?!@/\,._^~=]`

- `` ` `` doesn't exist, so that's why `open("|...")` is a thing.
- regex syntax is totally different
- `=begin` doesn't exist
- `BEGIN`/`END` dont exist
- blocks dont use `do`/`end` or `{`..`}`

- function definitions with no arguments take any amount of arguments...?

# Function calling
- Top-level methods (eg `foo()`) required parenthesis always---otherwise they were variables
- Methods (eg `foo.bar()`) could omit parenthesis only if no arguments were given.
- Method definitions could omit parens only if no arguments were given.
- Private methods were defined with `@` (eg `def @private() ... end`), and could only be called
  like private methods today---`@private().foo()...`
- Functions that took no arguments could be passed any number of them (not sure if this is a bug...)
- There was a concept of "functions", removed in the next version (0.50): `def func my_function`.
  They acted essentially the same as private methods, and could only be called at the toplevel.
- The "splat" operator (`*x`) was only usable as the very last argument in a function definition, or
  a function call. Absolutely nowhere else was it supported.
- The `::` syntax was actually used for keyword arguments. `a :: b` was equivalent to `[a, b]`:
```ruby
# `\foo` is the syntax for symbols back then.
def doit(*kws)
    print(kw.assoc(\greeting)[1], ", ", kw.assoc(\place)[1], "!\n")
end
doit(\greeting::"Hello", \place::"World")
```
- Function aliases was done via `def`: `def aliased_name original_name`
- Block syntax was entirely different: it was `do fncall() [using VARIABLE]; ... end`, where the
  `using VARIABLE` was optional. You were allowed exactly one variable per block.
  - A fun little tidbit is that the variable could also be a global variable or instance variable.
- You checked for blocks via `iterator_p()` not `block_given?`
