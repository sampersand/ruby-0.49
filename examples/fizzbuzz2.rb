# Does `fizzbuz`
def fizzbuzz(max)
  # If a block's not given, just return an array of elements.
  unless iterator_p()
    ary = []
    do fizzbuzz(max) using i; ary.push(i) end
    return ary
  end

  # This is similar to modern ruby!
  for x in 1..max
    yield case 0
          when x % 15; "FizzBuzz"
          when x % 3;  "Fizz"
          when x % 5;  "Buzz"
          else         x
          end
  end
end

print(fizzbuzz(20)._inspect())
