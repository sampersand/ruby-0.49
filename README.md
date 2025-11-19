# Ruby v0.49

Ruby 0.49 is the [oldest extant version](https://git.ruby-lang.org/ruby.git/refs/tags) of Ruby. It's absolutely fascinating to see where Ruby came from, but trying to run it is difficult: It was written exclusively for 32 bit computers, in an (even for the time) old version of C, and has multiple severe bugs that can lead to segmentation faults.

Until now.

After spending copious amounts of time fiddling with it, I proudly present a fully working version! You can now install, compile, and play with Ruby 0.49 locally on your computer!

> [!NOTE]
> While I've fixed quite a few bugs, I haven't exhaustively tested this. There's probably many lurking bugs and segfaults!

## Compiling, TL;DR
1. Clone this repo
2. `cd` into `fixed`
3. Run `./configure`
4. Run `make`.
5. The resulting `./ruby` executable is ruby 0.49!

See the end of this file for troubleshooting!

## Sample Program

Here's a sample program that showcases (a very minor) subset of differences! Checkout [my examples](./examples) for other ones!

```ruby
# Constants use `%`. `$ARGV` was a global, not a constant!!
%MAX = ($ARGV[0] || 100).to_i

# Perlism variables were commonly used. This one (still present as of Ruby 3.5,
# but deprecated)
$\ = "\n"

# You had to use `for` loops. No `.each!`
for num in 1..%MAX
  if a = 0 == num % 3 then
    "Fizz".print # You could `.print` instead of `print()`!
  end

  if b = 0 == num % 5 then
    "Buzz".print
  end if # You could add end tags!

  # Unless existed!
  unless a || b then
  	num.print
  end unless
end
```

## Repo structure
This repo's structured as follows:

- `examples` is filled with a bunch of example programs I've written
- `syntax.ebnf` is an EBNF I wrote by hand for what the syntax Ruby 0.49 accepts
- `original` is the exact original code
- `fixed` contains my updated code.
- `fixed/{ruby.1,ToDo,ChangeLog,C-IF}` have all been converted from the original `EUC-JP` encoding[^1] and then translated via AI. Not sure how correct they are!

[^1]: You can convert via `iconv -f EUC-JP -t UTF-8 input.txt`

I wanted to keep the original "wild west" feeling of the source code, so `fixed` only makes surgical, required changes, and leaves everything else as-is. You can identify all the changes I've made in [`fixed`](./fixed) via the `__r49` prefix—if it doesn't have `__r49`, I didn't touch it (and that's how the code originally looked!)

### Flags

You don't need to touch the flags; compiling programs will just work as-is. But you can modify them if you want!

The following flags affect how the program compiles. You can disable them by adding `-D<__r49_no_<flag>` to `CPPFLAGS` when you call `make`. (e.g., `CPPFLAGS='-D__r49_no_64bit -D__r49_no_bugfix make`.)
|          name           | description |
|:------------------------|-------------|
| `__r49_required_change` | Changes that are required to compile it with modern compilers |
| `__r49_64bit`           | Changes to allow compiling on 64 bit |
| `__r49_critical_bugfix` | Fixes to the sourcecode that make Ruby 0.49 bearable |
| `__r49_bugfix`          | More minor bugfixes to the source code |
| `__r49_ubfix`           | Fix behaviours which are now undefined in modern C |
| `__r49_recursion_limit` | How many stackframes to use; set to `0` to revert to the original behaviour of segfaulting when you stack overflow |
| `__r49_no_use_includes` | Use `#include`s for stdlib prototypes, instead of explicitly declaring them. |
| `__r49_redefine_builtins` | Enable ruby's definition of builtins (such as `read`, `wait`, `sigpause`, etc) |


## Known issues
- You can't use `Kernel#class` --- that should be a bugfix i need to do
- `print(nil = 34)` causes segfaults, as even though `nil = 34` raises an exception, the parser doesnt handle it well
- `"πa".intern` segfaults

## Troubleshooting
You'll need `yacc`, which comes preinstalled on some computers---if you're getting errors compiling `parse.y`, you'll need to install it with your favourite package manager (homebrew, `apt-get`, `pacman`, etc.)

If you're getting errors like "too many arguments", you may need to `R49FLAGS='-std=gnu11' make` instead. This is because modern versions of C don't like implicit arguments.

If you're having issues with `ndbm` (which is not required, and is only used in the `DBM` builtin type!), you have a few options:
1. Just disable it, by passing `R49FLAGS='-UHAVE_NDBM_H' make`
2. Other times, you just need to link it---add `R49FLAGS='-lgdbm -lgdbm_compat' make`. Though this might not work, you might have to investigate it
