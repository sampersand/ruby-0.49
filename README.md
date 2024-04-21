# Ruby v0.49

Ruby 0.49 is the [oldest extant version](https://git.ruby-lang.org/ruby.git/refs/tags) of Ruby. While it's fascinating to see where Ruby came from, actually running Ruby 0.49 is difficult nowadays: It was written exclusively for 32 bit computers, was compiled in an (even for the time) old version of C, and has multiple bugs that can lead to segmentation faults.

Until now.

After spending copious amounts of time fiddling with it, you can now install, compile, and play with Ruby 0.49 locally on your computer!

## Compiling, tl;dr
1. Clone this repo
2. `cd` into `fixed`
3. Run `./configure`.
4. Run `make`. The resulting `./ruby` executable is ruby 0.49!

## Notes
The original code as it existed in 1994 is in [`original`](./original). The code I've cleaned up lives in [`fixed`](./fixed). I've tried to stay as true to the original code as possible in my cleaned up code, only fixing things that're necessary. 

You can identify all the changes I've made in [`fixed`](./fixed) via `__r49`; If it doesn't have `__r49`, I didn't touch it (and that's how the code originally looked.)

### Flags

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


## Caveats
If you disable some of the macros, you may end up with segfaults. I also haven't exhaustively tested it, so you may encounter problems. 

## Reading `CHANGELOG` and friends
It's in EUC-JP encoding. You can convert via `iconv -f EUC-JP -t UTF-8 input_filename`; I then pasted it into Google translate to read it.
