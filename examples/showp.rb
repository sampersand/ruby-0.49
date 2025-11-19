##
# Prints out all executable files in `PATH`
##

# Required because there's a bug in the gc which can cause segfaults,
# but I haven't bothered to find.
GC.disable()

# Directory is an alias for `Dir` lol
def Directory.foreach(dir)
  diro = open(dir)
  protect
    for path in diro
      yield format('%s/%s', dir, path)
    end for
  ensure
    diro.close
  end
end

for dir in getenv('PATH').split(':') # `$ENV['PATH']` is also valid
  # Make sure it's a dir and you can look through it
  unless File.d(dir) && File.x(dir)
    continue # `continue` not `next`!
  end

  # This is how iterators worked!
  do Dir.foreach(dir) using path
    # Make sure it's executable and nonempty
    if File.x(path) && File.f(path)
      print(path, "\n")
    end
  end
end
