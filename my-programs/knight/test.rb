class Foo
  new()
end
def Foo.new(value)
  fail('failed')
end

Foo.new(0, 1, 2)
d
