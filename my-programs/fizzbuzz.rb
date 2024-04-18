print(do (0..1).each using a
end)
__END__
%MAX = ($ARGV[0] || 100).to_i
a = 'a'
b = 'b'
c = 'c'

__r49_dump(a)
__r49_dump(b)
__r49_dump(c)
for x in 1..%MAX
  q =(case 0
  when x % 3; a
  when x % 5; b
  when x % 15; c
  end)
  __r49_dump(q)
  print(q)
end
