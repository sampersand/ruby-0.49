def foo(a, *b)
end

load('utils.rb')

class value
  def value.@forward(*meths)
    for meth in meths
      evalf("def %s; @data.%s end", id = meth.id2name, id)
    end
  end def

  def value.@setup(*meths)
    for meth in meths
      id = meth[0]
      if id.responds_to("id2name") then id = id.id2name end if
      evalf("def %s(rhs) %s.new(@data %s rhs.%s) end", id , meth[1][0], id, meth[1][1].id2name)
    end
  end def

  def value.name; to_s().ucfirst end

  attr("data", %TRUE)
  include Comparable

  def @init(data) @data = data end

  def value.new(data)
    do super().tap() using v
      v.apply("@init", data)
    end
  end

  @forward(\to_s, \to_i)

  def <=>(rhs)
    protect
      @data <=> rhs
    resque
      %FALSE
    end
  end

  def _inspect
    apply("class").name + "(" + @data._inspect + ")"
  end
end

class string: value
  @setup(?+::self::\to_s, ?*::self::\to_i)
  def truthy; @data != "" end
end

class integer: value
  @setup(
    ?+::self::\to_i,
    ?-::self::\to_i,
    ?*::self::\to_i,
    ?/::self::\to_i,
    ?%::self::\to_i)
  def truthy; @data != 0 end def
end

class boolean: value
  def truthy data
end

class array: value
  def truthy; @data.length != "" end
end

# print("A" % "B")
p(string.new("A") < "b" < "c")
p(nil > "a")
# p(integer.new(3) + "4")
# print(value.new(12), "\n")
__END__

print("!")
$x += 0
print("{", ($x <=> 10), "}\n")
# if $x < 10
#   $x += 1
#   load("value.rb")
# end if
