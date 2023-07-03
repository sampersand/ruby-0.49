print(1.0 <=> 2.0)

__END__
"A".foo 3
"A".print()
"A".printf()
__END__
def normal1; end
def func funct1; end

class klass
  # def funct2; end
  def func funct2; end
  def normal2; funct2() end
end

inst = klass.new

normal1()
funct1()
inst.normal2()
# inst.funct2()


__END__
load('knight/utils.rb') # for `p()`

def bar
  !!!!!!!yield(3)
end

do bar(); end #=> method `bar': yield called out of iterator
__END__
def one_upto(max)
  for x in 1..max
    x = [1,2]
    res = yield(x)
    print("yielded: ", res._inspect, "\n")
  end
end


do one_upto(5) using i
  print("inside: ", i, " (", i.apply("class"), ")\n")
  exit()
  i * i
end
