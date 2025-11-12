class parent
  def doit
    printf("%s: %d\n", self, eval("%foo"))
  end
end

class child1: parent
  %foo = 3
end

class child2: parent
  %foo = 4
end

class child3: child2
  %foo = 5
end

# print(Object.new.doit)
child3.new.doit
child2.new.doit
child1.new.doit
