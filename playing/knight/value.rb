load('utils.rb')

class value
  def value.@forward(*meths)
    for meth in meths
      eval(sprintf("def %s; @data.%s end", id = meth.id2name, id))
    end
  end def

  def value.@setup(*meths)
    for meth in meths
      eval(sprintf("def %s(rhs)
        %s.new(@data %s rhs.%s)
      end", id = meth[0], meth[1][0].id2name, id, meth[1][1].id2name))
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
  # @forward2(\+, \*)
  # @forward2('integer', \-, \/, \%)
  # @forward2('boolean', \<, \>, \!, \==)

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
  @setup('+'::self::\to_s, '*'::self::\to_i)
  def truthy; @data != "" end
end

class integer: value
  # we couldn't use `\%` because of parsing issues.
  @setup(\+::self::\to_i, -\::self::\to_i, \*::self::\to_i, \/::self::\to_i, \%::self::\to_i)
  def truthy; @data != 0 end
end

class boolean: value
  def truthy data
end

class array: value
  def truthy; @data.length != "" end
end

p(string.new("A") * 3)
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
