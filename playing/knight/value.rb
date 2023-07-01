def tap; yield(self) ; self end

class value
  def value.@forward(*meths)
    for meth in meths
      eval(sprintf("def %s; @data.%s end", id = meth.id2name, id))
    end
  end def

  def value.@forward2(cls, *meths)
    for meth in meths
      id = q[0].id2name
      print(sprintf("def %s(rhs); %s.new(@data %s rhs) end\n", id = meth.id2name, cls, id))
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
  @forward2('itself', \+, \*)
  @forward2('integer', \-, \/, \%)
  @forward2('boolean', \<, \>, \!, \==)

  def <=>(rhs)
    protect
      value.from(@data <=> rhs)
    resque
      value.from(%FALSE)
    end
  end

  def _inspect
    apply("class").name + "(" + @data._inspect + ")"
  end
end

class string: value
  def truthy; @data != "" end
end

class integer: value
  def truthy; @data != 0 end
end

class boolean: value
  def truthy data
end

class array: value
  def truthy; @data.length != "" end
end

print((string.new("A") + 3)._inspect)
# print(value.new(12), "\n")
__END__

print("!")
$x += 0
print("{", ($x <=> 10), "}\n")
# if $x < 10
#   $x += 1
#   load("value.rb")
# end if
