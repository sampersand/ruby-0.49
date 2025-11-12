# Aliasing!
def __old_open open

# Redefine `open` to allow it to take a block!
def open(*x)
  value = __old_open(*x)

  # We use `iterator_p()` instead of `block_given?`
  if iterator_p() then
    # `begin` was `protect` lol
    protect
      yield value
    ensure
      value.close
    end protect
  end if

  value
end def

# Try it out!
for file in $ARGV
  # This is how blocks were; syntax was so different!
  do open(file, "r") using i
    print(i.read())
  end
end
