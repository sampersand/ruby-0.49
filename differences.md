if youre curious, oh, there are so, so many differences from ruby
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
