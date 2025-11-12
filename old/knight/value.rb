class Value
end

class Null: Value
  %null = new()
  def Null.new; %null end

  def to_i; 0 end
  def to_a; [] end
  def to_s; "" end
  def is_truthy; %FALSE end
  def _inspect; "Null" end
end

class Bool: Value
  def _inspect; sprintf("Bool(%s)", self) end
  $t = Value.new()
  $f = Value.new()
  def Bool.new(value) fail('1') end
end
print(Bool.new(0, 1, 2))
__END__
# eval("def Bool.new(value) if value then $t else $f end end")
  def $t.to_i; 1 end
  def $t.to_a; [self] end
  def $t.to_s; 'true' end
  def $t.is_truthy; %TRUE end

  def $f.to_i; 0 end
  def $f.to_a; [] end
  def $f.to_s; 'false' end
  def $f.is_truthy; %FALSE end
printf("%s\n%s\n", $t.id, $f.id)
Bool.new(1).to_i
# printf("%s\n%s\n%s\n", $t.id, $f.id, Bool.new(1).id)
print(Bool.new(1).to_i)

__END__
class Value
  def Value.new(val)
    super.init(val)
  end

  attr("val")

  def init(val)
    @val = val
    self
  end

  def to_s; run().val.to_s end
  def to_i; run().val.to_i end
  def to_a; run().to_a end
  def is_truthy; run().val end
  def length; to_a().length end

  def run; self end
end


class Var: Value
  # `{}` syntax was supported, but the fact it's named `Dict` is so much wackier
  @known_variables = Dict.new

  def Var.new(name)
    unless @known_variables.has_key(name)
      @known_variables[name] = super.init(name)
    end

    @known_variables[name]
  end

  attr("name")
  attr("value", %TRUE)

  def init(name)
    @name = name
    super(nil)
  end

  def assign value=; # the `;` is required so it doesn't think it's an assignment.

  def run
    @value || fail("uninitialized variable: " + @name)
  end
end

class Null : Value
  def to_i; 0 end
  def to_s; "" end
  def to_a; [] end
  def is_truthy; %FALSE end

  def _inspect; "Null" end
end
%null = Null.new(nil)

class Bool : Value
  def _inspect; sprintf("Bool(%s)", self) end
end

%true = Bool.new(%TRUE)
def %true.to_i; 1 end
def %true.to_s; "true" end
def %true.to_a; [self] end
def %true.is_truthy; true end
%false = Bool.new(%FALSE)
def %false.to_i; 1 end
def %false.to_s; "true" end
def %false.to_a; [self] end
def %false.is_truthy; false end
def Bool.new(value) if value then %true else %false end

class Str : Value
  def length; @val.length end
end

class Int : Value
  def init(val)
    super(val.to_i)
  end

  for x in '+ - * / % **'.split
    eval(sprintf("def %s(rhs) Int.new(@val %s rhs.to_i) end", x, x))
  end

  def <(rhs) Bool.new(@val < rhs.to_i) end
  def >(rhs) Bool.new(@val > rhs.to_i) end
end

class Ary : Value
  def Ary.new(*args)
    super(args)
  end
end
%EMPTY_ARY = Ary.new()

class Ast : Value
  def Ast.new(fn, args)
    super([fn, args])
  end

  def init(a)
    @fn = a[0]
    @args = a[1]
    self
  end

  def run
    kn.apply(@fn, *@args)
  end
end
