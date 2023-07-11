class Foo
  include Enumerable
  def each
    for x in 1..10
      yield x
    end
  end
end

print(Foo.new.max())
# x = 1..10
# method(\bar)
# print([1,2,3].max())
# print((1..10).max())
