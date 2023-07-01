
__END__
def fizzbuzz(max)
  print(1,"\n")
  $stdout.flush()
  if (!iterator_p())
    (x = []
    do fizzbuzz(max) using i
    x.push(i)
    end
    return x
    )
  end


  for x in 1..max
    print(x, "\n")
    yield case 0
          when x % 15; "FizzBuzz"
          when x % 3;  "Fizz"
          when x % 5;  "Buzz"
          else         x
          end
  end
end

do fizzbuzz(15) using i
  print(i, "\n")
end
# class fizzbuzz
#   def fizzbuzz.new(*x)
#     if x.length == 0
#       x = [1]
#     end
#     super.init(*x)
#   end

#   def init(start)
#     @start = start; self
#   end

#   def to_s
#     "oops"
#   end

#   def ..(max)

# end


# print(fizzbuzz.new(10)..10)
# print(Proc)
