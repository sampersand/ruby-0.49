# Ruby v0.49

Ruby 0.49 is the [oldest extant version](https://git.ruby-lang.org/ruby.git/refs/tags) of Ruby. While it's fascinating to see where Ruby came from, actually running Ruby 0.49 is difficult nowadays: It was written exclusively for 32 bit computers, was compiled in an (even for the time) old version of C, and has multiple bugs that can lead to segmentation faults.

Until now.

After spending copious amounts of time fiddling with it, you can now install, compile, and play with Ruby 0.49 locally on your computer!

## Notes
The contents of the ruby repo 

## Compiling
Clone this repo on your computer
Clone this on your computer, then run `./configure`. The old configure file doesn't account for most modern systems, so you have to change a single thing in the makefile:

Convert `DBM = -fpcc-struct-return` to `DBM = `. 

Then you can run `make` and start playing with ruby 0.49!

## Caveats
I haven't fixed all the 32bit <-> 64 bit compatibility issues, so random segfaults may occur. (If you call an unknown function, it'll segfault on you and give no indication as to why it failed.) I plan on fixing them in the future.

## Reading `CHANGELOG` and friends
It's in EUC-JP encoding. You can convert via `iconv -f EUC-JP -t UTF-8 input_filename`; I then pasted it into Google translate to read it.
