def if_print
  if iterator_p(); print("iterator\n") else print("not iterator\n") end
end

def print_if
  print(if iterator_p(); "iterator" else "not iterator" end, "\n")
end

def if_not_print
  #  v--- note the negation
  if !iterator_p(); print("iterator\n") else print("not iterator\n") end
end

if_print()         #=> not iterator
do if_print(); end #=> iterator

print_if()         #=> not iterator
do print_if(); end #=> not iterator

if_not_print()         #=> iterator
do if_not_print(); end #=> iterator

