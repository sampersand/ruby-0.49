def takes_keywords(*kw)
  print(kw.assoc('a')[1], "\n")
  print(kw.assoc('b')[1], "\n")
  34
end

takes_keywords('a' :: 34, 'b' :: 45)
