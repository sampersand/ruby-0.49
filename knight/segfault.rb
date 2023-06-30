def puts(*x)
  print(x.join(" "), "\n")
end

class foo
  def coerce(x) [self, x] end
  def +(rhs)
    rhs * 2
  end
end

puts(3 + foo.new)
