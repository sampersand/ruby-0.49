%MAX = ($ARGV[0] || 100).to_i

for num in 1..%MAX
  if a = 0 == num % 3
    "Fizz".print
  end if

  if b = 0 == num % 5
    "Buzz".print
  end

  (unless (a || b) then num.print end unless)

  "\n".print
end for
